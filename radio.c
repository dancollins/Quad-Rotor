/*
 * Quad Rotor Controller
 * Rev A
 * Dan Collins 2012
 */

#include "radio.h"

xQueueHandle xRadioTxQueue;

xQueueHandle StartRadioTxTask(void) {
    xRadioTxQueue = xQueueCreate(10, sizeof(xRadioTxMessage));

    xTaskCreate(vRadioTx, "RadioTransmitter", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, (xTaskHandle*) NULL); // Start the radio TODO:  Stack size

    return xRadioTxQueue;
}

void vRadioTx( void * pvParameters ) {
    xRadioTxMessage xMessage;

    while(1) {
        while(xQueueReceive(xRadioTxQueue, &xMessage, portMAX_DELAY ) != pdPASS); // Wait for a message
        radio_putS(xMessage.debug);
    }
}

void vRadioRx( void * pvParameters ) {
    portTickType xLastWakeTime;
    const portTickType xFrequency = 5;
    char * str;

    xLastWakeTime = xTaskGetTickCount(); // Store the current time

    while(1) {
        if(rx_int_flag) { // Replace this with a binary semaphore
            str = strstr(rx_buffer, "t");
            
            if(str != NULL)
                xQueueSendToBack(xInputValues, str, (portTickType)0); // Send the message to the control thread
            
            rx_int_flag = 0;
        } else {
            vTaskDelayUntil(&xLastWakeTime, xFrequency); // 10mS delay
        }
    }
}

void radio_putC(char c) {
    portTickType xLastWakeTime;
    const portTickType xFrequency = 1;
    xLastWakeTime = xTaskGetTickCount(); // Store the current time
    
    while(U2STAbits.UTXBF)
        vTaskDelayUntil(&xLastWakeTime, xFrequency); // 1mS delay

    U2TXREG = c; // Send the byte
}

void radio_putS(char *s) {
    while(*s)
        radio_putC(*s++);
}
