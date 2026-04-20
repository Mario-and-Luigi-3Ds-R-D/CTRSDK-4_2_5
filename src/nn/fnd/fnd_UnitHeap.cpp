#include <nn/fnd/fnd_UnitHeap.h>

namespace nn{
namespace fnd{

UnitHeapBase::~UnitHeapBase() {     
    if (this->mFreeNode == 0) 
        return;
    this->mFreeNode = 0;
}

void UnitHeapBase::FreeV(void* p){
    p = this->mFreeNode;
    this->mFreeNode = (Node*)p;
    this->mCount--;
}

void* UnitHeapBase::GetStartAddress() const { 
    return reinterpret_cast<void*>(this->mAddr); 
}

size_t UnitHeapBase::GetTotalSize() const {
    return this->mSize; 
}

void UnitHeapBase::Dump() const {
}

bool UnitHeapBase::HasAddress(const void* addr) const {
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