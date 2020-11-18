#include "bluetooth.h"
#include "timer.h"

#include "potentiometer.h"
#include "button.h"
#include "led.h"

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
