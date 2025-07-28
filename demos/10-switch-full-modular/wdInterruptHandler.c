#include <msp430.h>
#include "switches.h"
#include "led.h"

//track whether other LEDS are on during blinking
static char blink_state =0;

//watchdog timer interrupt
void __interrupt_vec(WDT_VECTOR) WDT(){
  static int blink_count=0;
  blink_count++;

  //toggle blink state
  if(blink_count >=125){
    blink_count=0;
    blink_state ^=1;

    //if blink state is on
    if(blink_state){

      //if button is pressed, green on, red off
      if(switch_state_down){
	set_green_led(1);
	set_red_led(0);
	
      //if button is not pressed, green off, red on
      }else{
	set_green_led(0);
	set_red_led(1);
      }

    //if blink state is off, green off, red on (solid)
    }else{
      set_green_led(0);
      set_red_led(1);
    }

    //update leds on board
    led_update();
  }
}

