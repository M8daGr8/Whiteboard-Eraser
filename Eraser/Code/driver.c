#include "driver.h"

#define X_STEP		PORTB0
#define X_DIR		PORTD7
#define X_SLEEP		PORTB1

#define Y_STEP		PORTD5
#define Y_DIR		PORTD6
#define Y_SLEEP		PORTD4

void driver_X_init(void){
	DDRB |= (1 << DDB0) | (1 << DDB1);
	DDRD |= (1 << DDD7);
}

void driver_Y_init(void){
	DDRD |= (1 << DDD5) | (1 << DDD6) | (1 << DDD4);
}

void drivers_init(void){
	driver_X_init();
	driver_Y_init();
}

void driver_X_step_high(void){
	PORTB |= (1 << X_STEP);
}

void driver_X_step_low(void){
	PORTB &= ~(1 << X_STEP);
}

void driver_X_step_toggle(void){
	PORTB ^= (1 << X_STEP);
}

void driver_Y_step_high(void){
	PORTD |= (1 << Y_STEP);
}

void driver_Y_step_low(void){
	PORTD &= ~(1 << Y_STEP);
}

void driver_Y_step_toggle(void){
	PORTD ^= (1 << Y_STEP);
}

void driver_X_sleep_high(void){
	PORTB |= (1 << X_SLEEP);
}

void driver_X_sleep_low(void){
	PORTB &= ~(1 << X_SLEEP);
}

void driver_Y_sleep_high(void){
	PORTD |= (1 << Y_SLEEP);
}

void driver_Y_sleep_low(void){
	PORTD &= ~(1 << Y_SLEEP);
}

/*
	Sätter direction pin beroende på input
*/
void driver_X_set_direction(XDir dir){
	if(dir == FORWARD)
		PORTD &= ~(1 << X_DIR);
	else
		PORTD |= (1 << X_DIR);
}

/*
	Sätter direction pin beroende på input
*/
void driver_Y_set_direction(YDir dir){
	if(dir == UP)
		PORTD |= (1 << Y_DIR);
	else
		PORTD &= ~(1 << Y_DIR);
}

/*
	Stoppar x driver
	ATOMIC_BLOCK för att forca stopp
*/
void driver_X_stop(void){
	ATOMIC_BLOCK(ATOMIC_FORCEON){
		driver_X_sleep_low();
		driver_X_step_low();
	}
}

/*
	Stoppar y driver
	ATOMIC_BLOCK för att forca stopp
*/
void driver_Y_stop(void){
	ATOMIC_BLOCK(ATOMIC_FORCEON){
		driver_Y_sleep_low();
		driver_Y_step_low();
	}
}

/*
	Stoppar alla drivers
	ATOMIC_BLOCK för att forca att de stoppas
*/
void drivers_stop(void){
	ATOMIC_BLOCK(ATOMIC_FORCEON){
		driver_X_stop();
		driver_Y_stop();
	}
}

/*
	UNDER CONSTRUCTION
	detta är en map funktion som inte används just nu.
*/
uint8_t map_value(int16_t value, uint8_t inMin, uint8_t inMax, uint8_t outMin, uint8_t outMax){
	return (abs((((value - inMin) * (outMax - outMin)) / (inMax - inMin))) + outMin);
}

/*
	UNDER CONSTRUCTION
	denna samt map_value är tänkt att fixas för en smooth acceleration och de-acceleration
*/
uint8_t get_speed(int16_t joystickValue, int8_t acceleration){
	return map_value(abs(joystickValue), 6, 130, 40, 1) ;
} 

/*
	denna körs om mode == free varje 0.1 ms
	tar x axis value och kollar "döda vinkeln" / mid point.

	annars steppar motorn och väljer direction varanan gång
*/
void driver_X_go(int16_t xValue){
	
	if(xValue < 5 && xValue > -5){
		driver_X_stop();
	}
	else {
		static uint8_t count = 0;
		
		if(count++ >= 1){
			driver_X_sleep_high();
			driver_X_set_direction((xValue > 0) ? FORWARD : BACKWARD);
			driver_X_step_toggle();
			count = 0;
		}
	}
}

/*
	denna körs om mode == free varje 0.1 ms
	tar x axis value och kollar "döda vinkeln" / mid point.

	annars steppar motorn och väljer direction varanan gång
*/
void driver_Y_go(int16_t yValue){
	if(yValue < 5 && yValue > -5){
		driver_Y_stop();
	}
	else {
		static uint8_t count = 0;
		
		if(count++ >= 1){
			driver_Y_sleep_high();
			driver_Y_set_direction((yValue > 0) ? UP : DOWN);
			driver_Y_step_toggle();
			count = 0;
		}
	}
}

void drivers_go(Joystick joystick){
	driver_X_go(joystick.xAxis);
	driver_Y_go(joystick.yAxis);
}