#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#define F_CPU			16000000UL
#define BAUD			38400UL
#define UBRR			(F_CPU / (BAUD * 16UL)) - 1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

/*
	CLEAN är inte implementerat än

	Connceting sätts automatiskt vid disconnect
*/
typedef enum{
	STOP = 0,
	FREE = 1,
	CLEAN = 2,
	CONNECTING
}Mode;

/*
	Skulle varit soft med int8_t
	men efterson minsta på x axis är -130
	så går inte detta utan att mappa värdet.

	Värderna ser ut såhär:	
	X -130 && 125
	Y -128 && 127

*/
typedef struct{
	int16_t xAxis;
	int16_t yAxis;
}Joystick;

void bluetooth_init(void);

Mode bluetooth_get_mode(void);

Joystick bluetooth_get_joystick(void);

#endif
