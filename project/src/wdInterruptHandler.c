#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"

static char state=0;
static short tone_sequence[]={1000,1200,1400, 1600, 1800, 2000};
static int sequence_len=6;
static int index=0;
static int count=0;


void __interrupt_vec(WDT_VECTOR) WDT(){
  count++;
  if(count >=125){
    count=0;

    //switch cases based on button pressed
    switch(state){

    //solid red led
    case 0:
      set_red_led(1);
      set_green_led(0);
      buzzer_set_period(0);
      break;

    //tone when pressing button  
    case 1:
      set_red_led(0);
      set_green_led(1);
      buzzer_set_period(600);
      break;

    //sound sequence
    case 2:
      buzzer_set_period(tone_sequence[index]);
      set_red_led(index%2);
      set_green_led(!(index%2));
      index=(index+1) %sequence_len;
      break;
      
    //siren
    case 3:
      buzzer_set_period(1000+500*(index%10));
      set_red_led(1);
      set_green_led(1);
      index++;
      break;
    }
    led_update();
  }
}

void set_state(int new_state){
  state=new_state;
  index=0;
}

void advance_state(int temp){
  //placeholder
}
