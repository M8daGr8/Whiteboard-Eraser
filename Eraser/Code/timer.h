#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "bluetooth.h"
#include "led.h"
#include "driver.h"

void timers_init(void);

#endif
