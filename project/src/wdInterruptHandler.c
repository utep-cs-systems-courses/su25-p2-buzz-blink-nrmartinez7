#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"

//used for transitions
char state=0;
char next_state=0;

//used for leds
static int count=0;
static int led_dim=0;
static int led_bright=1;
static int dim_cycle=0;

//tone sequence
static short tone_sequence[]={
  293, 0, 311, 0,  329, 0, //D, Eb, E
  293, 0, 293, 0,  //D, D
  311, 0, 329, 0, //Eb, E
  261, 0, 293, 0,  //C, D
  261, 0, 293, 0,  //C, D
  261, 0,  //C
  466, 0, 440, 0,  //Bb, A
  392, 0, 349, 0 //G, F
};

static int index=0;
static int sequence_len=32;
static int tone_delay=0;

//changes state, resets index and counter
void set_state(int new_state){
  state=new_state;
  index=0;
  count=0;
}

//assembly transition
void advance_state(int next){
  extern void assy_trans();
  assy_trans();
}

//runs toy, checks state and updates leds and sound
void __interrupt_vec(WDT_VECTOR) WDT(){
  count++;

  //handles dimming
  if(++dim_cycle>=125){
    dim_cycle=0;
    led_dim= !led_dim;
  }

  switch(state){

  //bright red, no buzzer
  case 0:
    set_red_led(1);
    set_green_led(0);
    buzzer_set_period(0);
    break;

  //green, single tone  
  case 1:
    set_red_led(0);
    set_green_led(1);
    buzzer_set_period(900);
    break;

  //green-red alternating, tone sequence
  case 2:
    //red green alternating
    if(++tone_delay>=60){
      tone_delay=0;
      set_red_led(index%2);
      set_green_led(!(index%2));
      buzzer_set_period(tone_sequence[index]);
      index=(index+1)%sequence_len;
    }
    break;

  //dimming leds, siren
  case 3:
    set_red_led(led_dim);
    set_green_led(led_dim);

    buzzer_set_period(1000+500 *(index%10));
    index++;
    break;
  }
  led_update();
}

