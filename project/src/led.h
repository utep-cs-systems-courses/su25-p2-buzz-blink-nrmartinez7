#ifndef led_included
#define led_included

#define LED_GREEN BIT0 //P1.0
#define LED_RED BIT6 //P1.6
#define LEDS (BIT0|BIT6)

void led_init();
void led_update();
void set_red_led(char on);
void set_green_led(char on);

#endif //included
