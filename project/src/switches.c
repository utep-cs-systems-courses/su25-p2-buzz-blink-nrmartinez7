#include <msp430.h>
#include "switches.h"
#include "wdInterruptHandler.h"

int temp=0;

void switch_init(){
  P2REN |= BIT0| BIT1|BIT2|BIT3;
  P2OUT |= BIT0| BIT1|BIT2|BIT3;
  P2DIR &= ~(BIT0| BIT1|BIT2|BIT3);
  P2IE |= BIT0| BIT1|BIT2|BIT3;
  P2IES |= BIT0| BIT1|BIT2|BIT3;
  P2IFG &= ~(BIT0| BIT1|BIT2|BIT3);
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  //first button
  if(P2IFG & BIT0){
    set_state(0);
    P2IFG &= ~BIT0;
    advance_state(temp);

  //second button
  }else if(P2IFG &BIT1){
    set_state(1);
    P2IFG &= ~BIT1;
    advance_state(temp);


  //third button
  }else if(P2IFG &BIT2){
    set_state(2);
    P2IFG &= ~BIT2;
    advance_state(temp);
    
  //fourth button
  }else if(P2IFG &BIT3){
    set_state(3);
    P2IFG &= ~BIT3;
    advance_state(temp);
  }
}


    


