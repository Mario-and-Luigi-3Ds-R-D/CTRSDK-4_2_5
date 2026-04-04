#pragma once

#include "nn/Handle.h"
#include "nn/fnd/fnd_Intrusive.h" //rename 2 Intrusive.h

namespace nn{
namespace srv{
namespace detail{

    class Manager{
        nn::Handle sSession;
    };

    class HandlerManager{
    public:
        nn::fnd::IntrusiveLinkedList mHandler;
        
        ~HandlerManager();
    };

}
}
}