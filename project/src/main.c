//runs toy project
#include <msp430.h>
#include "libTimer.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "wdInterruptHandler.h"

int main(){
  configureClocks();
  enableWDTInterrupts();

  led_init();
  buzzer_init();
  switch_init();
  set_state(0);   //init state 0
  
  or_sr(0x18);   //CPU off, GIE on
  return 0;
}

