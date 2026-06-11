
CC=arm-none-eabi-gcc
CFLAGS=-mcpu=cortex-m4 -mthumb --specs=nano.specs
CPPFLAGS=-DSTM32F405xx \
				 -Ivendor/CMSIS/Device/ST/STM32F4/Include \
				 -Ivendor/CMSIS/CMSIS/Core/Include

LINKER_FILE=linker_script.ld
LDFLAGS=-T $(LINKER_FILE) -u _printf_float

BINARY = blink.elf

PROGRAMMER = openocd
PROGRAMMER_FLAGS = -f interface/stlink.cfg -f target/stm32f4x.cfg

all: $(BINARY)

$(BINARY): startup.o system_stm32f4xx.o syscalls.o usart.o esc_pwm_init.o esc_pwm_main.o ir_init.o ir_timer_init.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $(BINARY) 

startup.o: startup.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -c

system_stm32f4xx.o: vendor/CMSIS/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -c

syscalls.o: syscalls.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -c

esc_pwm_init.o: esc_pwm_init.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -c

esc_pwm_main.o: esc_pwm_main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -c

uart.o: uart.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -c

ir_init.o: ir_init.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -c

ir_timer_init.o: ir_timer_init.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -c

.PHONY: clean
clean:
	del /Q *.o *.elf

flash: $(BINARY)
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program $(BINARY) verify reset exit"


	