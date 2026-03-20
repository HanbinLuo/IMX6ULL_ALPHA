objs := start.o main.o

all:ledc_stm32.bin

ledc_stm32.bin:$(objs)
	arm-linux-gnueabihf-ld -T imx6ul.lds -o ledc_stm32.elf $^
	arm-linux-gnueabihf-objcopy -O binary -S ledc_stm32.elf $@
	arm-linux-gnueabihf-objdump -D -m arm ledc_stm32.elf > ledc_stm32.dis

	
%.o:%.s
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<
	
%.o:%.S
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<
	
%.o:%.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<
	
clean:
	rm -rf *.o ledc.bin ledc.elf ledc.dis
	
	
