#include "bluetooth.h"

void bluetooth_putchar(uint8_t data, FILE *stream);
void bluetooth_clear_data(void);

static FILE uart_stdout = FDEV_SETUP_STREAM(bluetooth_putchar, NULL, _FDEV_SETUP_WRITE);

#define		X_AXIS 0
#define		Y_AXIS 1

volatile Mode mode = STOP;

volatile Joystick joystick = { 0, 0 };

/*
	Kollar input från joysticken, om de "joystick controlled" så sparas
	X och Y axis värderna i en struct.

	Skickar tillbaka vilket läge systemet är i för att konfirmera för joysticken
	att erasern har fått meddelandet.

	TODO:
		[ ]en egen fil med metoder för joystick inputs.
*/
ISR(USART_RX_vect){
	static uint8_t collectingValues = 0;
	
	static char axisValue[10] = "";
	static uint8_t currentValue = 0;
	
	uint8_t chr = UDR0;
	
	if(chr == '<'){
		collectingValues = 1;
	}
	else if(chr == ','){
		axisValue[currentValue] = '\0';
		joystick.xAxis = atoi(axisValue);
		
		axisValue[0] = '\0';
		currentValue = 0;
	}
	else if(chr == '>'){
		axisValue[currentValue] = '\0';
		joystick.yAxis = atoi(axisValue);
		
		axisValue[0] = '\0';
		currentValue = 0;
		
		collectingValues = 0;
	}
	else if(collectingValues){
		axisValue[currentValue++] = chr;
	}
	else{
		mode = chr - 48;
		if(mode != FREE)
			bluetooth_clear_data();
		printf("%d", mode);
	}
	
	if(currentValue > sizeof(axisValue) / sizeof(axisValue[0]))
		currentValue = 0;
}

void bluetooth_init(void) {
	UBRR0H = (UBRR >> 8);
	UBRR0L = (UBRR);
	
	UCSR0A = 0;
	
	UCSR0B = ((1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0));
	UCSR0C = (1 << UCSZ01 | 1 << UCSZ00);

	stdout = &uart_stdout;
}

void bluetooth_putchar(uint8_t data, FILE *stream) {
	if (data == '\n')
		bluetooth_putchar('\r', NULL);

	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

/*
	Rensar structen "joystick" / sätter värdena till 0
*/
void bluetooth_clear_data(void){
	joystick.xAxis = 0;
	joystick.yAxis = 0;
}

/*
	Returnerar vilket läge systemet är i.
*/
Mode bluetooth_get_mode(void){
	return mode;
}

/*
	returnerar structen joystick
*/
Joystick bluetooth_get_joystick(void){
	return joystick;
}

