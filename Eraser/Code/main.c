#include "bluetooth.h"
#include "timer.h"

#include "driver.h"
#include "led.h"

int main(void){
	bluetooth_init();
	timers_init();
	
	drivers_init();
	led_init();
	
	sei();
	
	for(;;);
	
	return 1337;
}
