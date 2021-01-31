

SOURCE_C_LIST= \
src/main.c \
src/handlers.c 


SOURCE_S_LIST= \
src/startup_code.s


OBJECT_LISTS= 
OBJECT_LISTS+= $(addprefix build/, $(notdir $(SOURCE_C_LIST:.c=.o)))
OBJECT_LISTS+= $(addprefix build/, $(notdir $(SOURCE_S_LIST:.s=.o)))

DEBUG= -g -gdwarf-2 -fdebug-prefix-map==../


all: build/program.elf build/program.hex

build/program.hex: build/program.elf
	arm-none-eabi-objcopy.exe -O ihex $(<) $(@)
	
build/program.elf: $(OBJECT_LISTS) makefile
	arm-none-eabi-ld.exe -T linker_script.ld -o $(@) $(OBJECT_LISTS)
	

build/%.o: src/%.s makefile | build
	arm-none-eabi-gcc.exe -c -x assembler -mcpu=cortex-m3 -mthumb $(DEBUG) -o $(@) $(<)
	
build/%.o: src/%.c makefile | build
	arm-none-eabi-gcc.exe -c -mcpu=cortex-m3 -mthumb -MMD -MP  -Iinc $(DEBUG) -o $(@) $(<)		


build:
	mkdir build
	
clean:
	rm -rf build	


-include $(wildcard build/*.d)


