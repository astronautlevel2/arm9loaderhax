rwildcard = $(foreach d, $(wildcard $1*), $(filter $(subst *, %, $2), $d) $(call rwildcard, $d/, $2))

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/3ds_rules

CC := arm-none-eabi-gcc
AS := arm-none-eabi-as
LD := arm-none-eabi-ld
OC := arm-none-eabi-objcopy

name := $(shell basename $(CURDIR))

dir_source := source
dir_build := build
dir_data := data

ASFLAGS := -mlittle-endian -mcpu=arm946e-s -march=armv5te
CFLAGS  := -Wall -Wextra -MMD -MP -marm $(ASFLAGS) -fno-builtin -std=c11 -Wno-main -O2 -flto -ffast-math -mthumb -mthumb-interwork
LDFLAGS := -nostartfiles

objects = $(patsubst $(dir_source)/%.s, $(dir_build)/%.o, \
          $(patsubst $(dir_source)/%.c, $(dir_build)/%.o, \
          $(call rwildcard, $(dir_source), *.s *.c)))

bundledobjects = $(dir_build)/arm11.bin.o

define bin2o
	bin2s $< | $(AS) -o $(@)
	echo "extern const u8" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"[];" >> $(dir_build)/bundled.h
	echo "extern const u32" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`_size";" >> $(dir_build)/bundled.h
endef

.PHONY: all
all: $(name).bin

.PHONY: clean
clean:
	@rm -rf $(dir_build) $(dir_data)

$(name).bin: $(dir_build)/$(name).elf
	$(OC) -S -O binary $< $@

$(dir_build)/$(name).elf: $(bundledobjects) $(objects)
	$(CC) $(LDFLAGS) -T linker.ld $(OUTPUT_OPTION) $^

$(dir_build)/%.bin.o: $(dir_data)/%.bin
	@mkdir -p "$(@D)"
	@$(bin2o)

$(dir_build)/%.o: $(dir_source)/%.c
	@mkdir -p "$(@D)"
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(dir_build)/%.o: $(dir_source)/%.s
	@mkdir -p "$(@D)"
	$(COMPILE.s) $(OUTPUT_OPTION) $<

$(dir_build)/fatfs/%.o: $(dir_source)/fatfs/%.c
	@mkdir -p "$(@D)"
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(dir_build)/fatfs/%.o: $(dir_source)/fatfs/%.s
	@mkdir -p "$(@D)"
	$(COMPILE.s) $(OUTPUT_OPTION) $<
include $(call rwildcard, $(dir_build), *.d)
