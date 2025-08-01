//handles input from buttons (P2.0-P2.3)

#include <msp430.h>
#include "switches.h"
#include "wdInterruptHandler.h"

//init buttons
void switch_init(){
  P2REN |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  P2IE |= SWITCHES;
  P2IES |= SWITCHES;
  P2IFG &= ~SWITCHES;
}


/*
  runs when interrupted by button
  1. sets next state
  2. clears interrupt flag,
  3. calls advance_state(0) (assembly file that handles state transitions)
*/
void __interrupt_vec(PORT2_VECTOR) Port_2(){
  //first button
  if(P2IFG & BIT0){
    next_state=0;
    advance_state(0);
    P2IFG &= ~BIT0;

  //second button
  }else if(P2IFG &BIT1){
    next_state=1;
    advance_state(0);
    P2IFG &= ~BIT1;


  //third button
  }else if(P2IFG &BIT2){
    next_state=2;
    advance_state(0);
    P2IFG &= ~BIT2;
    
  //fourth button
  }else if(P2IFG &BIT3){
    next_state=3;
    advance_state(0);
    P2IFG &= ~BIT3;
  }
}


    


