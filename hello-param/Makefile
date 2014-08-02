# Makefile for hello-param.c
# Makefile adopted from free-electrons slides on Kernel development
ifneq ($(KERNELRELEASE),)
obj-m := hello-param.o
else
KDIR=/usr/src/linux-headers-$(shell uname -r)

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean # from lkmpg 
	rm -rvf *~
endif


