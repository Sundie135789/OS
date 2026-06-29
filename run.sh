#!/bin/bash
i686-elf-gcc -c kernel.c -o kernel.o -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c framebuffer.c -o framebuffer.o -ffreestanding -O2 -Wall -Wextra
i686-elf-as multiboot.S -o multiboot.o

i686-elf-gcc -T linker.ld -o kernel.bin \
  -ffreestanding -O2 -nostdlib \
  multiboot.o kernel.o framebuffer.o -lgcc

mkdir -p iso/boot/grub
cp kernel.bin iso/boot/
cp grub/grub.cfg iso/boot/grub/

grub-mkrescue -o myos.iso iso
qemu-system-i386 -cdrom myos.iso -display sdl
