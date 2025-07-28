//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

/*
  Global variables and state machines
 */

//state var representing reciprocal of duty cycle 
static int blinkLimit=5;


/*
  intialization
*/

int main(void) {
  //led output direction
  P1DIR |= LEDS;

  //red on, green off
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  //setup clocks and watchdog timer interrupt
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}


/*
  LED output
*/

//green LED state
void setGreenLED(int on)
{
  if (on) {
    P1OUT |= LED_GREEN;
  } else {
    P1OUT &= ~LED_GREEN;
  }
}


/*
  State machine: blinking
*/

//calling every 250th of a sec to blink green
void blinkUpdate() // called every 1/250s to blink with duty cycle 1/blinkLimit
{
  static int blinkCount = 0; // state var representing blink state
  blinkCount ++;
  if (blinkCount >= blinkLimit) {
    blinkCount = 0;
    setGreenLED(1);
  } else
    setGreenLED(0);
}


/*
  state machine: once per second
*/

// repeatedly start bright and gradually lower duty cycle, one step/sec
void oncePerSecond() 
{
  blinkLimit ++;  // reduce duty cycle
  if (blinkLimit >= 8)  // but don't let duty cycle go below 1/7.
    blinkLimit = 0;
}

// called every 1/250 sec to call oncePerSecond once per second
void secondUpdate() 
{
  static int secondCount = 0; // state variable representing repeating time 0…1s
  secondCount ++;
  if (secondCount >= 250) { // once each second
    secondCount = 0;
    oncePerSecond();
  } }


/*
  state machine controller
*/

// called every 1/250 sec
void timeAdvStateMachines() 
{
  blinkUpdate();
  secondUpdate();
}


/*
  interrupt handler
*/

//watchdog timer interrupt
void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking   
  timeAdvStateMachines();
} 

