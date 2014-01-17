CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Kernel)

SET(CMAKE_ASM_NASM_OBJECT_FORMAT "elf")

ENABLE_LANGUAGE(ASM_NASM)

INCLUDE_DIRECTORIES(src/)

SET(CMAKE_C_FLAGS "-march=i386 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -std=gnu99")
SET(CMAKE_C_LINK_FLAGS "-T${CMAKE_SOURCE_DIR}/src/link.ld -melf_i386")
SET(CMAKE_C_LINK_EXECUTABLE "/usr/bin/ld <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET>")

SET(ASM_SRCS src/boot/boot.s src/boot/gdt.s src/boot/idt.s src/boot/isr.s src/mm/paging.s)
SET(C_SRCS src/boot/kstart.c src/console/video_frame_buffer.c src/io/lowlevel_io.c src/io/screen_io.c
	src/common/printk.c src/common/stdio.c src/common/string.c src/common/stdlib.c src/boot/idt.c
	src/boot/isr.c src/boot/kpaging.c)

SET_PROPERTY(SOURCE ${ASM_SRCS} PROPERTY LANGUAGE ASM_NASM)

ADD_EXECUTABLE(kernel.bin ${ASM_SRCS} ${C_SRCS})