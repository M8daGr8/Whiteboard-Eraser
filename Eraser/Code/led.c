#include "led.h"

#define LED PORTB2

void led_init(void){
	DDRB |= (1 << DDB2);
	PORTB |= (1 << LED);
}

void led_low(void){
	PORTB &= ~(1 << LED);
}

void led_high(void){
	PORTB |= (1 << LED);
}

void led_toggle(void){
	PORTB ^= (1 << LED);
}

void led_show_mode(Mode mode){
	static uint8_t count = 0;
	
	switch(mode){
		case STOP:
			if(count == 10)
				led_toggle();
				break;
		case FREE:
			led_toggle();
			break;
		case CLEAN:
			led_low();
			break;
		default:
			led_high();
			break;
	}
	if(count++ == 10)
		count= 0;
}

