#include "board.h"

/**
 * Configuration.
 * 80MHz Clock
 */
#pragma config POSCMOD = EC // Using an external clock IC
#pragma config FNOSC = PRIPLL // Use the PLL as the clock source
#pragma config FPLLIDIV = DIV_2 // Divide 8MHz / 2 = 4MHz
#pragma config FPLLMUL = MUL_20 // Multiply 4MHz * 20 = 80MHz
#pragma config FPLLODIV = DIV_1 // Don't divide the output = 80MHz
#pragma config FPBDIV = DIV_2 // PB Clock will be 40MHz

#ifdef __DEBUG
#pragma config ICESEL = ICS_PGx1
#endif

button_t board_b1, board_b2, board_b3;

void board_init(void) {
    // System
    SYSTEMConfig(GetSystemClock(), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    while(!(OSCCON && 0x20)); // Wait for PLL to start up
    DDPCONbits.JTAGEN = 0; // Disable JTAG

    // LEDs
    init_led1();
    init_led2();
    init_led3();
    init_led4();
    init_led5();
    init_led6();
    init_led7();
    init_led8();
    init_led9();
    init_led10();
    init_led11();
    init_led12();

    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;
    led5 = 0;
    led6 = 0;
    led7 = 0;
    led8 = 0;
    led9 = 0;
    led10 = 0;
    led11 = 0;
    led12 = 0;

    // Buttons
    init_but1();
    board_b1.pressed = FALSE;
    board_b1.time = 0;
    board_b1.read = FALSE;

    init_but2();
    board_b2.pressed = FALSE;
    board_b2.time = 0;
    board_b2.read = FALSE;

    init_but3();
    board_b3.pressed = FALSE;
    board_b3.time = 0;
    board_b3.read = FALSE;

    // Interrupts
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();
}

/**
 * Button Debouncing
 */
void board_update(void) {
    // Button 1
    if (but1) {
        board_b1.pressed = TRUE;

        if(board_b1.time < BUTTON_COUNT)
            board_b1.time++;
    } else {
        if (board_b1.time)
            board_b1.time --;

        if (board_b1.time < BUTTON_COUNT) {
            board_b1.pressed = FALSE;
            board_b1.read = FALSE;
        }
    }

    // Button 2
    if (but2) {
        board_b2.pressed = TRUE;

        if(board_b2.time < BUTTON_COUNT)
            board_b2.time++;
    } else {
        if (board_b2.time)
            board_b2.time --;

        if (board_b2.time < BUTTON_COUNT) {
            board_b2.pressed = FALSE;
            board_b2.read = FALSE;
        }
    }

    // Button 3
    if (but3) {
        board_b3.pressed = TRUE;

        if(board_b3.time < BUTTON_COUNT)
            board_b3.time++;
    } else {
        if (board_b3.time)
            board_b3.time --;

        if (board_b3.time < BUTTON_COUNT) {
            board_b3.pressed = FALSE;
            board_b3.read = FALSE;
        }
    }
}

void board_idle(void) {
    PowerSaveIdle(); // TODO: Move this to board so it's more portable
}

BOOL board_getButtonState(BYTE button) {
    switch (button) {
        case 1:
            if ((board_b1.pressed == TRUE) && (board_b1.time >= BUTTON_COUNT) && (board_b1.read == FALSE)) {
                board_b1.read = TRUE;
                return TRUE;
            }
            return FALSE;
            break;
        case 2:
            if ((board_b2.pressed == TRUE) && (board_b2.time >= BUTTON_COUNT) && (board_b2.read == FALSE)) {
                board_b2.read = TRUE;
                return TRUE;
            }
            return FALSE;
            break;
        case 3:
            if ((board_b3.pressed == TRUE) && (board_b3.time >= BUTTON_COUNT) && (board_b3.read == FALSE)) {
                board_b3.read = TRUE;
                return TRUE;
            }
            return FALSE;
            break;
    }
}
