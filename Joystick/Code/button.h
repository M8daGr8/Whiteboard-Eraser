#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>

typedef enum{
	RELEASED = 0,
	PRESSED = 1
}State;

void button_init(void);

void button_update_clean_state(void);
void button_update_safety_state(void);

uint8_t button_safety_isPressed(void);
uint8_t button_clean_isPressed(void);
 
#endif
