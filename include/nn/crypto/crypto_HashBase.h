#pragma once

#include "nn/types.h"

namespace nn{
namespace crypto{
class HashContextBase{
public:
    virtual void Initialize() {}
    virtual void Finalize() {}
    virtual void Update(const void* pData, size_t size) {}
    virtual size_t GetHashSize() { return 0; }
    virtual void GetHash(void* pOut) {}

protected:
    HashContextBase() {}
    virtual ~HashContextBase() {}
    virtual void ProcessBlock() {}
};
}
}