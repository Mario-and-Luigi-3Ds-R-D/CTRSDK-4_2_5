#include <nn/fnd/detail/fnd_DetailHeap.h>
#include <nn/fnd/detail/fnd_DetailList.h>
#include <nn/fnd/detail/fnd_DetailCommon.h>

#define MBLOCK_FREE_SIGNATURE ('FR')

#define MIN_FREE_BLOCK_SIZE 4

namespace nn{
namespace fnd{
namespace detail{

typedef struct NNSiMemRegion NNSiMemRegion;

struct NNSiMemRegion{
    void*       start;
    void*       end;
};

/* Static Inlines n Shit */
/*
static inline void* GetMBlockEndAddr(NNSiFndExpHeapMBlockHead* pMBHead){
    return AddU32ToPtr(GetMemPtrForMBlock(pMBHead), pMBHead->blockSize);
}

static inline void* GetMemPtrForMBlock(NNSiFndExpHeapMBlockHead* pMBlkHd){
    return AddU32ToPtr(pMBlkHd, sizeof(NNSiFndExpHeapMBlockHead));
}

static inline u16 GetAlignmentForMBlock(const NNSiFndExpHeapMBlockHead* pMBlkHd){
    return (u16)NNSi_FndGetBitValue(pMBlkHd->attribute, 8, 7);
}

static inline NNSiFndExpHeapMBlockHead* InitFreeMBlock(const NNSiMemRegion* pRegion){
    return InitMBlock(pRegion, MBLOCK_FREE_SIGNATURE);
}

static NNSiFndExpHeapMBlockHead* InitMBlock(const NNSiMemRegion* pRegion,u16 signature){
    NNSiFndExpHeapMBlockHead* block = reinterpret_cast<NNSiFndExpHeapMBlockHead*>(pRegion->start);

    block->signature = signature;
    block->attribute = 0;
    block->blockSize = GetOffsetFromPtr(GetMemPtrForMBlock(block), pRegion->end);
    block->pMBHeadPrev = NULL;
    block->pMBHeadNext = NULL;

    return block;
}

static NNSiFndExpHeapMBlockHead* RemoveMBlock(NNSiFndExpMBlockList* list,NNSiFndExpHeapMBlockHead* block){
    NNSiFndExpHeapMBlockHead *const prev = block->pMBHeadPrev;
    NNSiFndExpHeapMBlockHead *const next = block->pMBHeadNext;

    if (prev){
        prev->pMBHeadNext = next;
    }
    else{
        list->head = next;
    }

    if (next){
        next->pMBHeadPrev = prev;
    }
    else{
        list->tail = prev;
    }

    return prev;
}

static NNSiFndExpHeapMBlockHead* InsertMBlock(NNSiFndExpMBlockList* list,NNSiFndExpHeapMBlockHead* target, NNSiFndExpHeapMBlockHead* prev){
    NNSiFndExpHeapMBlockHead* next;

    target->pMBHeadPrev = prev;
    if (prev){
        next = prev->pMBHeadNext;
        prev->pMBHeadNext = target;
    }
    else{
        next = list->head;
        list->head = target;
    }

    target->pMBHeadNext = next;
    if (next){
        next->pMBHeadPrev = target;
    }
    else{
        list->tail = target;
    }
    return target;
}
*/
/* Funcs */



ushort SetGroupIDForHelp(Heap heap, ushort groupId){
    ushort setGroupId;
    NNSiFndExpHeapHead* pEHHead;

    setGroupId = heap->groupID;
    heap->groupID = groupId;
    return setGroupId;
}

ushort SetAllocModeForHeap(Heap heap, ushort mode){
    ushort allocMode = heap->feature;
    heap->feature = mode & 1 | allocMode & 0xfffe;
    return allocMode & 1;
}

bool UseMarginOfAlignmentForHeap(Heap heap, bool reuse){
    bool isReuse = heap->reuse;
    heap->reuse = reuse;
    return isReuse;
}
/*
static void GetRegionOfMBlock(NNSiMemRegion* region,NNSiFndExpHeapMBlockHead* block){
    region->start = SubU32ToPtr(block, GetAlignmentForMBlock(block));
    region->end = GetMBlockEndAddr(block);
}*/

/* Allocation */

void* AllocUsedBlockFromFreeBlock(NNSiFndExpHeapHead* pEHHead, NNSiFndExpHeapMBlockHead* pMBHeadFree,void* mblock,u32 size,u16 direction){
/*    NNSiMemRegion freeRgnT;
    NNSiMemRegion freeRgnB;
    NNSiFndExpHeapMBlockHead* pMBHeadFreePrev;

    GetRegionOfMBlock(&freeRgnT, pMBHeadFree);
    freeRgnB.end   = freeRgnT.end;
    freeRgnB.start = AddU32ToPtr(mblock, size);
    freeRgnT.end   = SubU32ToPtr(mblock, sizeof(NNSiFndExpHeapMBlockHead));

    pMBHeadFreePrev = RemoveMBlock(&pEHHead->mbFreeList, pMBHeadFree);  // delete the free block for the time being

    if ((GetOffsetFromPtr(freeRgnT.start, freeRgnT.end) < sizeof(NNSiFndExpHeapMBlockHead) + MIN_FREE_BLOCK_SIZE) ||
       (direction == NN_OS_EXPHEAP_ALLOC_DIR_FRONT && !pEHHead->reuse)){
        freeRgnT.end = freeRgnT.start;
    }
    else{
        pMBHeadFreePrev = InsertMBlock(&pEHHead->mbFreeList, InitFreeMBlock(&freeRgnT), pMBHeadFreePrev);
    }

    if ((GetOffsetFromPtr(freeRgnB.start, freeRgnB.end) < sizeof(NNSiFndExpHeapMBlockHead) + MIN_FREE_BLOCK_SIZE) ||
       (direction == NN_OS_EXPHEAP_ALLOC_DIR_REAR && !pEHHead->reuse)){
        freeRgnB.start= freeRgnB.end;
    }
    else{
        (void)InsertMBlock(&pEHHead->mbFreeList, InitFreeMBlock(&freeRgnB), pMBHeadFreePrev);
    }

    FillAllocMemory(GetHeapHeadPtrFromHeapHead(pEHHead), freeRgnT.end, GetOffsetFromPtr(freeRgnT.end, freeRgnB.start));
    {
        NNSiFndExpHeapMBlockHead* pMBHeadNewUsed;
        NNSiMemRegion region;

        region.start = SubU32ToPtr(mblock, sizeof(NNSiFndExpHeapMBlockHead));
        region.end   = freeRgnB.start;

        pMBHeadNewUsed = InitMBlock(&region, MBLOCK_USED_SIGNATURE);
        SetAllocDirForMBlock(pMBHeadNewUsed, direction);
        SetAlignmentForMBlock(pMBHeadNewUsed, (u16)GetOffsetFromPtr(freeRgnT.end, pMBHeadNewUsed));
        SetGroupIDForMBlock(pMBHeadNewUsed, pEHHead->groupID);
        AppendMBlock(&pEHHead->mbUsedList, pMBHeadNewUsed);
    }

    return mblock;
*/
}

// ASM AllocFromHeap
// Allocates from the current expanded heap.
//
// Paramaters: nn::fnd::Heap heap, size_t size(heap size), s32 alignment(heap alignment)

__asm void* AllocFromHeap(Heap heap, size_t size, s32 alignment){
    PUSH            {R3-R11,LR}
    CMP             R1, #0
    MOVEQ           R1, #1
    MOV             R5, #1
    ADD             R1, R1, #3
    LDRH            R12, [R0,#0x36]
    CMP             R2, #0
    MOV             R10, #0
    BIC             R3, R1, #3
    BIC             R7, R5, R12
    BLT             loc_132C6C
    LDR             R12, [R0,#0x24]!
    MOV             R1, #0
    MOV             R6, #0xFFFFFFFF
    CMP             R12, #0
    MOV             R8, R1
    SUBNE           R9, R2, #1
    BEQ             loc_132CF4

loc_132BFC
    ADD             R5, R12, #0x10
    ADD             LR, R5, R2
    SUB             R4, LR, #1
    LDR             LR, [R12,#4]
    BIC             R4, R4, R9
    SUB             R5, R4, R5
    ADD             R5, R5, R3
    CMP             LR, R5
    CMPCS           R6, LR
    BLS             loc_132C40
    CMP             R7, #0
    MOV             R1, R12
    MOV             R6, LR
    MOV             R8, R4
    BNE             loc_132C4C
    CMP             R6, R3
    BEQ             loc_132C4C

loc_132C40
    LDR             R12, [R12,#0xC]
    CMP             R12, #0
    BNE             loc_132BFC

loc_132C4C
    CMP             R1, #0
    BEQ             loc_132CF4
    MOV             R2, R8
    STR             R10, [SP,#0]
    BL              __cpp(nn::fnd::detail::AllocUsedBlockFromFreeBlock)
    MOV             R10, R0
    NOP
    B               loc_132CF4

loc_132C6C
    ADD             R6, R0, #0x24 ; '$'
    LDR             R0, [R0,#0x28]
    RSB             R12, R2, #0
    MOV             R1, #0
    CMP             R0, #0
    MOV             LR, #0xFFFFFFFF
    MOV             R2, R1
    SUBNE           R9, R12, #1
    BEQ             loc_132CF4

loc_132C90
    LDR             R8, [R0,#4]
    ADD             R4, R0, #0x10
    ADD             R12, R8, R4
    SUB             R12, R12, R3
    BIC             R12, R12, R9
    SUBS            R4, R12, R4
    BMI             loc_132CD0
    CMP             R8, LR
    BCS             loc_132CD0
    CMP             R7, #0
    MOV             R1, R0
    MOV             LR, R8
    MOV             R2, R12
    BNE             loc_132CDC
    CMP             LR, R3
    BEQ             loc_132CDC

loc_132CD0
    LDR             R0, [R0,#8]
    CMP             R0, #0
    BNE             loc_132C90

loc_132CDC
    CMP             R1, #0
    BEQ             loc_132CF4
    MOV             R0, R6
    STR             R5, [SP,#0x0]
    BL              __cpp(nn::fnd::detail::AllocUsedBlockFromFreeBlock)
    MOV             R10, R0

loc_132CF4
    MOV             R0, R10
    POP             {R3-R11,PC}
}

/* Freeing Heap */

__asm void FreeToHeap(Heap heap, void* p){
    SUB             R1, R1, #0x10
    ADD             R3, R0, #0x24 ; '$'
    PUSH            {R4}
    LDRH            R0, [R1,#2]
    LDR             R2, [R1,#4]
    ADD             R12, R1, #0x10
    MOV             R0, R0,LSL#17
    ADD             R4, R2, R12
    SUB             R2, R1, R0,LSR#25
    LDRD            R0, R1, [R1,#8]
    CMP             R0, #0
    STRNE           R1, [R0,#0xC]
    STREQ           R1, [R3,#8]
    CMP             R1, #0
    STRNE           R0, [R1,#8]
    STREQ           R0, [R3,#0xC]
    LDR             R1, [R3]
    MOV             R0, #0
    CMP             R1, #0
    BEQ             loc_460388

loc_4602F4
    CMP             R2, R1
    BLS             loc_460310
    MOV             R0, R1
    LDR             R1, [R1,#0xC]
    CMP             R1, #0
    BNE             loc_4602F4
    B               loc_460344

loc_460310
    CMP             R4, R1
    BNE             loc_460344
    LDR             R12, [R1,#4]
    ADD             R4, R1, #0x10
    ADD             R4, R4, R12
    LDR             R12, [R1,#8]
    LDR             R1, [R1,#0xC]
    CMP             R12, #0
    STRNE           R1, [R12,#0xC]
    STREQ           R1, [R3]
    CMP             R1, #0
    STRNE           R12, [R1,#8]
    STREQ           R12, [R3,#4]

loc_460344
    CMP             R0, #0
    BEQ             loc_460388
    LDR             R1, [R0,#4]
    ADD             R12, R0, #0x10
    ADD             R12, R12, R1
    CMP             R12, R2
    BNE             loc_460388
    LDR             R1, [R0,#8]
    MOV             R2, R0
    LDR             R0, [R0,#0xC]
    CMP             R1, #0
    STRNE           R0, [R1,#0xC]
    STREQ           R0, [R3]
    CMP             R0, #0
    STRNE           R1, [R0,#8]
    MOV             R0, R1
    STREQ           R1, [R3,#4]

loc_460388
    SUB             R12, R4, R2
    CMP             R12, #0x10
    BCC             loc_4603D4
    LDR             R4, =0x4652
    MOV             R1, #0
    SUB             R12, R12, #0x10
    STRH            R4, [R2]
    STRH            R1, [R2,#2]
    STR             R12, [R2,#4]
    CMP             R0, #0
    STRD            R0, R1, [R2,#8]
    LDRNE           R1, [R0,#0xC]
    LDREQ           R1, [R3]
    STRNE           R2, [R0,#0xC]
    STREQ           R2, [R3]
    CMP             R1, #0
    STR             R1, [R2,#0xC]
    STRNE           R2, [R1,#8]
    STREQ           R2, [R3,#4]

loc_4603D4
    POP             {R4}
    BX              LR
}

/* Creating Heap */

__asm Heap CreateHeap(Heap heapHandle, void* startAddr, u32 size, ushort optFlag){
    PRESERVE8
    MOV             R12, R3
    PUSH            {R3-R5, R12, LR}
    ADD             R3, R1, R2
    ADD             R1, R1, #3
    BIC             R2, R1, #3
    BIC             R3, R3, #3
    CMP             R3, R2
    SUBCS           R1, R3, R2
    CMPCS           R1, #0x14
    MOVCC           R0, #0
    BCC             locret_1196C4
    LDR             R1, =0x45585048
    MOV             R4, R0
    ADD             R5, R0, #0x24
    STR             R12, [SP,#0x0]
    BL              __cpp(nn::fnd::detail::NNSi_FndInitHeapHead)
    MOV             R2, #0
    STRH            R2, [R5,#0x10]
    STRH            R2, [R5,#0x12]
    LDR             R1, [R4,#0x18]
    LDR             R0, [R4,#0x1C]
    LDR             R3, =0x4652
    ADD             LR, R1, #4
    SUB             R0, R0, R1
    STRH            R3, [R1]
    SUB             R0, R0, #0x10
    STRH            R2, [R1,#2]
    STM             LR, {R0,R2}
    MOV             R0, R4
    ADD             R4, R5, #4
    STR             R2, [R1,#0xC]
    STR             R1, [R5]
    STM             R4, {R1,R2}
    STR             R2, [R5,#0xC]

locret_1196C4
    POP             {R3-R5, R12, PC}
}

NNSiFndHeapHead* FindContainHeap(NNSFndList* pList, void* memBlock){
    NNSiFndHeapHead* pHeapHd = NULL;
    while (NULL != (pHeapHd = reinterpret_cast<NNSiFndHeapHead*>(
                    GetNextListObject(pList, pHeapHd)))){
        if(NNSiGetUIntPtr(pHeapHd->heapStart) <= NNSiGetUIntPtr(memBlock) &&  NNSiGetUIntPtr(memBlock) < NNSiGetUIntPtr(pHeapHd->heapEnd)){
            NNSiFndHeapHead* pChildHeapHd = FindContainHeap(&pHeapHd->childList, memBlock);
            if(pChildHeapHd){
                return pChildHeapHd;
            }
            return pHeapHd;
        }
    }
    return 0;
}

void NNSi_FndInitHeapHead(NNSiFndHeapHead* pHeapHd,u32 signature,void* heapStart,void* heapEnd,ushort optFlag){
    pHeapHd->signature = signature;
    pHeapHd->attribute = optFlag & 0xFF;
    pHeapHd->heapStart = heapStart;
    pHeapHd->heapEnd = heapEnd;

    nn::fnd::detail::InitList(&pHeapHd->childList, 4);

    if (!sRootListInitialized){
        nn::fnd::detail::InitList(&sRootList, 4);
        sRootListInitialized = true;
    }

    NNSFndList* pRootList = &sRootList;
    NNSiFndHeapHead* pList = NULL;
    NNSFndList* pContain = &sRootList;

    pList = (NNSiFndHeapHead*)nn::fnd::detail::GetNextListObject(pRootList, NULL);
    while (pList != NULL){
        if (pList->heapStart <= pHeapHd && pHeapHd < pList->heapEnd){
            NNSiFndHeapHead* pFound = (NNSiFndHeapHead*)nn::fnd::detail::FindContainHeap(&pList->childList, pHeapHd);

            if (pFound == NULL)
                pFound = pList;

            pContain = &pFound->childList;
            break;
        }

        pList = (NNSiFndHeapHead*)nn::fnd::detail::GetNextListObject(pRootList, pList);
    }
    nn::fnd::detail::AppendListObject(pContain, pHeapHd);
}

}
}
}