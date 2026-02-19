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

BUILD := build

BIN := program.hex
ELF := $(BUILD)/program.elf

SOURCES := src/main.c src/lcd.c src/ClientManager.c src/Display.c src/utils.c src/clients_db.c
OBJS := $(patsubst src/%.c,$(BUILD)/%.o,$(SOURCES))

all: $(BIN)

$(BUILD):
	mkdir $(BUILD)

$(BUILD)/%.o: src/%.c | $(BUILD)
	$(COMPILE.c) -MD -o $@ $<

$(ELF): $(OBJS) | $(BUILD)
	$(CC) -Wl,-Map=$(BUILD)/program.map $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@

$(BIN): $(ELF)
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@

isp: ${BIN}
	$(OBJISP) -F -V -c arduino -p ${MCU} -P ${PORT} -U flash:w:$<

clean:
	@rm -f $(BIN) $(OBJS) $(ELF) $(BUILD)/*.map $(BUILD)/*.P $(BUILD)/*.d
