#ifndef LED_H
#define LED_H

#include <avr/io.h>

#include "bluetooth.h"

void led_init(void);

void led_show_safety(uint8_t btnState);
void led_show_mode(Mode mode);

#endif
