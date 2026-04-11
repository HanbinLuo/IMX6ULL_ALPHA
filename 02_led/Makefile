KERNEL_DIR := /home/lhb/linux_learning/02_system_migration/nxp_linux/linux-imx-rel_imx_4.1.15_2.1.0_ga
CURRENT_PATH := $(shell pwd)
obj-m := led.o
ccflags-y := -fno-pic

# 交叉编译设置
ARCH := arm
CROSS_COMPILE := arm-linux-gnueabihf-


all: modules ledApp

modules:
	@echo "Building for ARM architecture..."
	@echo "Using compiler: $(CROSS_COMPILE)gcc"
	make -C $(KERNEL_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(CURRENT_PATH) modules

clean:
	make -C $(KERNEL_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(CURRENT_PATH) clean

# 编译测试应用程序
ledApp: ledApp.c
	$(CROSS_COMPILE)gcc ledApp.c -o ledApp

.PHONY: all modules clean