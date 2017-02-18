# Makefile for module_param.c
# Makefile adopted from free-electrons slides on Kernel development
ifneq ($(KERNELRELEASE),)
obj-m := module-param.o
else
KDIR=/lib/modules/$(shell uname -r)/build

all: modules

modules:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
modules_install:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules_install
kernel_clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean # from lkmpg
clean: kernel_clean
	rm -rvf *~

endif


