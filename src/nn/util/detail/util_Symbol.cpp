#include "nn/util/detail/util_Symbol.h"


/* The RO System Uses this. Refers a func symbol for "nn::ro" */

__asm void nnutilReferSymbol_(const char*){
    bx lr
}

/* This one makes 0 Sense, so I didn't do it. */