/*
 * definicje.c
 *
 * Created: 2016-02-27 22:40:53
 *  Author: Komar
 */ 

#include "definicje.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void triger(void);
static uint16_t LastCapture;
static uint16_t odl = 0;
volatile uint16_t PulseWidth; //globalna zmienna licz¹ca szerokoœc impulsu

ISR(TIMER1_CAPT_vect)
{
	// Timer na potrzeby pomiaru czasu dla czujnika
	// static uint16_t LastCapture;

	if( !(TCCR1B & (1<<ICES1)) ) PulseWidth = ICR1 - LastCapture;
	LastCapture = ICR1;

	TCCR1B ^= (1<<ICES1); //zbocze malej¹ce wywo³a przerwanie
}

void triger(void)
{
	PORTD &= ~(1<<PD5);
	_delay_us(2);
	PORTD |= (1<<PD5); //wystawienie jedynki na TRIG
	_delay_us(10);    //wymagane 10 uS stanu wysokiego
	PORTD &= ~(1<<PD5);  //wystawienie zera na TRIG
}
void pwm_init(void)
{
	// initialize timer0 in PWM mode
	TCCR0 |= (1<<WGM00)|(1<<COM01)|(1<<WGM01)|(1<<COM00); // Tryb Fast PWM, Set OC0 on compare match
	TCCR0 |= (1<<CS01); // preskaler 8, sterowanie za pomoc¹ OCR0 = (0-255)

	// make sure to make OC0 pin (pin PB3 for atmega32) as output pin
	DDRB |= (1<<PB3);
	PORTB |= (1<<PB3);
}
void silnik_lewo(void)
{
	PORTD |= INB;
	PORTD &= ~INA;
}

void silnik_prawo(void)
{
	PORTD &= ~INB;
	PORTD |= INA;
}

void silnik_stop(void)
{
	// obie wartosci na 0 czyli stop
	PORTD &= ~INA;
	PORTD &= ~INB;
}

void hcsr_init(void)
{
	//ustawienie wyjœcia trigerra i echo oraz ustawienie przerwañ na 1B
	DDRD |= (1<<PD5);  //wyjscie
	PORTD &= ~(1<<PD5); //TRIGER

	DDRD &= ~(1<<PD6);  //wejscie ECHO
	PORTD &= ~(1<<PD6);  //ICP
	
	TCCR1B |= (1<<ICES1); // Zbocze narastaj¹ce wywo³a przerwanie
	TCCR1B |= (1<<CS11);  //preskaler = 8
	TCCR1B |= (1<<ICNC1); //NOISE CANCELLER
	TIMSK |= (1<<TICIE1);  // zezwolenie na przerwanie od ICP
}

void vnh3sp30_init()
{
	// ustawienie sterownika w tryb bez sprawdzania b³êdów
	//DiagA PC1
	//DiagB PC0
	DDRC |= DIAGA | DIAGB;
	PORTC |= DIAGA | DIAGB;
	DDRD |= INA | INB;
	silnik_stop(); // poczatkowy stan to GND Break czyli 0 i 0
	
	
}