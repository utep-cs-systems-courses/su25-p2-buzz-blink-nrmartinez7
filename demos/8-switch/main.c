#include <msp430.h>
#include "libTimer.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (LED_RED|LED_GREEN)

#define SW1 BIT3		/* switch1 is p1.3 */
#define SWITCHES SW1		/* only 1 switch on this board */

//global vars
char led_state =0; //red=0 , green=1
char blink_state=0; //led on/off state when blinking
char blink_mode=0; //solid=0, blinking=1


void update_led(char on){
  if(on){
    
    if(led_state){
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
    }else{
      P1OUT |= LED_RED;
      P1OUT &= ~LED_GREEN;
    }
  }else{
    turn_off_leds();
  }
}

void turn_off_leds(){
  P1OUT &=~LEDS;
}

void
switch_interrupt_handler()
{
  char p1val = P1IN;		/* switch is in P1 */

/* update switch interrupt sense to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */

  //toggle state to change leds
  if (!(p1val & SW1)) {
    blink_mode ^=1;
    blink_state=0;

    toggle_state();
    
    if(blink_mode==0){
      update_led(1);
    }
  }
}

void toggle_state(){
  led_state ^=1;
  update_led(1);
}


void main(void) 
{
  configureClocks();
  enableWDTInterrupts();
  
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		/* leds initially off */
  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */

  led_state=1;
  blink_mode=1;
  update_led(1);
  
  or_sr(0x18);  // CPU off, GIE on
} 

void __interrupt_vec(WDT_VECTOR)WDT(){
  static int blink_count=0;
  static int toggle_count=0;

  if(blink_mode==1){
    blink_count++;
    
    if(blink_count>=125){
      blink_state ^=1;
      update_led(blink_state);
      blink_count=0;

      toggle_count++;
      if(toggle_count >=2){
	toggle_state();
	toggle_count=0;
      }
    }
  }
}

/* Switch on P1 (S2) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P1IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
