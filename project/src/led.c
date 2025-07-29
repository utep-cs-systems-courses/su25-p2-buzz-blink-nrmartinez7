#include <msp430.h>
#include "led.h"

unsigned char red_on=0;
unsigned char green_on=0;
unsigned char led_changed=0;

static void led_updating(){
  char change=0;
  if(red_on){
    change |= LED_RED;
  }
  if(green_on){
    change |=LED_GREEN;
  }

  P1OUT &= ~(LED_RED | LED_GREEN);
  P1OUT |= change;

  led_changed=0;
}

void led_init(){
  P1DIR |= (LED_RED | LED_GREEN);
  led_updating();
}

void led_update(){
  if(led_changed){
    led_updating();
  }
}

void set_red_led(char on){
  red_on=on;
  led_changed=1;
}

void set_green_led(char on){
  green_on=on;
  led_changed=1;
}
