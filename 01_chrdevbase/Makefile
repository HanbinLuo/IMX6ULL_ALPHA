KERNEL_DIR := /home/lhb/linux_learning/02_system_migration/nxp_linux/linux-imx-rel_imx_4.1.15_2.1.0_ga
CURRENT_PATH := $(shell pwd)
obj-m := chrdevbase.o
ccflags-y := -fno-pic

# 交叉编译设置
ARCH := arm
CROSS_COMPILE := arm-linux-gnueabihf-

# 检查交叉编译工具链
CHECK_CC := $(shell which $(CROSS_COMPILE)gcc)
ifeq ($(CHECK_CC),)
$(error "Cross compiler $(CROSS_COMPILE)gcc not found. Please install: sudo apt-get install gcc-arm-linux-gnueabihf")
endif

# 检查内核源码是否已配置
ifeq ($(wildcard $(KERNEL_DIR)/.config),)
$(error "Kernel not configured. Please run: cd $(KERNEL_DIR) && make ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) imx_v7_defconfig")
endif

all: modules

modules:
	@echo "Building for ARM architecture..."
	@echo "Using compiler: $(CROSS_COMPILE)gcc"
	make -C $(KERNEL_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(CURRENT_PATH) modules

clean:
	make -C $(KERNEL_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(CURRENT_PATH) clean

.PHONY: all modules clean