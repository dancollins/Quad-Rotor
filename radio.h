#ifndef RADIO_H
#define RADIO_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "HardwareProfile.h"

#include <string.h>

extern unsigned char rx_buffer[512]; // UART2 input buffer
extern unsigned char rx_int_flag; // Set when the data reception is complete

extern xQueueHandle xInputValues;

xQueueHandle StartRadioTxTask(void);
void vRadioTx(void * pvParameters);
void vRadioRx(void * pvParameters);

void radio_putC(char c);
void radio_putS(char *s);

typedef struct {
    char* debug;
} xRadioTxMessage;

#endif