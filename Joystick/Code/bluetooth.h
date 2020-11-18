#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#define F_CPU			8000000UL
#define BAUD			38400UL
#define UBRR			(F_CPU / (BAUD * 16UL)) - 1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "button.h"
#include "potentiometer.h"

/*
	CLEAN gör inget för tillfället.

	Systemet sätts till CONNECTING automatiskt
	vid disconnect.
*/
typedef enum{
	STOP = 0,
	FREE = 1,
	CLEAN = 2,
	CONNECTING
}Mode;

void bluetooth_init(void);

void bluetooth_send(void);

Mode bluetooth_get_mode(void);

#endif
