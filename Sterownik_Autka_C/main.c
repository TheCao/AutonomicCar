/*
 * CPPFile1.cpp
 *
 * Created: 2016-02-27 16:38:06
 *  Author: Komar
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd44780.h"
#include "definicje.h"
/*
void triger(void);
static uint16_t LastCapture;
static uint16_t odl = 0;
volatile uint16_t PulseWidth; //globalna zmienna licz¹ca szerokoœc impulsu
*/
int main(void)
{
	lcd_init();
	lcd_locate(0,0);
	lcd_str("Sterownik du¿ego silnika");
	lcd_locate(1,0);
	lcd_str("Wersja 1");
	_delay_ms(2000);
	lcd_cls();
	// obsluga przerwan od ICP1
	sei();         // globalne zezwolenie na przerwania
	
	hcsr_init(); 
	pwm_init();
	vnh3sp30_init();
	
	OCR0 = 0;
	
	// testy silnika
	while(1)
	{
		/*triger(); //wyzwolenie odczytu z czujnika
		odl = PulseWidth / 58;
		lcd_locate(0,1);
		lcd_str("Odleglosc [cm]:");
		lcd_locate(1,3);
		lcd_int(odl);
		_delay_ms(100);
		lcd_cls();*/
		
		silnik_lewo();
		lcd_locate(1,3);
		lcd_str("Lewo");
		_delay_ms(5000);
		lcd_cls();
		
		lcd_locate(1,3);
		lcd_str("Stop");
		silnik_stop();
		_delay_ms(3000);
		lcd_cls();
		
		silnik_prawo();
		lcd_locate(1,3);
		lcd_str("Prawo");
		_delay_ms(5000);
		lcd_cls();
		
		lcd_locate(1,3);
		lcd_str("Stop");
		silnik_stop();
		_delay_ms(3000);
		lcd_cls();
	}
	

	return 0;
}

