#include <nn/os/os_Thread.h>
#include <nn/os/os_ThreadLocal.h>
#include <nn/os/CTR/os_CppException.h>
#include <nn/os/CTR/os_ErrorHandler.h>
#include <nn/os/ARM/os_SpinWait.h>
#include <nn/svc/svc_Api.h>
#include <nn/util/util_Result.h>

extern "C" nn::os::AutoStackManager* spAutoStackManager;

namespace nn{
namespace os{

Thread Thread::sMainThread = Thread::InitializeAsCurrentTag();
Thread::AutoStackManager* Thread::spAutoStackManager = NULL;

/* Inlines */

inline void Thread::OnThreadStart(){
    nn::os::detail::InitializeThreadEnvrionment();
}

inline void Thread::OnThreadExit(){

}

/* Functions */
void Thread::FinalizeImpl(){
    if (this->mCanFinalize)
        return;

    s32 index;
    nn::Handle handle = this->mHandle;

    Result rc = nn::svc::WaitSynchronizationN(&index, &handle, 1, false, -1LL);

    u32 failed = rc.mResult >> 31;
    if (failed)
        nn::os::CTR::detail::HandleInternalError(rc);

    this->mCanFinalize = true;
}

void Thread::ThreadStart(uptr p){
    FunctionInfo& info = *reinterpret_cast<FunctionInfo*>(p);

    OnThreadStart();
    info.Invoke();
    info.Destroy();
    OnThreadExit();

    if(info.pAutoStackBuffer != NULL){
        CallDestructorAndExit(info.pAutoStackBuffer);
    }

    nn::svc::ExitThread();
}

void Thread::NoParamaterFunc(void (*f)()){
    f();
}

void Thread::SetAutoStackManager(nn::os::AutoStackManager* pManager){
    nn::os::Thread::spAutoStackManager = pManager;
}

void Thread::SleepImpl(fnd::TimeSpan span){
    if(span.GetNanoSeconds() >= 0){ // >= 0 could be wrong
        svc::SleepThread(span.GetNanoSeconds());
    }
    else{
        os::ARM::SpinWaitCpuCycles();
    }
}

Result Thread::TryInitializeAndStartImpl(const TypeInfo& typeInfo,nn::os::ThreadFunc f,const void *p,uptr stackBottom,s32 priority, s32 coreNo,bool isAutoStack){
    return TryInitializeAndStartImpl(typeInfo,f,p,stackBottom,priority,coreNo,(isAutoStack ? stackBottom: NULL));
}

Result Thread::TryInitializeAndStartImpl(const TypeInfo& typeInfo,nn::os::ThreadFunc f,const void *p,uptr stackBottom,s32 priority, s32 coreNo,uptr autoStackBuffer){
    uptr stack = stackBottom;
    
    stack -= typeInfo.size;
    stack &= 0xfffffff8;
    void* obj = reinterpret_cast<void*>(stack);
    typeInfo.copy(p, obj);

    stack -= sizeof(FunctionInfo);
    stack &= 0xfffffff8;
    FunctionInfo& info = *reinterpret_cast<FunctionInfo*>(stack);
    info.destroy = typeInfo.destroy;
    info.invoke = typeInfo.invoke;
    info.f = f;
    info.p = obj;
    info.pAutoStackBuffer = reinterpret_cast<void*>(autoStackBuffer);

    Handle handle;
    NN_UTIL_RETURN_IF_FAILED(nn::svc::CreateThread(&handle,ThreadStart,stack,stack,os::detail::ConvertLibraryToSvcPriority(priority),coreNo));

    this->SetHandle(handle);
    this->mCanFinalize = false;
    this->mUsingAutoStack = false;
    return ResultSuccess();
}

// Ori SDK Asms it.
__asm void Thread::CallDestructorAndExit(void* pStackBottom){    
    MOV             R2, #0 
    MOV             R1, R0 
    LDR             R0, =__cpp(&spAutoStackManager) // load AutoStackManager
    LDR             R0, [R0]
    LDR             R3, [R0]
    LDR             R3, [R3,#0xC] // load AutoStackManager's 0xC vtable slot
    LDR             LR, =__cpp(nn::svc::ExitThread) // goto -> nn::svc::ExitThread and prroceed
    BX              R3 // Branch eXchange R3's vtable, in this case AutoStackManager
}


os::CTR::ThreadLocalRegion* spTlr = NULL;


namespace detail{

s32 ConvertLibraryToSvcPriority(s32 lib){
    // if ( (u32)lib <= 32 )
  if ( lib >= 0 && lib <= 32 )
    return lib + 32;
  if ( lib >= 0x5109D500 && lib <= 0x5109D527 ) {
      const s32 offset = lib - 0x5109D500;
    return 24 + offset;
  }
  if ( lib >= 0x6C8DA500 && lib <= 0x6C8DA540 ) {
      const s32 offset = lib - 0x6C8DA500;
    return offset;
  }
  return -1;
}


__asm void SaveThreadLocalRegionAddress(){
    MRC             p15, 0, R0,c13,c0, 3
    LDR             R1, =__cpp(&os::spTlr)
    STR             R0, [R1,#4]
    BX              LR
}


}
}
}