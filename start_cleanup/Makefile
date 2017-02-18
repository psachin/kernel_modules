# Makefile for start_clean
obj-m := final.o
final-objs := startup.o cleanup.o

KDIR=/lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean # from lkmpg
	rm -rvf *~
