/*
 * Quad Rotor Controller
 * Rev A
 * Dan Collins 2012
 */

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <string.h>
#include <math.h>

#include "HardwareProfile.h"

#include "radio.h"
#include "accel.h"
#include "gyro.h"
#include "mag.h"
#include "imu.h"

#pragma config FWDTEN = OFF

#pragma config POSCMOD = HS
#pragma config FNOSC = PRIPLL
#pragma config FPLLIDIV = DIV_3
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_1

#pragma config FPBDIV = DIV_2

#define Kp 25.0
#define Ki 0.05
#define Kd 0.0

static xQueueHandle xRadioTxQueue;
xQueueHandle xInputValues;

unsigned char rx_buffer[512]; // UART2 input buffer
unsigned char rx_int_flag = 0; // Set when the data reception is complete

void vBlinkyLed(void * pvParameters);
void vTestThread(void * pvParameters);
void constrain(unsigned int value[], int thrust);
int thrustLen(unsigned char * msg);

void __ISR(_DMA0_VECTOR, ipl5) Dma0(void) {
    INTClearFlag(INT_DMA0);

    rx_int_flag = 1; // Set the interrupt flag // TODO: This should be a binary semphore
    DmaChnClrEvFlags(DMA_CHANNEL0, DMA_EV_BLOCK_DONE);
}

void init(void) {
    /* System */
    SYSTEMConfig(GetSystemClock(), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    while(!(OSCCON && 0x20)); // Wait for PLL to start up
    DDPCONbits.JTAGEN = 0; // Disable JTAG

    /* Ports */
    LED = 0; // Enable the LED
    LED_OFF();

    MOTORA = 0; // Set the motor pins as outputs
    MOTORB = 0;
    MOTORC = 0;
    MOTORD = 0;

    /* UART2 */
    U2MODEbits.ON = 1; // Enable the UART
    U2STAbits.UTXEN = 1; // Enable the TX
    U2STAbits.URXEN = 1; // Enable the RX
    U2BRG = 259; // 9600bps

    /* Timer2 - Motor PWM */
    OpenTimer2(T2_ON | T2_IDLE_STOP | T2_PS_1_64, PWM_TICK); // 50Hz PWM Frequency

    /* Timer 3 - IMU time measurement */
    OpenTimer3(T3_ON | T3_PS_1_256, 65535); // 16 bit synchronous counter

    /* Motor OCR */
    OpenOC1(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0); // Motor A
    OpenOC2(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0); // Motor B
    OpenOC3(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0); // Motor C
    OpenOC4(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0); // Motor D

    SetPulseOC1(0, timeToPeriod(1000)); // Set the PWM to 1mS duty
    SetPulseOC2(0, timeToPeriod(1000));
    SetPulseOC3(0, timeToPeriod(1000));
    SetPulseOC4(0, timeToPeriod(1000));

    /* I2C */
    I2CConfigure(I2C1, I2C_STOP_IN_IDLE | I2C_ENABLE_HIGH_SPEED);
    I2CSetFrequency(I2C1, GetPeripheralClock(), 400000); // 400KHz
    I2CEnable(I2C1, TRUE);

    /* DMA */
    DMACONbits.ON = 1; // Enable the DMA controller
    DmaChnConfigure(DMA_CHANNEL0, DMA_CHN_PRI0, DMA_CONFIG_AUTO);
    DmaChnSetMatchPattern(DMA_CHANNEL0, '\n');
    DmaChnSetEventControl(DMA_CHANNEL0, DMA_EV_START_IRQ_EN | DMA_EV_MATCH_EN | DMA_EV_START_IRQ(_UART2_RX_IRQ)); // IRQ will start a DMA transfer, and then it will keep copying until it gets a match
    DmaChnSetTxfer(DMA_CHANNEL0, (void*)&U2RXREG, rx_buffer, 1, 256, 1); // UART2 buffer is one byte in size, so copy 1 byte at a time into the receiver buffer
    DmaChnSetEvEnableFlags(DMA_CHANNEL0, DMA_EV_BLOCK_DONE); // Fire an interrupt when we get a pattern match, or the buffer gets full
    DmaChnEnable(DMA_CHANNEL0);

    /* Interrupts */
    INTSetVectorPriority(INT_DMA_0_VECTOR, INT_PRIORITY_LEVEL_5);
    INTSetVectorSubPriority(INT_DMA_0_VECTOR, INT_SUB_PRIORITY_LEVEL_3);
    INTClearFlag(INT_DMA0);
    INTEnable(INT_DMA0, INT_ENABLED);

    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();
}

int main(void) {
    init();
    accel_init();
    gyro_init();
    mag_init();

    xInputValues = xQueueCreate(10, sizeof(char*));

    xTaskCreate(vBlinkyLed, "BlinkyLED", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, (xTaskHandle*) NULL); // Start the Blinky task
    xTaskCreate(vTestThread, "TestThread", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+3, (xTaskHandle*) NULL); // Start a test thread
    xRadioTxQueue = StartRadioTxTask();
    xTaskCreate(vRadioRx, "RadioReceiver", 300, NULL, tskIDLE_PRIORITY+2, (xTaskHandle*) NULL); // Start the radio TODO:  Stack size

    vTaskStartScheduler(); // Start the scheduler
    
    return 0; // It should never get here, as the scheduler is a loop
}

/* Blinky LED */
void vBlinkyLed(void * pvParameters) {
    portTickType xLastWakeTime;
    const portTickType xFrequency = 500; // 500 ticks is 500mS

    xLastWakeTime = xTaskGetTickCount(); // Store the current time

    while(1) {
        LED_TOGGLE();
        vTaskDelayUntil(&xLastWakeTime, xFrequency); // 500mS delay
    }
}

void vTestThread(void * pvParameters) {
    portTickType xLastWakeTime;
    const portTickType xDelay = 5;

    unsigned int count = 0;
    int inputBytes = 0;
    int motorValue[4];
    float error[3];
    float errorPrev[3];
    float errorAverage[3];
    float errorChange[3];
    float pitch, roll, yaw;
    unsigned int thrust = 0;
    int i;
    float dT = 0.005; // Time in seconds between samples

    xRadioTxMessage xMessage; // Create an instance of the radio TX struct
    char str[100]; // 100 byte string
    unsigned char input[10];

    struct imuEstimate imu;

    xLastWakeTime = xTaskGetTickCount(); // Store the current time
    
    xMessage.debug = str;

    vTaskDelayUntil(&xLastWakeTime, (portTickType)1000);

    while(1) {
        imu_update(&imu);

        if (xQueueReceive(xInputValues, input, (portTickType)1) == pdPASS) { // If we have a message
            inputBytes = thrustLen(input);

            sprintf(str, "E,Received %d bytes.\n", inputBytes);
            xQueueSendToBack(xRadioTxQueue, &xMessage, (portTickType)0);

            if (inputBytes == 3) {
                thrust = input[1]<<8;
                thrust |= input[2];
            } else {
                sprintf(str, "E,Invalid number of bytes!\n", inputBytes);
                xQueueSendToBack(xRadioTxQueue, &xMessage, (portTickType)0);
            }
        }

        /* Error:
         * e(t) = currentValue - setPoint
         */

        /* Proportion:
         * (Kp * e(t)) / (Max motor - Min motor)
         */

        /* Integration:
         * averageError += e(t) / 2
         * Ki * averageError * dT
         */

        /* Differenciation:
         * changeInError = e(t) - oldError
         * Kd * (changeInError / dT)
         */

        for (i=0; i<3; i++)
            errorPrev[i] = error[i]; // Save the old error value

        /* TODO: Set points */
        error[0] = imu.ex - 0.12; // X axis
        error[1] = imu.ey - 0; // Y axis
        error[2] = imu.ez - 1; // Z axis

        for (i=0; i<3; i++) {
            errorAverage[i] += error[i]/2; // Find average error on all axes
            errorChange[i] = error[i] - errorPrev[i]; // Find change in error on all axes
        }

        pitch = (error[0] * Kp) + ((errorAverage[0] * dT)*Ki) + ((errorChange[0] / dT)*Kd);
        roll = (error[1] * Kp) + ((errorAverage[1] * dT)*Ki) + ((errorChange[1] / dT)*Kd);
        //yaw = (error[2] * Kp) + ((errorAverage[2] * dT)*Ki) + ((errorChange[2] / dT)*Kd);

        motorValue[0] = 1350 - pitch + roll + thrust;
        motorValue[1] = 1350 - pitch - roll + thrust;
        motorValue[2] = 1350 + pitch - roll + thrust;
        motorValue[3] = 1350 + pitch + roll + thrust;

        constrain(motorValue, thrust);

        SetPulseOC1(0, timeToPeriod(motorValue[0]));
        SetPulseOC2(0, timeToPeriod(motorValue[1]));
        SetPulseOC3(0, timeToPeriod(motorValue[2]));
        SetPulseOC4(0, timeToPeriod(motorValue[3]));
        
        if (count >= 30) {
            sprintf(str, "G,%f,%f,%f\nT,%d,%d,%d,%d\n", imu.ex, imu.ey, imu.ez, motorValue[0], motorValue[1], motorValue[2], motorValue[3]);
            xQueueSendToBack(xRadioTxQueue, &xMessage, (portTickType)0);
            count = 0;
        }

        count++;

        vTaskDelayUntil(&xLastWakeTime, xDelay);
    }
}

void vApplicationStackOverflowHook( void ) {
    while(1);
}

void constrain(unsigned int * value, int thrust) {
    int i;
    for (i=0; i<4; i++) {
        if (thrust > 10) {
            if (value[i] < 1100)
                value[i] = 1100;
            if (value[i] > 1600)
                value[i] = 1600;
        } else {
            value[i] = 1000;
        }
    }
}

int thrustLen(unsigned char * msg) {
    int ret = 0;
    
    while (*msg != '\n') {
        msg++; // Increment pointer
        ret++; // Increment counter
    }

    return ret;
}
