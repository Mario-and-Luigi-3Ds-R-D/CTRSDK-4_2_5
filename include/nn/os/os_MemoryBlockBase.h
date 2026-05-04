#pragma once

#include "nn/fnd/fnd_Intrusive.h"

namespace nn{
namespace os{
    class MemoryBlockBase : public nn::fnd::IntrusiveLinkedList<MemoryBlockBase>::Item{
    protected:
        void SetReadOnly(bool readOnly) {
            this->mReadOnly = readOnly; 
        }
    public:
        uptr mAddr;
        size_t mSize;
        bool mReadOnly;
        s8 rev[3];

        void SetAddressAndSize(uptr addr, size_t size){
            this->mAddr = addr;
            this->mSize = size;
        }
        uptr GetAddress() const { 
            return this->mAddr; 
        }
        size_t GetSize() const {
            return this->mSize; 
        }
        bool IsReadOnly() const {
            return this->mReadOnly; 
        }
    };

}
}


typedef union nnosMemoryBlockBase{

} nnosMemoryBlockBase;