[bits 32]

section .data
    GDT_START:
        dq 0x0                  ;Null segment 
        dq 0x00CF9A000000FFFF   ;KERNEL CODE
        dq 0x00CF92000000FFFF   ;KERNEL DATA
        dq 0x00CFFA000000FFFF   ;USER CODE
        dq 0x00CFF2000000FFFF   ;USER DATA 
    Task_State_Segment:
        dq 0x0
    GDT_END:
        
    GDT_INFORMATION:
        dw (GDT_END-GDT_START)-1
        dd GDT_START

section .text
    global load_gdt
    load_gdt:


        ;load GDT
        lgdt [GDT_INFORMATION]

        ;set up control registers
        mov eax, cr0
        or eax, 1
        mov cr0, eax

        ;set up segment registers
        jmp 0x08:flush
    flush:
        ;set up registers
        mov ax, 0x10
        mov ds, ax
        mov ss, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        mov ax, 0x28
        ltr ax
        xor ax, ax ; task state segment initialization
        
        ret