#include "timer.h"

ISR(TIMER1_COMPA_vect){
	led_show_mode(bluetooth_get_mode());
	bluetooth_send();
}

ISR(TIMER2_COMPA_vect){
	potentiometer_adc_start();
	button_update_safety_state();
	button_update_clean_state();
	led_show_safety(button_safety_isPressed());
}

/*
	3125 = (0.1 / (1 / (8 * 10^6))) / 256
	0xC35 = 3125
	100ms interrupt = 0xC35
*/
void timer1_init(void) {
	//CTC mode
	TCCR1B |= (1 << WGM12);
	
	// Startar Timer0 med 256 prescaler.
	TCCR1B |= (1 << CS12);
	
	// Sätter Timer0 compare value A till 100 ms
	OCR1A = 0xC35;
	
	// Startar interrupt
	TIMSK1 |= (1 << OCIE1A);
}

/*
	78.125 = (0.01 / (1 / (8 * 10^6))) / 1024
	0x4E = 78 ~ 78.125
	10ms interrupt = 0x4E
*/
void timer2_init(void){
	// CTC mode.
	TCCR2A |= (1 << WGM21);
	
	// Startar Timer2 med 1024 prescaler.
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
	
	// Sätter Timer2 A compare value A till ca 10 ms
	OCR2A = 0x4E;
	
	// Startar interrupt
	TIMSK2 |= (1 << OCIE2A);
}

void timers_init(void){
	timer1_init();
	timer2_init();
}
