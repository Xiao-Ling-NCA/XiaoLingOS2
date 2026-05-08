#include "stdlib/stdio.h"
#include "stdlib/stdint.h"
#include "gdt/gdt.h"

void kmain(){
    init_gdt();
    print("GDT Initialized with TSS segment!");

    return;
}