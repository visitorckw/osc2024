CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
AR = aarch64-linux-gnu-ar
OBJCOPY = aarch64-linux-gnu-objcopy
LINKER_SCRIPT = linker.ld
START = start

CFLAGS := -fno-stack-protector

all: kernel8.img

$(START).o: $(START).S
	$(CC) $(CFLAGS) -c $(START).S -o $(START).o

OBJS := \
	main.o \
	mbox.o \
	uart.o \
	shell.o \
	string.o \
	reset.o \

%.o: %.c
	$(CC) $(CFLAGS) -c $<

kernel8.img: $(START).o $(OBJS)
	$(LD) $(START).o $(OBJS) -T $(LINKER_SCRIPT) -o kernel8.elf
	$(OBJCOPY) -O binary kernel8.elf kernel8.img

clean:
	rm -f kernel8.elf kernel8.img *.o

run:
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial null -serial stdio
