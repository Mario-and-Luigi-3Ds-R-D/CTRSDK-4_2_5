#pragma once

#include "nn/types.h"
#include "nn/os/os_Types.h"
#include "nn/os/os_AutoStackManager.h"
#include "nn/fnd/fnd_TimeSpan.h"

namespace nn{
namespace os{
typedef void (*ThreadFunc)(uptr);

    class Thread : public nn::os::WaitObject{
    private:
        struct InitializeAsCurrentTag {};
        
        Thread(const InitializeAsCurrentTag&) { }
    public:
        Thread() : mCanFinalize(true) {}
        /* Paramaters */
        typedef nn::os::AutoStackManager AutoStackManager;

        bool mCanFinalize;
        bool mUsingAutoStack;
        short pad1;

        static Thread               sMainThread;
        static AutoStackManager*    spAutoStackManager;
        
        /* nn::os::Thread::TypeInfo */

        struct TypeInfo{
        public:

        /* Type Info Paramaters*/
            size_t size;
            void* copy;
            void* destroy;
            void* invoke;

            template <typename T, typename U>
            static void Copy(const void* src, void* dst){
                new (dst) T(*reinterpret_cast<const U*>(src));
            }
            template <typename T>
            static void Copy(const void* src, void* dst){
                new (dst) T(*reinterpret_cast<const T*>(src));
            }

            template <typename T>
            static void Destroy(void* p){
                reinterpret_cast<T*>(p)->~T();
            }

            template <typename T>
            static void Invoke(ThreadFunc f, const void* p){
                (*reinterpret_cast<void (*)(T)>(f))(*reinterpret_cast<const T*>(p));
            }
            template <typename T>
            static void Invoke2(ThreadFunc f, const void* p){
                (*reinterpret_cast<void (*)(const T*)>(f))(reinterpret_cast<const T*>(p));
            }
        };

        class ProtectedAccessor{
            inline void InitializeAsMainThread(void* p){
                new(p) Thread(Thread::InitializeAsCurrentTag());
            }
        };

        /* Funcs */

        void CallDestructorAndExit();
        void FinalizeImpl();
        static void NoParamaterFunc(void (*f)());
        static void SetAutoStackManager(nn::os::AutoStackManager*);
        void SleepImpl(fnd::TimeSpan span); // nn::fnd::TimeSpan* span
        void ThreadStart(uptr p);
        void TryInitializeAndStartImpl(nn::os::Thread::TypeInfo *typeInfo,nn::os::ThreadFunc f,void *p,uptr stackBottom,s32 priority, s32 coreNo,bool isAutoStack);
        void TryInitializeAndStartImplUsingAutoStack(nn::os::Thread::TypeInfo *typeInfo,nn::os::ThreadFunc f,void *p,size_t stackSize,s32 priority,s32 coreNo);
    private:
    };

namespace detail{

void InitializeThreadEnvrionment();
void SaveThreadLocalRegionAddress();

}
}
}