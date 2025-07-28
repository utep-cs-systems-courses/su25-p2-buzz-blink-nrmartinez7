#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

static char count=0;

void state_advance(){
  //change red and green based on count
  green_on=(count>>1)&1;
  red_on=count&1;

  led_changed=1;
  led_update();

  count=(count+1)%4;
}


