#pragma once

#include "nn/os/os_AutoStackManager.h"
#include "nn/os/os_Mutex.h"
#include "nn/os/os_StackBuffer.h"

namespace nn{
namespace os{

    void SetDefaultAutoStackManager();

namespace{
    static AutoStackManager* spAutoStackManager;

    class DefaultAutoStackManager : public os::AutoStackManager{
    protected:
        os::Mutex mDestructorMutex;
        bool mInitialized;
        s8 rev[3];
        s32 rev2;
        os::StackBuffer200 mDeconstStack;
    public:
        virtual ~DefaultAutoStackManager();
        virtual void* Construct(size_t stackSize);
        virtual void Destruct(void* pStackBottom, bool isError);

        void FreeStack(void* pStackBottom);
    };
    static void InvokeOnOtherStack(uptr stackBottom,void (*f)(void*),void* param ,uptr returnAddr);
}
}
}