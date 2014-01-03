SOURCES=src/boot/boot.o src/boot/k_start.o src/io/lowlevel_io.o src/console/console.o
CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -Isrc/
LDFLAGS=-Tsrc/link.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm -f src/boot/*.o src/console/*.o src/io/*.o src/kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
