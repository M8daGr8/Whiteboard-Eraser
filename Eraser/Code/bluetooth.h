#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#define F_CPU			16000000UL
#define BAUD			38400UL
#define UBRR			(F_CPU / (BAUD * 16UL)) - 1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum{
	STOP = 0,
	FREE = 1,
	CLEAN = 2,
	CONNECTING
}Mode;

typedef struct{
	int16_t xAxis;
	int16_t yAxis;
}Joystick;

void bluetooth_init(void);

Mode bluetooth_get_mode(void);

Joystick bluetooth_get_joystick(void);

#endif
