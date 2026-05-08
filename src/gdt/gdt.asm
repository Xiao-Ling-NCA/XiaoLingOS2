global gdt_flush
gdt_flush:
    mov eax, [esp + 4]
    lgdt [eax]
    mov eax, 10

    mov eax, cr0
    or eax, 1
    mov cr0, eax
    
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ;set up segment registers
    jmp 0x08:flush
flush:
    ;set up registers
    
    ret

global tss_flush
tss_flush:
    mov ax, 0x2B
    ltr ax
    ret