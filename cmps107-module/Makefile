# Makefile for the cmps107 module
#
# Note: You can override the build directory by specifying BUILD on the
# command line:
#
# make BUILDPATH=...
#
# NOTE!!! If you've compiled your own kernel, you must override BUILDPATH
# and supply the path to its build directory
#
# After building the kernel module, copy the resulting *.ko file into the
# "initramfs" directory and run ./create-initramfs to generate a new
# filesystem image for the kernel to boot into. If done successfully, you
# should see the cmps107.ko module in the root directory of the filesystem
# when you boot your kernel with qemu.
#
# To load your module after booting your kernel, run:
#
# insmod cmps107.ko
#
# To check if the module has loaded, run `lsmod'
#
BUILDPATH := /lib/modules/$(shell uname -r)/build
obj-m += cmps107.o

all:
	make -C $(BUILDPATH) M=$(PWD) modules

clean:
	make -C $(BUILDPATH) M=$(PWD) clean
