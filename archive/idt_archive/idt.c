#include "idt.h"

//All of this is for the ISR handling
extern void* isr_stub_table[];

const uint32_t IDT_MAX_DESCRIPTORS = 32;

static idt_entry_t idt[256];
static idtr_t idtr;
static boolean vectors[IDT_MAX_DESCRIPTORS];

unsigned char* interrupt_message[IDT_MAX_DESCRIPTORS]={
    "Divide Error",
    "Debug Exceptions",
    "NMI Interrupt",
    "Breakpoint",
    "INTO Detected Overflow",
    "BOUND Range Exceeded",
    "Invalid Opcode",
    "Coprocessor Not Available",
    "Double Exception",
    "Coprocessor Segment Overrun",
    "Invalid Task State Segment",
    "Segment Not Present",
    "Stack Fault",
    "General Protection",
    "Page Fault",
    "(reserved)",
    "Coprocessor Error",
    "(reserved)",
    "(reserved)",
    "(reserved)",
    "(reserved)",
    "(reserved)",
    "(reserved)",
    "(reserved)",
    "(reserved)",
    "(reserved)",
    "(reserved)",
    "(reserved)",
    "(reserved)",
    "(reserved)",
    "(reserved)",
    "(reserved)",
    "(reserved)"
};

void idt_set_descriptor(uint8_t entry, void* isr, uint8_t flags);
__attribute__((noreturn)) void exception_handler(void);
void idt_init(void);

void exception_handler() {
    __asm__ volatile ("cli; hlt");
}

void idt_set_descriptor(uint8_t entry, void* isr, uint8_t flags){
    idt_entry_t* descriptor = &idt[entry];
    
    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08; //kernel code segment data
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
    
    descriptor->reserved       = 0;
    
    return;
}

void init_idt(){
    idtr.base = (uint32_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}