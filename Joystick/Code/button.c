#include "button.h"

#define STY_BTN		PINB2
#define CLEAN_BTN	PIND3

volatile State safetyBtnState = RELEASED;
volatile State cleanBtnState = RELEASED;
	
void button_init(void){
	DDRB &= ~(1 << DDB2);
	DDRD &= ~(1 << DDD3);
}

State button_read_saftey(void){
	return (PINB & (1 << STY_BTN)) ? PRESSED : RELEASED;
}

State button_read_clean(void){
	return (PIND & (1 << CLEAN_BTN)) ? PRESSED : RELEASED;
}

void button_update_safety_state(void){
	static uint8_t count = 0;
	static State lastState = RELEASED;
	State currentState = button_read_saftey();
	
	if(currentState != lastState)
		count = 0;
	
	//10 ms * 5 = 50 ms debounce delay
	if(count++ >= 5)
		if(currentState != safetyBtnState)
			safetyBtnState = currentState;
			
	lastState = currentState;
}

void button_update_clean_state(void){
	static uint8_t count = 0;
	static State lastState = RELEASED;
	State currentState = button_read_clean();
	
	if(currentState != lastState)
		count = 0;
	
	//10 ms * 5 = 50 ms debounce delay
	if(count++ >= 5)
		if(currentState != cleanBtnState)
			cleanBtnState = currentState;
	
	lastState = currentState;
}

uint8_t button_safety_isPressed(void){
	return (safetyBtnState == PRESSED);
}

uint8_t button_clean_isPressed(void){
	return (cleanBtnState == PRESSED);
}
