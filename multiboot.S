# -------------------------
# Multiboot2 HEADER (DATA)
# -------------------------
.section .multiboot
.align 8

header_start:
    .long 0xe85250d6
    .long 0
    .long header_end - header_start
    .long -(0xe85250d6 + 0 + (header_end - header_start))

    # framebuffer tag
    .align 8
    .short 5
    .short 0
    .long 20
    .long 1024
    .long 768
    .long 32

    # end tag
    .align 8
    .short 0
    .short 0
    .long 8

header_end:
.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:
# -------------------------
# CODE SECTION
# -------------------------
.section .text
.global _start
.extern kernel_main

_start: 
    cli
    mov $stack_top, %esp
    mov %esp, %ebp
    push %ebx
    push %eax
    call kernel_main
hang:
    cli
    hlt
    jmp hang
