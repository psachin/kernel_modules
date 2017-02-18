# Makefile for pen-driver.c
obj-m := pen-driver.o

KDIR=/lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean # from lkmpg 
	rm -rvf *~
