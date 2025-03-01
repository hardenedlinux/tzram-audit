obj-m = tzram_test.o smram_test.o
CC = gcc
PWD=$(shell pwd)

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	gcc -o userland_physmap userland_physmap.c

clean:
	rm -rf *.o *.ko Module.* modules.* *.mod.c .* *~ *.mod userland_physmap
