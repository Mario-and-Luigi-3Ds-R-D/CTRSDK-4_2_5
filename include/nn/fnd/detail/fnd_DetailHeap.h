#pragma once

#include "nn/fnd/detail/fnd_DetailHeapHead.h"
#include "nn/fnd/fnd_ExpHeap.h"

#define NN_OS_EXPHEAP_ALLOC_DIR_FRONT 0
#define NN_OS_EXPHEAP_ALLOC_DIR_REAR  1
#define NN_OS_EXPHEAP_ALLOC_MODE_FIRST 0
#define NN_OS_EXPHEAP_ALLOC_MODE_NEAR 1

namespace nn{
namespace fnd{
namespace detail{
    typedef nn::fnd::detail::NNSiFndExpHeapHead* Heap;

    ushort SetGroupIDForHelp(Heap heap, ushort groupId); // 100%
    ushort SetAllocModeForHeap(Heap heap, ushort mode); // 100%
    bool UseMarginOfAlignmentForHeap(Heap heap, bool reuse); // 100%
    void* AllocFromHeap(Heap heap, size_t size, s32 alignment);  // ASM
    void* AllocUsedBlockFromFreeBlock(NNSiFndExpHeapHead* pEHHead, NNSiFndExpHeapMBlockHead* pMBHeadFree,void* mblock,u32 size,u16 direction); // ASM
    void FreeToHeap(Heap heap, void* p); // ASM
    Heap CreateHeap(Heap heapHandle, void* startAddr, u32 size, ushort optFlag); // ASM
    NNSiFndHeapHead* FindContainHeap(NNSFndList* pList, void* memBlock); // Should be 100% but unsure

    void NNSi_FndFinalizeHeap(NNSiFndHeapHead* pHeadHd); // ASM
    void NNSi_FndInitHeapHead(NNSiFndHeapHead *pHeapHd,u32 signature,void *heapStart,void *heapEnd,ushort optFlag); // 68%

    static bool sRootListInitialized = false;
    static NNSFndList sRootList;
}
}
}