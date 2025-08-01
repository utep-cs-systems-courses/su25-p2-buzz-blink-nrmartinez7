#makefile configuration
COMMON_OBJECTS= main.o led.o switches.o buzzer.o wdInterruptHandler.o assy.o
CPU		=msp430g2553
CFLAGS		=-mmcu=${CPU} -I. -I../h
LDFLAGS		=-L../lib -lTimer

#compile and assemble
CC		=msp430-elf-gcc
AS		=msp430-elf-as

all: toy.elf

toy.elf: ${COMMON_OBJECTS} ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<


assy.o: assy.s
	${AS} -mmcu=${CPU} -o $@ $<

load: toy.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
