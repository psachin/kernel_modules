# Makefile for charater devices
obj-m += testCharDevice.o
obj-m += null-driver.o
obj-m += video-ram.o

KDIR=/usr/src/linux-headers-$(shell uname -r)

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean # from lkmpg 
	rm -rvf *~
