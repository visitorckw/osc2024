QEMU_OPTS = -initrd ../initramfs.cpio -dtb ../bcm2710-rpi-3-b-plus.dtb

.PHONY: all kernel run-kernel clean

all: kernel

kernel:
	$(MAKE) -C kernel LIB_PATH=$(CURDIR)/lib BSP_PATH=$(CURDIR)/bsp

run-kernel:
	$(MAKE) -C kernel run QEMU_OPTS="$(QEMU_OPTS)"

clean:
	$(MAKE) -C kernel clean
