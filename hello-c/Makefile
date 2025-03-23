CC      = arm-linux-gnueabihf-gcc
AS      = arm-linux-gnueabihf-as
CFLAGS  = -O2 -ggdb -Wall
LDFLAGS = -fno-stack-protector

objects	= hello.o

default: hello

.PHONY: default clean clobber

hello: $(objects)
	$(CC) -o $@ $^

hello.o: hello.c

%.o: %.c
	$(CC) -c $(CFLAGS) $(LDFLAGS) -o $@ $<

%.o: %.s
	$(AS) -o $@ $<

clean:
	rm -f $(objects) hello

qemu: hello
	qemu-arm -L /usr/arm-linux-gnueabihf ./hello