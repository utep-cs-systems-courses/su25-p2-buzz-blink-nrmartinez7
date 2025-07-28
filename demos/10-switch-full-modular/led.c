#include <msp430.h>
#include "led.h"
#include "switches.h"

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}

static char red_on=0;
static char green_on=0;

void set_red_led(char on){
  red_on=on;
}

void set_green_led(char on){
  green_on=on;
}

void led_update(){
  char ledFlags=0;

  if(red_on){
    ledFlags |= LED_RED;
  }
  if(green_on){
    ledFlags |= LED_GREEN;
  }

  P1OUT=(P1OUT & ~LEDS)|ledFlags;
}

