#pragma once

#include "nn/types.h"
#include "nn/util/util_NonCopyable.h"
#include "nn/fnd/fnd_Intrusive.h"

// Some macros for it, needed
#define NN_FND_HEAP_DEFAULT_ALIGNMENT   4
#define NN_FND_HEAP_OPTION_ZERO_CLEAR   (1 << 0)
#define NN_FND_HEAP_OPTION_DEBUG_FILL   (1 << 1)
#define NN_FND_HEAP_OPTION_ERROR_PRINT  (1 << 0)

// 100%

namespace nn{ 
namespace fnd{

enum HeapFillType {
    HEAP_FILL_TYPE_NOUSE,
    HEAP_FILL_TYPE_ALLOC,
    HEAP_FILL_TYPE_FREE,
    HEAP_FILL_TYPE_MAX
};

enum HeapInfoPlacement {
    HEAP_INFOPLACEMENT_HEAD,
    HEAP_INFOPLACEMENT_TAIL
};

enum HeapAdjustMode {
    HEAP_ADJUST_TAIL = 1,
    HEAP_ADJUST_HEAD = -1
};

class HeapBase : public IntrusiveLinkedList::Item {
public:
    HeapBase() {}
    static const s32 DEFAULT_ALIGNMENT = 4;
    static const bit32 OPTION_ERROR_PRINT = NN_FND_HEAP_OPTION_ERROR_PRINT;
    static void  SetFillValue(HeapFillType type, bit32 val);
    static bit32 GetFillValue(HeapFillType type);
    virtual ~HeapBase(){}
    virtual void FreeV(void*) = 0;
    virtual void* GetStartAddress() const = 0;
    virtual size_t GetTotalSize() const = 0;
    virtual void Dump() const = 0;
    virtual bool HasAddress(const void* addr) const = 0;
    
    HeapBase* GetRoot();
    HeapBase* FindHeap(void* addr);
    void Destroy(HeapBase* child);

protected:
    void Initialize(bit32 option);

    void SetParent(HeapBase* parent);

/*    static uptr RoundDown(uptr addr, s32 alignment) {
        return (addr / alignment) * alignment;
    }

    static uptr RoundUp(uptr addr, s32 alignment) {
        return RoundDown(addr + alignment - 1, alignment);
    }


    void FillMemoryZero(uptr addr, size_t size) {
        if (mOption & NN_FND_HEAP_OPTION_ZERO_CLEAR) {
            FillMemory32(addr, addr + size, 0);
        }
    }
*/
#ifdef BUILD_VERBOSE
    void DebugFillMemory(uptr addr, size_t size, HeapFillType type) {
        if (mOption & NN_FND_HEAP_OPTION_DEBUG_FILL) {
            FillMemory32(addr, addr + size, GetFillValue(type));
        }
    }
#else
    inline void DebugFillMemory(uptr, size_t, HeapFillType) {
    }

#endif

private:
    HeapBase* mParent;
    IntrusiveLinkedList mChildren;

    static void FillMemory(uptr addr, uptr end, bit8 value);
    static void FillMemory32(uptr addr, uptr end, bit32 value);
};

typedef u32 NNSiUIntPtr;

inline NNSiUIntPtr NNSiGetUIntPtr(const void* ptr){
    return (NNSiUIntPtr)ptr;
}

}
}