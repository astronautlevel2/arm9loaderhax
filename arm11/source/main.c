#include "types.h"

void main(void)
{
   vu32 *const arm11 = (u32 *)0x1FFFFFF8;

   //Clear ARM11 entry offset
   *arm11 = 0;

   //Wait for the entry to be set
   while(!*arm11);

   //Jump to it
   ((void (*)())*arm11)();
}