#ifndef LED_H
#define LED_H

#include <avr/io.h>

#include "bluetooth.h"

void led_init(void);

void led_low(void);
void led_high(void);
void led_toggle(void);

void led_show_mode(Mode mode);

#endif
