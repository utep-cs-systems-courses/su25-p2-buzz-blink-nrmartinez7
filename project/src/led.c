//this file controls the leds

#include <msp430.h>
#include "led.h"

//flags for change
unsigned char red_flag=0;
unsigned char green_flag=0;
unsigned char led_changed_flag=0;

//toggle leds based on flags/state
static void led_updating(){
  char change=0;
  if(red_flag){
    change |= LED_RED;
  }
  if(green_flag){
    change |=LED_GREEN;
  }

  P1OUT &= ~(LED_RED | LED_GREEN);
  P1OUT |= change;

  led_changed_flag=0;
}

//init leds 
void led_init(){
  P1DIR |= (LED_RED | LED_GREEN);
  led_updating();
}

//updates physical leds if needed
void led_update(){
  if(led_changed_flag){
    led_updating();
  }
}

//toggles only red led based on flag
void set_red_led(char on){
  red_flag=on;
  led_changed_flag=1;
}

//toggles only green led based on flag
void set_green_led(char on){
  green_flag=on;
  led_changed_flag=1;
}
