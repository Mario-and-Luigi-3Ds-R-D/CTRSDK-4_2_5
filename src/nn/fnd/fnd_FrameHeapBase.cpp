#include <nn/fnd/fnd_FrameHeap.h>

namespace nn{
namespace fnd{

FrameHeapBase::~FrameHeapBase(){
    this->mAddr = 0;
}

void FrameHeapBase::FreeV(void* ptr){
}

void* FrameHeapBase::GetStartAddress() const{
    return reinterpret_cast<void*>(mAddr); 
}

size_t FrameHeapBase::GetTotalSize() const{
    return this->mSize; 
}

void FrameHeapBase::Dump() const{
}

bool FrameHeapBase::HasAddress(const void* addr) const{
    bool hasAddr;
    if(addr < (uint*)*(uptr*) this->mAddr){
        this->mSize + this->mAddr <= *(u64*)addr;
        hasAddr = 0;
    }
    else{
        hasAddr = true;
    }
    return hasAddr;
}
}
}