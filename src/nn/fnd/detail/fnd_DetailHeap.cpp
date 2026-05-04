#include <nn/fnd/detail/fnd_DetailHeap.h>
#include <nn/fnd/detail/fnd_DetailList.h>

namespace nn{
namespace fnd{
namespace detail{

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

// ASM AllocUsedBlockFromFreeBlock
// This function allocates a new memory from free blocks.

__asm void* AllocUsedBlockFromFreeBlock(NNSiFndExpHeapHead* pEHHead, NNSiFndExpHeapMBlockHead* pMBHeadFree,void* mblock,u32 size,u16 direction){
    PUSH            {R4-R11}
    ADD             R5, R1, #0x10
    SUB             R6, R2, #0x10
    LDR             R4, [R1,#4]
    LDRH            R12, [R1,#2]
    LDR             R7, [SP,#0x20]
    ADD             R8, R4, R5
    ADD             R5, R2, R3
    MOV             R12, R12,LSL#17
    LDR             R3, [R1,#8]
    SUB             R4, R1, R12,LSR#25
    LDR             R1, [R1,#0xC]
    CMP             R3, #0
    LDR             R9, =0x4652
    STRNE           R1, [R3,#0xC]
    STREQ           R1, [R0]
    CMP             R1, #0
    STRNE           R3, [R1,#8]
    SUB             R10, R6, R4
    STREQ           R3, [R0,#4]
    CMP             R10, #0x14
    MOV             R12, R6
    MOV             R1, #0
    BCC             loc_13E03C
    CMP             R7, #0
    LDRBEQ          R11, [R0,#0x14]
    CMPEQ           R11, #0
    BEQ             loc_13E03C
    STRH            R9, [R4]
    STRH            R1, [R4,#2]
    STR             R1, [R4,#0xC]
    SUB             R10, R10, #0x10
    STR             R3, [R4,#8]
    CMP             R3, #0
    STR             R10, [R4,#4]
    LDRNE           R10, [R3,#0xC]
    LDREQ           R10, [R0]
    STRNE           R4, [R3,#0xC]
    STREQ           R4, [R0]
    CMP             R10, #0
    STR             R10, [R4,#0xC]
    STRNE           R4, [R10,#8]
    MOV             R3, R4
    STREQ           R4, [R0,#4]
    B               loc_13E040

loc_13E03C
    MOV             R6, R4

loc_13E040
    SUB             R4, R8, R5
    CMP             R4, #0x14
    BCC             loc_13E09C
    CMP             R7, #1
    LDRBEQ          R10, [R0,#0x14]
    CMPEQ           R10, #0
    BEQ             loc_13E09C
    STRH            R9, [R5]
    STRH            R1, [R5,#2]
    STR             R1, [R5,#0xC]
    SUB             R4, R4, #0x10
    STR             R3, [R5,#8]
    CMP             R3, #0
    STR             R4, [R5,#4]
    LDRNE           R4, [R3,#0xC]
    LDREQ           R4, [R0]
    STRNE           R5, [R3,#0xC]
    STREQ           R5, [R0]
    CMP             R4, #0
    STR             R4, [R5,#0xC]
    STRNE           R5, [R4,#8]
    STREQ           R5, [R0,#4]
    B               loc_13E0A0

loc_13E09C
    MOV             R5, R8

loc_13E0A0
    LDR             R3, [R0,#-4]
    SUB             R4, R5, R6
    AND             R3, R3, #1
    CMP             R3, #0
    MOVNE           R8, #0
    CMPNE           R4, #3
    BLS             loc_13E0E4
    MOV             R9, R4,LSL#29
    SUB             R3, R6, #4
    CMP             R9, #0
    STRLT           R8, [R3,#4]!
    MOVS            R4, R4,LSR#3
    BEQ             loc_13E0E4

loc_13E0D4
    STR             R8, [R3,#4]
    SUBS            R4, R4, #1
    STR             R8, [R3,#8]!
    BNE             loc_13E0D4

loc_13E0E4
    LDR             R3, =0x5544
    SUB             R4, R5, R12
    SUB             R4, R4, #0x10
    STRH            R3, [R12]
    STR             R1, [R12,#8]
    STR             R4, [R12,#4]
    SUB             R3, R12, R6
    STR             R1, [R12,#0xC]
    ORR             R1, R1, R7,LSL#15
    AND             R3, R3, #0x7F
    BIC             R1, R1, #0x7F00
    ORR             R1, R1, R3,LSL#8
    STRH            R1, [R12,#2]
    LDRH            R3, [R0,#0x10]
    BIC             R1, R1, #0xFF
    AND             R3, R3, #0xFF
    ORR             R1, R1, R3
    STRH            R1, [R12,#2]
    LDR             R1, [R0,#0xC]
    CMP             R1, #0
    STR             R1, [R12,#8]
    LDRNE           R3, [R1,#0xC]
    LDREQ           R3, [R0,#8]
    STRNE           R12, [R1,#0xC]
    STREQ           R12, [R0,#8]
    CMP             R3, #0
    STR             R3, [R12,#0xC]
    STRNE           R12, [R3,#8]
    STREQ           R12, [R0,#0xC]
    POP             {R4-R11}
    MOV             R0, R2
    BX              LR
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

// ASM CreateHeap
// Returns the memory block to the expanded heap base.
// Also, as the title saids, it frees the heap.
//
// Paramaters: nn::fnd::Heap heap, void* pointer

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
// ASM CreateHeap
// Creates Heap to the expanded memory base.
//
// Paramaters: nn::fnd::Heap heapHandle, void* startAddr, u32 size, ushort optFlag.

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

#ifdef NONMATCHING
#endif
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