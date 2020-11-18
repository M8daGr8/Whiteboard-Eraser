#include "bluetooth.h"
#include "timer.h"

#include "potentiometer.h"
#include "button.h"
#include "led.h"

/*
	PINS
		JOYSTICK
			X-AXIS		PC3		<- ADC
			Y-AXIS		PC2		<- ADC
			A-BTN		PD3		<- INPUT
			
		SAFTEY-BTN		PB2		<- INPUT
		SAFTEY-LED		PD4		<- OUTPUT
		ACTION-LED		PD2		<- OUTPUT
		
		BLUETOOTH
			RX			PD0		<- AT.RECEIVE	-> BT.TRANSMITT
			TX			PD1		<- AT.TRANSMITT -> BT.RECEIVE
		BT-MAC
			Joystick	50:51:A9:FC:86:8E
			Eraser		00:35:FF:1C:D0:E6
			
	X -130 && 125 == 255
	Y -128 && 127 == 255
*/
int main(void){
	bluetooth_init();
	timers_init();
	
	potentiometer_init();
	button_init();
	led_init();
	
	sei();
	
	for(;;);
	
	return 1337;
}
