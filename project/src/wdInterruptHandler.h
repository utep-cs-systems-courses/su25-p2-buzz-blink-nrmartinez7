#ifndef wdInterruptHandler_included
#define wdInterruptHandler_included

void set_state(int new_state);
void advance_state(int next);
extern char next_state;

#endif
