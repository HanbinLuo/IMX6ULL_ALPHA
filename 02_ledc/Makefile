objs := start.o main.o

all:ledc.bin

ledc.bin:$(objs)
	arm-linux-gnueabihf-ld -T imx6ul.lds -o ledc.elf $^
	arm-linux-gnueabihf-objcopy -O binary -S ledc.elf $@
	arm-linux-gnueabihf-objdump -D -m arm ledc.elf > ledc.dis

# ledc1.bin:$(objs)
# 	arm-linux-gnueabihf-ld -Ttext 0X87800000 -o ledc.elf $^
# 	arm-linux-gnueabihf-objcopy -O binary -S ledc.elf $@
# 	arm-linux-gnueabihf-objdump -D -m arm ledc.elf > ledc.dis
	
%.o:%.s
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<
	
%.o:%.S
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<
	
%.o:%.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<
	
clean:
	rm -rf *.o ledc.bin ledc.elf ledc.dis
	
	
