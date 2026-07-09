.section .multiboot2
.align 8

# header start
.long 0xe85250d6              # magic
.long 0                      # architecture
.long header_end - header_start
.long -(0xe85250d6 + 0 + (header_end - header_start))

header_start:

# framebuffer tag
.align 8
.short 5                     # type = framebuffer
.short 0
.long 20                     # size
.long 640                   # width
.long 480                    # height
.long 32                     # depth

# end tag
.align 8
.short 0
.short 0
.long 8

header_end:

.section .text
.global _start

_start:
    mov %ebx, %eax   # multiboot info pointer → eax
    push %eax
    call kernel_main

hang:
    cli
    hlt
    jmp hang
