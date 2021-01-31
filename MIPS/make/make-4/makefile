
PROGRAM = program

SOURCE_S_LIST = \
startup_code.s

SOURCE_C_LIST = \
main.c \
systick.c

OBJECTS_LIST =
OBJECTS_LIST += $(SOURCE_S_LIST:.s=.o)
OBJECTS_LIST += $(SOURCE_C_LIST:.c=.o)


CC = arm-none-eabi-gcc.exe -c
AS = arm-none-eabi-gcc.exe -c -x assembler
LD = arm-none-eabi-ld.exe
HX = arm-none-eabi-objcopy.exe -O ihex

MCU = -mcpu=cortex-m3 -mthumb

FLAGS_AS =
FLAGS_AS +=$(MCU)

FLAGS_CC =
FLAGS_CC += $(MCU)

LINKER_SCRIPT = linker_script.ld

FLAGS_CC += -MMD -MP


all : $(PROGRAM).hex $(PROGRAM).elf
	
$(PROGRAM).hex : $(PROGRAM).elf
	$(HX) $(<) $(@)

$(PROGRAM).elf : $(OBJECTS_LIST) makefile
	$(LD) -T $(LINKER_SCRIPT) -o $(@) $(OBJECTS_LIST)


%.o : %.s makefile
	$(AS)  $(FLAGS_AS) -o $(@) $(<)

%.o : %.c makefile
	$(CC) $(FLAGS_CC) -o $(@) $(<)
	
-include $(wildcard ./*.d)