#include "nn/os/os_SimpleLock.h"

namespace nn{
namespace os{
// nonmatch
void SimpleLock::Initialize(void) {

s32* lock = &this->mCounter.mValue.mValueType;
volatile s32 val;

do {
        val = __ldrex(lock);
} while (__strex(1, lock));
}

void SimpleLock::Lock(){
}

void SimpleLock::LockImpl(){
}

bool SimpleLock::TryLock(){
}

void SimpleLock::Unlock(){
}

// end nonmatch
} // os
} // nn