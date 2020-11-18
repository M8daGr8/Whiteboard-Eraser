#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <avr/io.h>
#include <avr/interrupt.h>

void potentiometer_init(void);
void potentiometer_adc_start(void);

int16_t potentiometer_get_Y(void);
int16_t potentiometer_get_X(void);

#endif
