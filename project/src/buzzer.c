//this file controls the buzzer

#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

//intit speaker
void buzzer_init(){
  timerAUpmode();
  P2SEL2 &= ~(BIT6|BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR |=BIT6;

}

//sets PWM and sets duty cycle to 50%
void buzzer_set_period(short cycles){
  CCR0=cycles;
  CCR1=cycles >>1;
}
