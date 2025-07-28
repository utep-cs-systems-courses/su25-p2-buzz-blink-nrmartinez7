//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

//functions
void updateGreenBlinking();
void updateRedBlinking();
void brightnessPattern();

//global vars
int greenLim=1;
int redLim=7;
int greenCount=0;
int redCount=0;
int secondCount=0; //state var representing repeating time 0..1s
int state=0;
int speed=1; 

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}


void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  updateGreenBlinking();
  updateRedBlinking();

  secondCount++;
  if(secondCount>=250*speed){
    secondCount=0;
    brightnessPattern();
  }
} 

void updateGreenBlinking(){
  greenCount++;
  if(greenCount >=greenLim){
    greenCount=0;
    P1OUT |=LED_GREEN;
  }else{
    P1OUT &= ~LED_GREEN;
  }
}

void updateRedBlinking(){
  redCount++;
  if(redCount >=redLim){
    redCount=0;
    P1OUT |=LED_RED;
  }else{
    P1OUT &= ~LED_RED;
  }
}

void brightnessPattern(){
  //dim to bright for green
  greenLim=(state%7)+1;

  //bright to dim for red
  redLim=8-greenLim;

  state++;
}

