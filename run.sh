#!/bin/bash
set -e
rm -rf iso
rm -f *.o kernel.bin mykernel.iso
i686-elf-gcc -c boot.s -o boot.o
i686-elf-gcc -ffreestanding -c kernel.c -o kernel.o
i686-elf-gcc -ffreestanding -c framebuffer.c -o  framebuffer.o

i686-elf-ld -T linker.ld -o kernel.bin boot.o kernel.o framebuffer.o 
mkdir -p iso/boot/grub
cp kernel.bin iso/boot/
cat > iso/boot/grub/grub.cfg << EOF
  menuentry "i386 kernel" {
    multiboot2 /boot/kernel.bin
    boot
  }
EOF
grub-mkrescue -o mykernel.iso iso/
qemu-system-i386 -cdrom mykernel.iso -display sdl,gl=on -full-screen
