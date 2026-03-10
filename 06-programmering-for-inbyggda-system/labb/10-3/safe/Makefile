# Build: make
# Build debug: make MODE=debug
# Upload: avrdude -c usbasp -p m328p -U flash:w:main.hex
# or: make flash
# Clean: make clean

# ==============================
# USER SETTINGS
# ==============================

MCU      = atmega328p
F_CPU    = 16000000UL
TARGET   = main

PROGRAMMER = usbasp
PORT       = usb

# Build mode: make MODE=debug
MODE ?= release

# ==============================
# TOOLCHAIN
# ==============================

CC       = avr-gcc
OBJCOPY  = avr-objcopy
SIZE     = avr-size
AVRDUDE  = avrdude

# ==============================
# FLAGS
# ==============================

COMMON_FLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -DBAUD=9600 -Wall -Wextra -std=c11 -MMD -MP


ifeq ($(MODE),debug)
    OPT = -Og -g
else
    OPT = -Os
endif

CFLAGS  = $(COMMON_FLAGS) $(OPT) -I$(INC_DIR)
LDFLAGS = -mmcu=$(MCU) -Wl,-Map=build/$(TARGET).map

# ==============================
# FILE STRUCTURE
# ==============================

SRC_DIR    = src
BUILD_DIR  = build
INC_DIR = include

SRC  = $(wildcard $(SRC_DIR)/*.c)
OBJ  = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEP  = $(OBJ:.o=.d)

# ==============================
# BUILD RULES
# ==============================

all: $(BUILD_DIR)/$(TARGET).hex size

# Create build dir if missing
$(BUILD_DIR):
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(BUILD_DIR)/$(TARGET).elf: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

# Hex
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Size
size: $(BUILD_DIR)/$(TARGET).elf
	$(SIZE) $<

# Flash
flash: $(BUILD_DIR)/$(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p m328p -P $(PORT) -U flash:w:$<

# Clean
clean:
	if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

# Include dependencies
-include $(DEP)
