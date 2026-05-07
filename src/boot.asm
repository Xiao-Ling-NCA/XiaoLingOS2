[bits 32]
section .text
global _start
_start:
    align 4
    dd 0x1BADB002
    dd 0x00000000

    dd -(0x1BADB002 + 0x00000000)
global start
extern kmain
start:
    cli
    mov esp, stack_space
    call kmain

halt_kernel:
    hlt
    jmp $

section .bss
resb 8192 ;8kb stack

stack_space: