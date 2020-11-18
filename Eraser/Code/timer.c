#include "timer.h"

ISR(TIMER1_COMPA_vect){
	led_show_mode(bluetooth_get_mode());
}

ISR(TIMER2_COMPA_vect){
	Mode mode = bluetooth_get_mode();
	
// 	if(mode != FREE)
// 		drivers_stop();
// 	else
	
	drivers_go(bluetooth_get_joystick());
}

/*
	6250 = (0.1 / (1 / (16 * 10^6))) / 256
	0x186A = 6250
	100ms interrupt = 0x186A
*/
void timer1_init(void) {
	//CTC mode
	TCCR1B |= (1 << WGM12);
	
	// Startar Timer0 med 256 prescaler.
	TCCR1B |= (1 << CS12);
	
	// Sätter Timer0 compare value A till 100 ms
	OCR1A = 0x186A;
	
	// Startar interrupt
	TIMSK1 |= (1 << OCIE1A);
}

/*
	25 = (0.0001 / (1 / (16 * 10^6))) / 64
	0x19 = 25
	0.1ms interrupt = 0x19
*/
void timer2_init(void){
	// CTC mode.
	TCCR2A |= (1 << WGM21);
	
	// Startar Timer2 med 64 prescaler.
	TCCR2B |= (1 << CS22);
	
	// Sätter Timer2 A compare value A till 0.1 ms
	OCR2A = 0x19;
	
	// Startar interrupt
	TIMSK2 |= (1 << OCIE2A);
}

void timers_init(void){
	timer1_init();
	timer2_init();
}
