#include "stdint.h"
#pragma once
void memset(void *dest, uint32_t value, uint32_t count);
void outPortB(uint16_t port, uint8_t value);

struct InterruptRegisters{
    uint32_t cr2;
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, csm, eflags, useresp, ss;
}__attribute__((packed));