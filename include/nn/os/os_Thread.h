#pragma once

#include "nn/types.h"
#include "nn/os/os_Types.h"
#include "nn/os/os_AutoStackManager.h"
#include "nn/fnd/fnd_TimeSpan.h"

namespace nn{
namespace os{

typedef void (*ThreadFunc)(uptr);

    class Thread : public nn::os::WaitObject{
    public:
        /* Paramaters */

        bool mCanFinalize;
        bool mUsingAutoStack;
        short pad1;
        
        /* nn::os::Thread::TypeInfo */

        struct TypeInfo{
        public:

        /* Type Info Paramaters*/
            size_t size;
            void* copy;
            void* destroy;
            void* invoke;

            void Copy(void* src, void* dst); // 5 of them
            void Destroy(void* p); // 4 of them
            void Invoke(nn::os::ThreadFunc f, void* p); // 4 of them
        };

        /* Funcs */

        void CallDestructorAndExit();
        void FinalizeImpl();
        void NoParamaterFunc();
        void SetAutoStackManager(nn::os::AutoStackManager* pManager);
        void SleepImpl(); // nn::fnd::TimeSpan* span
        void ThreadStart(uptr p);
        void TryInitializeAndStartImpl(nn::os::Thread::TypeInfo *typeInfo,nn::os::ThreadFunc f,void *p,uptr stackBottom,s32 priority, s32 coreNo,bool isAutoStack);
        void TryInitializeAndStartImplUsingAutoStack(nn::os::Thread::TypeInfo *typeInfo,nn::os::ThreadFunc f,void *p,size_t stackSize,s32 priority,s32 coreNo);
    protected:
    nn::os::AutoStackManager* spAutoStackManager;
    };
}
}