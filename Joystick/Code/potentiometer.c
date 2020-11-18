#include "potentiometer.h"

#define Y_AXIS		ADC2D
#define X_AXIS		ADC3D

volatile uint8_t targetPot = Y_AXIS;
volatile int16_t values[2] = { 0, 0 };

/*
	Jag skulle haft koll på vilka ports jag valde på atmegan.
	skulle valt 0 och 1 för att göra koden lite finare och slippa 
	"uint8_t value = (targetPot == X_AXIS);" och köra på targetPot
	vid sparning av värden.

	värdena sparas i en int16_t array för att.
	Första värdena (alltså potentiometerns mittpunkt) i mid.
	senare värden - mid ger negativa värden och den är 16 bit för
	att:
	X -130 && 125
	Y -128 && 127
*/
ISR(ADC_vect){
	uint8_t value = (targetPot == X_AXIS);
	static uint8_t mid[2] = { 0, 0 };
	
	if(!mid[value])
		mid[value] = ADCH;
	else
		values[value] = ADCH - mid[value];
	
	targetPot++;
	if(targetPot > X_AXIS)
		targetPot = Y_AXIS;
}

void potentiometer_init(void){
	//St�ng av digital input buffer	
	DIDR0 |= (1 << ADC2D) | (1 << ADC3D);

	// (AVcc Voltage Reference) (V�nsterjustering)
	ADMUX |= (1 << REFS0) | (1 << ADLAR);
	
	//  (S�tt prescaler till F_CPU / 8) (ADC Complete interrupt Enable) (ADC enable)
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0) | (1 << ADIE) | (1 << ADEN);
}


void potentiometer_adc_start(void){
	// V�lj vilken potentiometer som ska l�sas av i MUX.
	ADMUX = ((ADMUX & 0xF0) | targetPot);

	// Startar ADC conversion.
	ADCSRA |= (1 << ADSC);
}

/*
	Returnerar Y axis värde
*/
int16_t potentiometer_get_Y(void){
	return values[0];
}

/*
	Returnerar X axis värde
*/
int16_t potentiometer_get_X(void){
	return values[1];
}
