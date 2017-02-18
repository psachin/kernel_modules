# Makefile for charater devices
obj-m += testCharDevice.o null-driver.o video-ram.o

KDIR=/lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean # from lkmpg 
	rm -rvf *~
