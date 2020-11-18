#include "led.h"

#define ACT_LED		PORTD2
#define STY_LED		PORTD4

void led_init(void){
	DDRD |= (1 << DDD2) | (1 << DDD4);
	PORTD |= (1 << PORTD2) | (1 << PORTD4);
}

void led_low(uint8_t pin){
	PORTD &= ~(1 << pin);
}

void led_high(uint8_t pin){
	PORTD |= (1 << pin);
}

void led_toggle(uint8_t pin){
	PORTD ^= (1 << pin);
}

/*
	tar in vilket state säkerhetsknappen
	är i och tänder / släcker led.
*/
void led_show_safety(uint8_t btnState){
	if(btnState)
		led_low(STY_LED);
	else
		led_high(STY_LED);
}

/*
	Väljer hur leden kommer bete sig beroende på vilket läge
	systemet är i.

	Denna körs var 100 ms.
	Dvs.
		"STOP": blink 1 sek
		"FREE": blink 100 ms
*/
void led_show_mode(Mode mode){
	static uint8_t count = 0;
	
	switch(mode){
		case STOP:
			if(count == 10)
				led_toggle(ACT_LED);
			break;
		case FREE:
			led_toggle(ACT_LED);
			break;
		case CLEAN:
			led_low(ACT_LED);
			break;
		default:
			led_high(ACT_LED);
			break;
	}
	if(count++ == 10)
		count= 0;
}
