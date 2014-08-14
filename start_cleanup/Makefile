# Makefile for start_clean
obj-m := final.o
final-objs := startup.o cleanup.o

KDIR=/usr/src/linux-headers-$(shell uname -r)

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean # from lkmpg
	rm -rvf *~
