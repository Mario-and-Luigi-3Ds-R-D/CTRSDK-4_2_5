#pragma once

#include "nn/types.h"
#include "nn/fnd/fnd_HeapBase.h"
#include "nn/fnd/fnd_Allocator.h"
#include "nn/fnd/detail/fnd_DetailHeapHead.h"
#include "nn/os/os_LockPolicy.h"
#include "nn/os/os_CriticalSection.h"

// 100%

#define NN_FND_EXPHEAP_ALLOCATION_MODE_FIRST_FIT    0
#define NN_FND_EXPHEAP_ALLOCATION_MODE_BEST_FIT     1
#define NN_FND_EXPHEAP_ALLOCATION_DIRECTION_FRONT   0
#define NN_FND_EXPHEAP_ALLOCATION_DIRECTION_REAR    1

namespace nn{
namespace fnd{

class ExpHeapBase : public HeapBase {
public:
    enum AllocationMode {
        ALLOCATION_MODE_FIRST_FIT = NN_FND_EXPHEAP_ALLOCATION_MODE_FIRST_FIT,
        ALLOCATION_MODE_BEST_FIT  = NN_FND_EXPHEAP_ALLOCATION_MODE_BEST_FIT
    };

    enum AllocationDirection {
        ALLOCATION_DIRECTION_FRONT = NN_FND_EXPHEAP_ALLOCATION_DIRECTION_FRONT,
        ALLOCATION_DIRECTION_REAR  = NN_FND_EXPHEAP_ALLOCATION_DIRECTION_REAR
    };

    typedef void (*BlockVisitor)(void* pBlock, const ExpHeapBase* heap, uptr param);

    size_t           GetSizeOf(const void* pBlock) const;
    bit8             GetGroupIdOf(const void* pBlock) const;
    AllocationDirection GetDirectionOf(const void* pBlock) const;

public:
    ExpHeapBase() : mAllocCount(0) {}

    template <class MemoryBlock>
    explicit ExpHeapBase(const MemoryBlock& block, bit32 option) {
        Initialize(block.GetAddress(), block.GetSize(), option);
    }

    ExpHeapBase(uptr addr, size_t size, bit32 option); // 100%
    void Initialize(uptr addr, size_t size, bit32 option); // 100%
    void Invalidate(); // 100%
    void Finalize(); // 100%

    void* Allocate(size_t byteSize, s32 alignment, bit8 groupId, AllocationMode mode, bool reuse);
    void Free(void* p); // 100%
    virtual ~ExpHeapBase(); // 100%
    virtual void FreeV(void* p); // 100%
    virtual void* GetStartAddress() const; // 100%
    virtual size_t GetTotalSize() const; // 100%
    virtual void Dump() const; // 100%
    virtual bool HasAddress(const void* addr) const; // 100%
    size_t ResizeBlock(void* p, size_t newSize);
    void VisitAllBlocks(BlockVisitor visitor, uptr param);
    size_t GetTotalFreeSize() const;
    size_t GetAllocatableSize(s32 alignment) const;
    bool CheckHeap(bit32 option = OPTION_ERROR_PRINT) const;
    bool CheckBlock(const void* p, bit32 option = OPTION_ERROR_PRINT) const;

    detail::ExpHeapImpl mExpHeapImpl;
    size_t mAllocCount;
};

template <class LockPolicy>
class ExpHeapTemplate : public ExpHeapBase, private LockPolicy::LockObject {
private:
    typedef ExpHeapBase Base;
    typedef typename LockPolicy::LockObject LockObject;
    typedef typename LockPolicy::ScopedLock ScopedLock;

public:
    ExpHeapTemplate() {}

    ExpHeapTemplate(uptr addr, size_t size, bit32 option = 0) {
        Initialize(addr, size, option);
    }

    static ExpHeapTemplate* Create(HeapBase* parent, void* addr, size_t size, bit32 option = 0, bit32 placement = HEAP_INFOPLACEMENT_HEAD);

    void Initialize(uptr addr, size_t size, bit32 option = 0) {
        Base::Initialize(addr, size, option);
        LockObject::Initialize();
    }

    void Invalidate() { 
        this->Base::Invalidate(); 
    }

    void Finalize() {
        LockObject::Finalize();
        Base::Finalize();
    }

    virtual ~ExpHeapTemplate(){
    }

    void Free(void* p) {
        ScopedLock lk(*this);
        Base::Free(p);
    }

    virtual void FreeV(void* p) {
        Free(p); 
    }

    virtual void* GetStartAddress() const{
        ScopedLock lk(*this);
        return Base::GetStartAddress();
    }

    virtual size_t GetTotalSize() const{
        ScopedLock lk(*this);
        return Base::GetTotalSize();
    }

    virtual void Dump() const{
        ScopedLock lk(*this);
        Base::Dump();
    }

    virtual bool HasAddress(const void* addr) const{
        ScopedLock lk(*this);
        return Base::HasAddress(addr);
    }

    size_t ResizeBlock(void* p, size_t newSize) {
        ScopedLock lk(*this);
        return Base::ResizeBlock(p, newSize);
    }

    void* Allocate(size_t byteSize, s32 alignment, bit8 groupId, AllocationMode mode, bool reuse) {
        ScopedLock lk(*this);
        return Base::Allocate(byteSize, alignment, groupId, mode, reuse);
    }

    void VisitAllBlocks(BlockVisitor visitor, uptr param){
        ScopedLock lk(*this);
        return Base::VisitAllBlocks(visitor, param);
    }

    size_t GetTotalFreeSize() const{
        ScopedLock lk(*this);
        return Base::GetTotalFreeSize();
    }

    size_t GetAllocatableSize(s32 alignment) const{
        ScopedLock lk(*this);
        return Base::GetAllocatableSize(alignment);
    }

    bool CheckHeap(bit32 option = OPTION_ERROR_PRINT) const {
        ScopedLock lk(*this);
        return Base::CheckHeap(option);
    }

    bool CheckBlock(const void* p, bit32 option = OPTION_ERROR_PRINT) const {
        ScopedLock lk(*this);
        return Base::CheckBlock(p, option);
    }

    class Allocator; // needed for Template # 2
};

template <class LockPolicy>
class ExpHeapTemplate<LockPolicy>::Allocator : public IAllocator {
public:
    Allocator(ExpHeapTemplate<LockPolicy>& heap, bit8 groupId = 0, AllocationMode mode = ExpHeapBase::ALLOCATION_MODE_FIRST_FIT, bool reuse = false) : mHeap(0) {
        Initialize(heap, groupId, mode, reuse);
    }

    Allocator() : mHeap(0) {}

    void Initialize(ExpHeapTemplate<LockPolicy>& heap, bit8 groupId = 0, AllocationMode mode = ExpHeapBase::ALLOCATION_MODE_FIRST_FIT, bool reuse = false) {
        this->mHeap = &heap;
        this->mGroupId = groupId;
        this->mAllocationMode = mode;
        this->mReuse = reuse;
    }

    ExpHeapTemplate<LockPolicy>*GetHeap(){
        return this->mHeap; 
    }
    const ExpHeapTemplate<LockPolicy>* GetHeap() const {
        return this->mHeap; 
    }

    virtual void* Allocate(size_t size, s32 alignment) {
        return this->mHeap->Allocate(size, alignment, mGroupId, (AllocationMode)mAllocationMode, mReuse);
    }

    virtual void Free(void* p){
        this->mHeap->Free(p); 
    }

    bit8 GetGroupId() const{
        return this->mGroupId; 
    }
    void SetGroupId(bit8 groupId){
        this->mGroupId = groupId; 
    }
    AllocationMode GetAllocationMode() const{
        return (AllocationMode)this->mAllocationMode; 
    }
    void SetAllocationMode(AllocationMode mode){
        (AllocationMode)this->mAllocationMode = mode; 
    }
    bool GetUseMarginOfAlignment() const{
        return this->mReuse; 
    }
    void SetUseMarginOfAlignment(bool reuse) {
        this->mReuse = reuse; 
    }

private:
    ExpHeapTemplate<LockPolicy>* mHeap;
    bit8 mGroupId;
    s8 mAllocationMode;
    bool mReuse;
    s8 PADDING1;
};

}
}