#include "serial.h"

xQueueHandle outputData;

SerialModule_t UART_1 = {
    .name = UART1,
    .tx_buf_index = 0,
    .tx_buf_size = 0,
    .rx_buf_index = 0,
    .rx_buf_size = 0
};

void serial_init(void) {
    // UART1
    U1MODEbits.ON = 1; // Enable the UART
    U1STAbits.UTXEN = 1; // Enable the TX
    U1STAbits.URXEN = 1; // Enable the RX
    U1STAbits.URXISEL = 0; // Interrupt when the RX buffer has any data
    U1BRG = 64; // 38.4kbps

    // Interrupt
    IEC0bits.U1RXIE = 1; // Enable receive interrupt
    IPC6bits.U1IP = 4; // ipl = 4
    IPC6bits.U1IS = 3;

    // Queue
    outputData = xQueueCreate(5, sizeof(SerialMessage_t)); // Create a queue to hold up to 5 messages
}

void serial_isr(BYTE p) {
    SerialModule_t * mod = serial_loadStruct(p);

    mod->rx_buf[mod->rx_buf_index++] = UARTGetData(p).__data; // Save the data into the receive buffer
}

void serial_update(void * pvParameters) {
    SerialMessage_t * message;
    DWORD i;
    UART_DATA data; // The byte to send

    while (TRUE) {
        if (xQueueReceive(outputData, &message, portMAX_DELAY)) {
            for (i = 0; i < message->length; i++) {
                while (UARTTransmitterIsReady(message->port) == FALSE); // Wait until the transmitter is ready
                data.__data = message->buffer[i]; // Store the byte into the silly union
                UARTSendData(message->port, data); // Send the byte
            }

            vPortFree(message->buffer); // Free the message buffer
            vPortFree(message); // Free the message struct
        }
    }
}

BOOL serial_putChar(BYTE p, BYTE c) {
    SerialMessage_t * message;

    message = pvPortMalloc(sizeof(SerialMessage_t));

    message->port = p;
    message->length = 1; // Only one byte..!

    message->buffer = pvPortMalloc(sizeof(BYTE));
    message->buffer[0] = c;

    if (xQueueSend(outputData, &message, 0) == errQUEUE_FULL) { // Add the byte to the queue
        // The message failed to add, so remove the memory allocated
        vPortFree(message->buffer); // Free the message buffer
        vPortFree(message); // Free the message struct

        led2 ^= 1;
    }

    return TRUE;
}

BOOL serial_putString(BYTE p, BYTE *s) {
    SerialMessage_t * message;

    message = pvPortMalloc(sizeof(SerialMessage_t));

    message->port = p;
    message->length = strlen(s);

    message->buffer = pvPortMalloc(sizeof(BYTE) * message->length);
    memcpy(message->buffer, s, message->length);

    if (xQueueSend(outputData, &message, 0) == errQUEUE_FULL) { // Add the byte to the queue
        // The message failed to add, so remove the memory allocated
        vPortFree(message->buffer); // Free the message buffer
        vPortFree(message); // Free the message struct

        led2 ^= 1;
    }

    return TRUE;
}

BOOL serial_putData(BYTE p, BYTE *buf, DWORD len) {
    SerialMessage_t * message;

    message = pvPortMalloc(sizeof(SerialMessage_t));

    message->port = p;
    message->length = len;

    message->buffer = pvPortMalloc(sizeof(BYTE) * message->length);
    memcpy(message->buffer, buf, message->length);

    if (xQueueSend(outputData, &message, 0) == errQUEUE_FULL) { // Add the byte to the queue
        // The message failed to add, so remove the memory allocated
        vPortFree(message->buffer); // Free the message buffer
        vPortFree(message); // Free the message struct

        led2 ^= 1;
    }

    return TRUE;
}

BYTE * serial_getBuffer(BYTE p) {
    SerialModule_t * mod = serial_loadStruct(p);

    if (mod == NULL)
        return NULL;

    return mod->rx_buf;
}

void serial_clearBuffer(BYTE p) {
    SerialModule_t * mod = serial_loadStruct(p);

    memset(mod->rx_buf, 0, SERIAL_RX_BUFFER_SIZE);
}

SerialModule_t * serial_loadStruct(BYTE p) {
    switch (p) {
        case UART1:
            return &UART_1;
            break;
        default:
            return NULL;
    }
}
