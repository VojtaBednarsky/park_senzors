#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"
#include "timer.h"
// #include "segment.h"



void BZR(uint16_t dist);
volatile uint16_t  i=0;
volatile uint16_t value = 0;
char word [5];
int main(void)
{
 
TIM_config_prescaler(TIM2, TIM_PRESC_8);
TIM_config_interrupt(TIM2, TIM_OVERFLOW_ENABLE);


ADCSRA = ADCSRA |  _BV(ADEN);
ADCSRA = ADCSRA |  _BV(ADIE);
ADCSRA = ADCSRA |  _BV(ADPS0) |  _BV(ADPS1) |  _BV(ADPS2);
ADMUX = ADMUX |  _BV(REFS0);

sei();
GPIO_config_output(&DDRD, PD4);
/* Infinite loop */
for (;;)
  {
        
      
  }

  return (0);
}
ISR(TIMER2_OVF_vect)
{
  ADCSRA = ADCSRA |  _BV(ADSC);
  BZR(value);
  itoa(value, word, 10);
 
}

void BZR(uint16_t dist)
{
uint16_t delay=0;
uint16_t  freq=0;
  
 if (dist<=400 && dist>200) { freq=20; delay=6000; }
else if (dist<=200 && dist>70) { freq=19; delay=5650; }
else if (dist<=70 && dist>25) { freq=16; delay=4600; }
else if (dist<=25 && dist>18) { freq=15; delay=4250; }
else if (dist<=18 && dist>14) { freq=14; delay=3900; }
else if (dist<=14 && dist>11) { freq=13; delay=3550; }
else if (dist<=11 && dist>10) { freq=12; delay=3200; }
else if (dist<=10 && dist>9) { freq=11; delay=2850; }
else if (dist<=9 && dist>8) { freq=10; delay=2500; }
else if (dist<=8 && dist>7) { freq=9; delay=2150; }
else if (dist<=7 && dist>6) { freq=8; delay=1800; }
else if (dist<=6 && dist>5) { freq=7; delay=1450; }
else if (dist<=5 && dist>4) { freq=6; delay=1100; }
else if (dist<=4 && dist>3) { freq=5; delay=750; }
else if (dist<=3 && dist>2) { freq=4; delay=400; }
else { freq=3; delay=0; }

  i++;
  if (i%freq==0 && i<995){
  
   GPIO_write(&PORTD, PD4, 0);
   GPIO_write(&PORTD, PD4, 1);
   GPIO_write(&PORTD, PD4, 0); 
   
  }
else if(i==1000+delay)
i=0;
}

ISR(ADC_vect)
{
   
    value = ADC;
}