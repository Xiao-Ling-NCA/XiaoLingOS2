#include "stdlib/stdio.h"
#include "stdlib/stdint.h"
#include "gdt/gdt.h"
#include "idt/idt.h"

void kmain(){
    init_gdt();
    print("GDT Initialized with TSS segment!\n");

    init_idt();
    print("IDT Initialized!\n");
    return;
}