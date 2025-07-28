#include <msp430.h>
#include "led.h"

void greenControl(int on)
{
  if (on) {
    P1OUT |= LED_GREEN;
  } else {
    P1OUT &= ~LED_GREEN;
  }
}


//same as green but in red
void redControl(int on){
  if(on){
    P1OUT |=LED_RED;
  }else{
    P1OUT &= ~LED_RED;
  }
}
