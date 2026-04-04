#include "nn/os/os_SimpleLock.h"

namespace nn{
namespace os{
// nonmatch

// Most of these are written in ARM Assembly. A guide on using this function will be shown above it.
//
// This decision was made due to it making somewhat more sense, and because im Lazy.

__asm void SimpleLock::Initialize(void) {
    MOV             R1,#1
loc_120F44
    LDREX           R2, [R0]
    STREX           R3, R1, [R0]
    CMP             R3, #0
    BNE             loc_120F44
    BX              LR
}

__asm void SimpleLock::Lock(){
}

__asm void SimpleLock::LockImpl(){
}

bool SimpleLock::TryLock(){
}

void SimpleLock::Unlock(){
}

// end nonmatch
} // os
} // nn