#define F_CPU	16000000UL
#include <util/delay.h>

#include "bluetooth.h"
#include "timer.h"

#include "driver.h"
#include "led.h"

/*
	PINS
		X-AXIS
			STEP		PB0		<- OUTPUT
			DIR			PD7		<- OUTPUT
			SLEEP		PB1		<- OUTPUT
			
		Y-AXIS
			STEP		PD5		<- OUTPUT
			DIR			PD6		<- OUTPUT
			SLEEP		PD4		<- OUTPUT
		
		ACTION-LED		PB2		<- OUTPUT
		
		BLUETOOTH
			RX			PD0		<- AT.RECEIVE	-> BT.TRANSMITT
			TX			PD1		<- AT.TRANSMITT -> BT.RECEIVE
		BT-MAC
			Eraser		00:35:FF:1C:D0:E6
			Joystick	50:51:A9:FC:86:8E
			
			
	X -130 && 125 == 255
	Y -128 && 127 == 255
*/

int main(void){
	bluetooth_init();
	timers_init();
	
	drivers_init();
	led_init();
	
	sei();
	
	for(;;){
	}
	
	return 1337;
}
