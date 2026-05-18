// Filename: os_AddressSpaceManager.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/os/os_AddressSpaceManager.h>
#include <nn/os/os_CriticalSection.h>
#include <nn/fnd/fnd_Intrusive.h>
#include <nn/dbg/dbg_Break.h>

namespace nn{
namespace os{
uptr AddressSpaceManager::Allocate(MemoryBlockBase* pBlock, size_t size, size_t skipSize){
    #ifdef NN_DEBUG
        if(pBlock == 0){
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"os_AddressSpaceManager.cpp",16,"%s must not be NULL","pBlock");
        }
        if((size & 0xfff) != 0){
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"os_AddressSpaceManager.cpp",19,"%s(=0x%08x) must be %d byte aligned","size",size,0x1000);
        }
        if((skipSize & 0xfff) != 0){
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"os_AddressSpaceManager.cpp",22,"%s(=0x%08x) must be %d byte aligned","skipSize",skipSize,0x1000);
        }
    #endif
    Lock::ScopedLock scopedLock(mLock);

    MemoryBlockBase* pPrev = FindSpace(size, skipSize);
    uptr allocatedAddress;

    if(pPrev != NULL){
        allocatedAddress = pPrev->GetAddress() + pPrev->GetSize() + skipSize;
        MemoryBlockBase* pNext = mBlockList.GetNext(pPrev);

        if(pNext != NULL){
            mBlockList.Insert(pNext, pBlock);
        }
        else{
            mBlockList.PushBack(pBlock);
        }
    }
    else{
        allocatedAddress = mSpaceBegin;
        MemoryBlockBase* pNext = mBlockList.GetFront();

        if(pNext != NULL){
            const uptr allocatedEnd = allocatedAddress + size;
            const uptr nextBegin    = pNext->GetAddress();

            if(nextBegin < allocatedEnd + skipSize){
                return NULL;
            }

            mBlockList.Insert(pNext, pBlock);
        }
        else{
            const uptr allocatedEnd = allocatedAddress + size;

            if(mSpaceEnd < allocatedEnd){
                return NULL;
            }
            mBlockList.PushBack(pBlock);
        }
    }

    pBlock->SetAddressAndSize(allocatedAddress, size);
    return allocatedAddress;
}


MemoryBlockBase* AddressSpaceManager::FindSpace(size_t size, size_t skipSize){
    MemoryBlockBase* pItem = mBlockList.GetBack();
    uptr end = mSpaceEnd;

    while(pItem != NULL){
        const uptr nextBegin = pItem->GetAddress();
        const uptr nextEnd   = nextBegin + pItem->GetSize();
        const size_t spaceSize = end - nextEnd;
        if(spaceSize >= size + skipSize){
            return pItem;
        }

        end = nextBegin - skipSize;
        pItem = mBlockList.GetPrevious(pItem);
    }
    return NULL;
}

void AddressSpaceManager::Free(MemoryBlockBase *pBlock){
    Lock::ScopedLock scopedLock(mLock);

    mBlockList.Erase(pBlock);
    pBlock->SetAddressAndSize(NULL, 0);
}

void AddressSpaceManager::Switch(MemoryBlockBase *pTo,MemoryBlockBase *pFrom){
    Lock::ScopedLock scopedLock(mLock);

    pTo->SetAddressAndSize(pFrom->GetAddress(), pFrom->GetSize());
    mBlockList.Insert(pFrom, pTo);

    pFrom->SetAddressAndSize(NULL, 0);
    mBlockList.Erase(pFrom);
}

void AddressSpaceManager::Initialize(uptr begin, size_t size){
    if (mSpaceBegin == 0 && mSpaceEnd == 0){
        mLock.Initialize();
        
        mSpaceBegin = begin;
        mSpaceEnd   = begin + size;
    }
}

}
}

using namespace nn::os;

// TODO: Remake these.

extern "C" {

void nnosAddressSpaceManagerInitialize(nnosAddressSpaceManager* p, uptr begin, size_t size){
    AddressSpaceManager* pThis = new (p) AddressSpaceManager();
    pThis->Initialize(begin, size);
}

// Pointer to -> AddressSpaceMan::Switch
void nnosAddressSpaceManagerSwitch(nnosAddressSpaceManager* p, nnosMemoryBlockBase* p2, nnosMemoryBlockBase* p3){
    nn::os::AddressSpaceManager* pThis = reinterpret_cast<nn::os::AddressSpaceManager*>(p);
    nn::os::MemoryBlockBase* pTo = reinterpret_cast<nn::os::MemoryBlockBase*>(p2);
    nn::os::MemoryBlockBase* pFrom = reinterpret_cast<nn::os::MemoryBlockBase*>(p3);
    pThis->Switch(pTo, pFrom);
}

}