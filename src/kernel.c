#include "stdlib/stdio.h"
#include "stdlib/stdint.h"

extern void load_gdt(void);
void kmain(void);

void kmain(){
    print("did this work chat\n");
    load_gdt();
    print("GDT is loaded!\n");
    print("blah blah blah");

    return;
}