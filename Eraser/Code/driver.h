#ifndef DRIVER_H
#define DRIVER_H

#include <avr/io.h>
#include <util/atomic.h>

#include "bluetooth.h"

typedef enum{
	FORWARD = 0,
	BACKWARD = 1
}XDir;

typedef enum{
	UP = 0,
	DOWN = 1
}YDir;

void drivers_init(void);

void drivers_stop(void);
void drivers_go(Joystick joystick);

#endif
