#include "bluetooth.h"

void bluetooth_putchar(uint8_t data, FILE *stream);

static FILE uart_stdout = FDEV_SETUP_STREAM(bluetooth_putchar, NULL, _FDEV_SETUP_WRITE);

volatile Mode mode = STOP;

/*
	sätter läge på joysticken. 
	Detta kommer från erasern som konfiremerar att
	meddelande har mottagits.
*/
ISR(USART_RX_vect){
	mode = UDR0 - 48;
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
	skickar vilket läge som systemet är i just nu.
	Denna metod körs va 100 ms.
*/
void bluetooth_send(void){
	static uint8_t count = 0;
	
	if(bluetooth_get_mode() == CLEAN){
		if(count++ >= 5){
			if(button_safety_isPressed() || button_clean_isPressed()){
				printf("%d", STOP);
				count = 0;
			}
		}
	}
	else if(bluetooth_get_mode() != CLEAN && !button_safety_isPressed()){
		printf("%d", STOP);
	}
	else if(button_safety_isPressed() && button_clean_isPressed()){
		printf("%d", CLEAN);
	}
	else if(button_safety_isPressed()){
		printf("%d<%d,%d>", FREE, potentiometer_get_X(), potentiometer_get_Y());
	}
	else{
		printf("%d", STOP);
	}
}

/*
	Returnerar systemets läge
*/
Mode bluetooth_get_mode(void){
	return mode;
}
