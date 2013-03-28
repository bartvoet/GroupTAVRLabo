#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//next: use usart in combination with sipo
//next: connect to traffic-light system
//next: make more modular

volatile uint8_t i=0;
volatile unsigned long milis = 0;
volatile unsigned long now = 0;
volatile unsigned long lastMillis = 0;
volatile unsigned short continueCounting = 1;

#define TOGGLE_INPUT PB5
#define BUTTON_INPUT PB4
//hello
//----
// Initialization section
//----
void initTimer() {
	TCCR0A = (1 << WGM01);
	TCCR0B = ((1 << CS01) | (1 << CS00));
	OCR0A = 249;
	TIMSK0 = (1 << OCIE0A);
}

void initButton() {
	DDRB &= ~(1 << BUTTON_INPUT);
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT4);
}

void initInterruptInput() {
	initTimer();
	initButton();
	sei();
}

void initToggleSwitch() {
	DDRB &= ~(1 << TOGGLE_INPUT);
}

const uint8_t OUTPUT_PORTS_FOR_DDRB
	= ((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3));

/*
 * Prepare the output
 */
void initOutputNumber() {
	DDRB |= OUTPUT_PORTS_FOR_DDRB;
}

/*
 * Init all the IO
 */
void initIO() {
	initOutputNumber();
	initToggleSwitch();
	initInterruptInput();
}

int main(void) {
	initIO();
	while (1) {
		// waisting some clock-cycles while awaiting interupts
	}
	return 0; // never reached
}


//-----
// Inline methods for readability
//-----

/*
 * Controlling on level of ms
 */

volatile inline uint8_t checkForToggle() {
	return (PINB & (1 << TOGGLE_INPUT));
}

/*
 * Change the output
 */
void inline changeOutputNumber(volatile uint8_t i) {
	PORTB = (PORTB & 0xb11110000) | i;
}

/*
 * Counting milliseconds
 */
ISR(TIMER0_COMPA_vect) {
	milis++;
	if(continueCounting) {
		if (milis - now >= 1000) {
			now = milis;
			changeOutputNumber(i);
			if (checkForToggle()) {
				i++;
				if (i > 9) {i=0;}
			}else {
				if (i <= 0 ) {i=10;}
				i--;
			}
		}
	}
}

/*
 * When button pressed toggle between true or false
 */
ISR(PCINT0_vect) {
	if (milis - lastMillis >= 1000) { //software de-bouncing
		lastMillis = milis;
		continueCounting ^= (1);//toggle between true and false
	}
}
