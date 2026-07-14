#pragma once

#include <nn/types.h>

namespace nn { 
namespace ro {

template <typename T>
class OffsetPointer{
private:
    uptr    mValue;
public:
    T* GetPointer(uptr baseAddr) const          { return reinterpret_cast<T*>(mValue + baseAddr); }
    T* GetPointer(const void* baseAddr) const   { return GetPointer(reinterpret_cast<uptr>(baseAddr)); }
};

}
}