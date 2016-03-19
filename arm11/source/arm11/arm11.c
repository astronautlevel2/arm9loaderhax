#include <inttypes.h>

void __attribute__ ((naked)) a11Entry(void)
{
    __asm__ (
        "CPSID aif\n\t"
        "ldr r0,=_stack\n\t"
        "mov sp, r0"
    );

    volatile uint32_t *entry = (uint32_t *)0x1FFFFFF8;

    // Reset the entry
    *entry = 0;

    // Wait for entry to be set
    while(!*entry);
    // Jump
    ((void (*)())*entry)();
}