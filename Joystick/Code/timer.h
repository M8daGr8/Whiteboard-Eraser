#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <util/atomic.h>
#include <avr/interrupt.h>

#include "bluetooth.h"
#include "potentiometer.h"
#include "button.h"
#include "led.h"

void timers_init(void);

#endif
