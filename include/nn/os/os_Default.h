#pragma once

#include <nn/os/os_AutoStackManager.h>
#include <nn/os/os_Mutex.h>
#include <nn/os/os_Thread.h>

namespace nn{
namespace os{

void SetDefaultAutoStackManager();

namespace{
static AutoStackManager* spAutoStackManager;

class DefaultAutoStackManager : public os::AutoStackManager{
protected:
    static const size_t DESTRUCTOR_STACK_SIZE = 512;

    os::Mutex mDestructorMutex;
    bool mInitialized;
    s8 rev[3];
    s32 rev2;
    os::StackBuffer<DESTRUCTOR_STACK_SIZE>  mDestructorStack;
public:
    virtual ~DefaultAutoStackManager();
    virtual void* Construct(size_t stackSize);
    virtual void Destruct(void* pStackBottom, bool isError);

    static void FreeStack(void* pStackBottom);

private:
    void Initialize(void){
        this->mDestructorMutex.Initialize(false);
        mInitialized = true;
    }

};

static void InvokeOnOtherStack(uptr stackBottom,void (*f)(void*),void* param ,uptr returnAddr);
}
}
}