#ifndef switches_included
#define switches_included
#define SWITCHES (BIT0|BIT1|BIT2|BIT3)

void switch_init();
void switch_interrupt_handler();

extern char switch_state_down;

#endif
