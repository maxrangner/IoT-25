CC := avr-gcc
LD := avr-ld
OBJCOPY := avr-objcopy

MCU := atmega328p

CFLAGS := -Wall -Wextra  -Wundef -pedantic \
		-Os -std=gnu99 -DF_CPU=16000000UL -mmcu=${MCU}
LDFLAGS := -mmcu=$(MCU)

BIN := program.hex
SOURCES := main.c
OBJS := $(SOURCES:.c=.o)

all: $(BIN)

%.o:%.c
	$(COMPILE.c) -MD -o $@ $<

%.elf: $(OBJS)
	$(CC) -Wl,-Map=$(@:.elf=.map) $(LDFLAGS) -o $@ $^

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@

clean:
	@rm -f $(BIN) $(OBJS) *.map *.P *.d
