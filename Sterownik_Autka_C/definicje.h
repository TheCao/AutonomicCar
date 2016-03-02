/*
 * definicje.h
 *
 * Created: 2016-02-27 22:16:45
 *  Author: Komar
 */ 


#ifndef DEFINICJE_H_
#define DEFINICJE_H_
/*
PD0, PD1 VCC, GND - USB konwerter
PA1-PA7 - LCD 

*/
#define DIAGA (1<<PC1)
#define DIAGB (1<<PC0)
#define INA (1<<PD4)
#define INB (1<<PD3)


void triger(void);
void hcsr_init(void);
void vnh3sp30_init();
void silnik_lewo(void);
void silnik_prawo(void);
void silnik_stop(void);


#endif /* DEFINICJE_H_ */