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
    mov esp, stack_top
    call kmain

halt_kernel:
    hlt
    jmp $

section .bss

stack_bottom:
resb 8192 ;8kb stack
global stack_top
stack_top: