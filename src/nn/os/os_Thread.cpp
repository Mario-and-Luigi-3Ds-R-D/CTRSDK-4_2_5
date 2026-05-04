#include <nn/os/os_Thread.h>
#include <nn/os/os_ThreadLocal.h>
#include <nn/os/CTR/os_CppException.h>
#include <nn/os/CTR/os_ErrorHandler.h>
#include <nn/os/ARM/os_SpinWait.h>
#include <nn/svc/svc_Api.h>

/*extern "C" char** __ARM_get_argv(void){
    return NULL;
}*/

extern "C" nn::os::AutoStackManager* spAutoStackManager;

namespace nn{
namespace os{
// STI is wrong.
Thread Thread::sMainThread = Thread::InitializeAsCurrentTag();
Thread::AutoStackManager*    Thread::spAutoStackManager = NULL;

// done by user QqquickqQ
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
// TODO
/*void Thread::ThreadStart(uptr p){
    nn::os::detail::InitializeThreadEnvrionment(); 
}*/

void Thread::TryInitializeAndStartImpl(nn::os::Thread::TypeInfo *typeInfo,nn::os::ThreadFunc f,void *p,uptr stackBottom,s32 priority, s32 coreNo,bool isAutoStack){
    // Todo
}

// The Offical SDK ASMs this one too.
//
// But it handles deconstructors, and exits it from the thread when done.
__asm void Thread::CallDestructorAndExit(){    
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


__asm void SaveThreadLocalRegionAddress(){
    MRC             p15, 0, R0,c13,c0, 3
    LDR             R1, =__cpp(&os::spTlr)
    STR             R0, [R1,#4]
    BX              LR
}


}
}
}