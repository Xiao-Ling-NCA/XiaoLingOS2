#include "../stdlib/stdint.h"
typedef struct{
    uint16_t isr_low;
    uint16_t kernel_cs;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t isr_high;
}__attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idtr_t;

typedef struct{
    
}__attribute__((packed)) InterruptRegisters;

void init_idt(void);