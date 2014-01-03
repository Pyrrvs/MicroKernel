SOURCES=src/boot/boot.o src/boot/k_start.o src/io/lowlevel_io.o src/console/video_frame_buffer.o src/common/string.o src/common/stdio.o src/io/screen_io.o src/common/printk.o
CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -Isrc/ -std=gnu99
LDFLAGS=-Tsrc/link.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm -f src/boot/*.o src/console/*.o src/io/*.o src/kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
