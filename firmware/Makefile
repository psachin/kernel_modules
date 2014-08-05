# Makefile for m_firmware.c
ifneq ($(KERNELRELEASE),)
obj-m := m_firmware.o
else
KDIR=/usr/src/linux-headers-$(shell uname -r)

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


