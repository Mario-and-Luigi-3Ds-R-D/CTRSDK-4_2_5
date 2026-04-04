#include "nn/util/detail/util_Symbol.h"


/* The RO System Uses this. Refers a func symbol for "nn::ro" */

__asm void nnutilReferSymbol_(const char*){
    ldr lr,[r0,#34]
    add r1,r0,#38
    ldmia r1,{r2,r3}
    stmdb lr,{r2,r3}
    ldmia r0,{r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12}
    mov sp,lr
    ldmia sp,{lr,pc}
}

/* This one makes 0 Sense, so I didn't do it. */