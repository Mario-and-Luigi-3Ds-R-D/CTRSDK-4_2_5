#pragma once

#include "nn/types.h"
#include "nn/os/os_Types.h"
#include "nn/os/os_AutoStackManager.h"
#include "nn/fnd/fnd_TimeSpan.h"
#include "nn/util/util_TypeTraits.h"

namespace nn{
namespace os{
namespace detail{
void SaveThreadLocalRegionAddress();
s32 ConvertLibraryToSvcPriority(s32);

}
typedef void (*ThreadFunc)(uptr);

class Thread : public WaitObject{
private:
    struct FunctionInfo;
    struct TypeInfo;
    struct InitializeAsCurrentTag {};

private:
    Thread(const InitializeAsCurrentTag&) { }
    // Use this down here! Intro to the bottom!
    //
    // Result TryInitializeAndStartImpl(const TypeInfo& typeInfo,nn::os::ThreadFunc f,const void *p,uptr stackBottom,s32 priority, s32 coreNo,bool isAutoStack) !!!!
    void FinalizeImpl();
    Result TryInitializeAndStartImpl(const TypeInfo& typeInfo,nn::os::ThreadFunc f,const void *p,uptr stackBottom,s32 priority, s32 coreNo,bool isAutoStack);
    Result TryInitializeAndStartImpl(const TypeInfo& typeInfo,nn::os::ThreadFunc f,const void *p,uptr stackBottom,s32 priority, s32 coreNo,uptr autoStackBuffer );

public:
    Thread() : mCanFinalize(true) {}
    ~Thread();
    
    /* Paramaters */
    typedef AutoStackManager AutoStackManager;

    bool mCanFinalize;
    bool mUsingAutoStack;
    short pad1;

    static Thread sMainThread;
    static AutoStackManager* spAutoStackManager;

public:
        

    class ProtectedAccessor{
        inline void InitializeAsMainThread(void* p){
            new(p) Thread(Thread::InitializeAsCurrentTag());
        }
    };

    /* Funcs */
    static void NoParamaterFunc(void (*)());
    static void SetAutoStackManager(os::AutoStackManager*);
    static void ThreadStart(uptr p);
    static void CallDestructorAndExit(void*);
    static void SleepImpl(fnd::TimeSpan span); // nn::fnd::TimeSpan* span

    static void OnThreadStart();
    static void OnThreadExit();
};

struct Thread::FunctionInfo{
    void (*destroy)(void* p);                    //
    void (*invoke)(ThreadFunc f, const void* p); //
    void (*f)(uptr);                             //
    void* p;                                     //
    void* pAutoStackBuffer;

    void Invoke(){
        invoke(f, p);
    };
    void Destroy(){
        destroy(p);
    }
};

struct Thread::TypeInfo{
private:

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

public:
    size_t size;
    void (*copy)(const void* src, void* dst);
    void (*destroy)(void* p);
    void (*invoke)(ThreadFunc f, const void* p);

    template <typename T, typename U>
    void SetData(typename nn::util::enable_if<nn::util::is_convertible<U, T>::value>::type* = 0){
        this->size = sizeof(T);
        this->copy = &(Copy<T, U>);
        this->destroy = &(Destroy<T>);
        this->invoke = &(Invoke<T>);
    }
    template <typename T>
    void SetData(){
        this->size = sizeof(T);
        this->copy = &(Copy<T>);
        this->destroy = &(Destroy<T>);
        this->invoke = &(Invoke2<T>);
    }
};

inline Thread::~Thread(){ 
    this->FinalizeImpl();
}

}
}