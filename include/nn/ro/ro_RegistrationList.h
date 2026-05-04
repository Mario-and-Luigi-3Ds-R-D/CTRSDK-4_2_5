#pragma once

#include "nn/Result.h"

namespace nn{
namespace ro{

    class RegistrationList{
    public:
        RegistrationList();
        ~RegistrationList(){ Unregister(); }
        Result Unregister();
        void operator delete(void* p){ }
        void* operator new(size_t size) throw ();
        uptr GetHead() { return reinterpret_cast<uptr>(this); }
    };
}
}