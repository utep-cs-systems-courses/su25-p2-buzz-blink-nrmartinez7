#ifndef led_included
#define  led_included

#include <msp430.h>

#define LED_GREEN BIT0               // P1.0
#define LED_RED BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

void led_init();		/* initialize LEDs */
void led_update();		/* update leds */

// these are boolean flags
extern unsigned char leds_changed, green_led_state, red_led_state;

void set_red_led(char on);
void set_green_led(char on);

#endif
