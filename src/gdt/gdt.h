#include "../stdlib/stdint.h"
#include "../stdlib/stdutil.h"
struct gdt_entry_struct{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t flags;
    uint8_t base_high;
}__attribute__((packed));

struct gdt_pointer_struct{
    uint16_t limit;
    unsigned int base;
}__attribute__((packed));

void init_gdt();
void set_gdt_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

struct tss_entry_struct{
    uint32_t prev_tss;
   
    uint32_t esp0;
    uint32_t ss0;       
    
    uint32_t esp1;
    uint32_t ss1;
    
    uint32_t esp2;
    uint32_t ss2;
    
    uint32_t cr3;
    
    uint32_t eip;
    uint32_t eflags;
    
    uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
    
    uint32_t es, cs, ss, ds, fs, gs;
    
    uint32_t ldt;
    uint16_t trap;       
    uint16_t iomap_base;
} __attribute__((packed));

void writeTSS(uint32_t num, uint16_t ss0, uint32_t esp0);