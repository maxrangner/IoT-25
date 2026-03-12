# Build: make
# Build debug: make MODE=debug
# Upload: make flash
# Clean: make clean

# ==============================
# USER SETTINGS
# ==============================

MCU      = atmega328p
F_CPU    = 16000000UL
TARGET   = main

PROGRAMMER = usbasp
PORT       = usb

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

COMMON_FLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Wall -Wextra -std=c11 -MMD -MP -Iinclude

ifeq ($(MODE),debug)
    OPT = -Og -g
else
    OPT = -Os
endif

CFLAGS  = $(COMMON_FLAGS) $(OPT)
LDFLAGS = -mmcu=$(MCU) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

# ==============================
# FILE STRUCTURE
# ==============================

SRC_DIR   = src
BUILD_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

# ==============================
# BUILD RULES
# ==============================

all: $(BUILD_DIR)/$(TARGET).hex size

# Create build dir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

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
	rm -rf $(BUILD_DIR)

# Include dependencies
-include $(DEP)
