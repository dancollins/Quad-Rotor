#include "serial.h"

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
}

void serial_isr(BYTE p) {
    SerialModule_t * mod = serial_loadStruct(p);

    mod->rx_buf[mod->rx_buf_index++] = UARTGetData(p).__data; // Save the data into the receive buffer
}

void serial_update(BYTE p) {
    SerialModule_t * mod = serial_loadStruct(p);

    // If we have data to send
    if (mod->tx_buf_index < mod->tx_buf_size) {
        // If the transmitter is ready to send data
        if (UARTTransmitterIsReady(mod->name)) {
            UARTSendDataByte(mod->name, mod->tx_buf[mod->tx_buf_index++]);
        }
    } else {
        // Data has been set, to reset the buffer
        mod->tx_buf_index = 0;
        mod->tx_buf_size = 0;
    }
}

BOOL serial_putChar(BYTE p, BYTE c) {
    SerialModule_t * mod = serial_loadStruct(p);

    if (mod->tx_buf_size >= SERIAL_TX_BUFFER_SIZE)
        return FALSE;

    mod->tx_buf[mod->tx_buf_size++] = c; // Add the character to the buffer
    return TRUE;
}

BOOL serial_putString(BYTE p, BYTE *s) {
    SerialModule_t * mod = serial_loadStruct(p);
    
    if (strlen(s) >= (SERIAL_TX_BUFFER_SIZE - mod->tx_buf_size))
        return FALSE; // String is too big

    while(*s)
        serial_putChar(p, *s++);

    return TRUE;
}

BOOL serial_putData(BYTE p, BYTE *buf, DWORD len) {
    DWORD i;
    
    SerialModule_t * mod = serial_loadStruct(p);

    if (len >= (SERIAL_TX_BUFFER_SIZE - mod->tx_buf_size))
        return FALSE; // String is too big

    for (i = 0; i < len; i++)
        serial_putChar(p, buf[i]); // Add all of the bytes to the buffer

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
