CC := avr-gcc
LD := avr-ld
OBJCOPY := avr-objcopy
OBJISP := avrdude
AVRSIZE := avr-size
PORT := /dev/ttyACM0

MCU := atmega328p

CFLAGS := -Wall -Wextra  -Wundef -pedantic \
		-Os -std=gnu99 -DF_CPU=16000000UL -mmcu=${MCU} \
		-Iinclude
LDFLAGS := -mmcu=$(MCU)

BIN := program.hex
SOURCES := src/main.c src/lcd.c src/ClientManager.c src/Display.c src/utils.c
OBJS := $(SOURCES:.c=.o)

all: $(BIN)

%.o:%.c
	$(COMPILE.c) -MD -o $@ $<

%.elf: $(OBJS)
	$(CC) -Wl,-Map=$(@:.elf=.map) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@

isp: ${BIN}
	$(OBJISP) -F -V -c arduino -p ${MCU} -P ${PORT} -U flash:w:$<

clean:
	@rm -f $(BIN) $(OBJS) *.map *.P *.d
