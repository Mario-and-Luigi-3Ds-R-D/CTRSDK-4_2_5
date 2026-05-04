#include <nn/os/os_Default.h>
#include <nn/os/os_StackMemory.h>
#include <nn/os/os_Thread.h>
#include <nn/os/CTR/os_ErrorHandler.h>

namespace nn{
namespace os{

void SetDefaultAutoStackManager(){
    Thread* thread;
    thread->nn::os::Thread::SetAutoStackManager(spAutoStackManager);
}

namespace{

DefaultAutoStackManager::~DefaultAutoStackManager(){
if (this->mInitialized){
        this->mDestructorMutex.Finalize();
        this->mInitialized = false;
    }
}

// Constructor manager.

__asm void* DefaultAutoStackManager::Construct(size_t stackSize){
    PUSH            {R4-R6,LR}
    MOV             R6, R1
    LDRB            R1, [R0,#8]
    SUB             SP, SP, #0x20
    CMP             R1, #0
    BNE             loc_45F22C
    MOV             R4, R0
    ADD             R5, R0, #4
    MOV             R1, #0
    ADD             R0, SP, #0x18
    STR             R1, [SP,#0x18]
    BL              __cpp(nn::svc::CreateMutex)
    MOVS            R1, R0,LSR#31
    BNE             loc_45F21C
    LDR             R1, [SP,#0x18]
    MOV             R0, #0
    STR             R1, [R5]

loc_45F21C
    MOVS            R1, R0,LSR#31
    BLNE            __cpp(nn::os::CTR::detail::HandleInternalError)
    MOV             R0, #1
    STRB            R0, [R4,#8]

loc_45F22C
    MOV             R1, R6
    MOV             R0, SP
    BL              __cpp(nnosStackMemoryBlockAllocate)
    MOV             R0, SP
    NOP
    BL              __cpp(nnosStackMemoryBlockGetStackBottom)
    SUB             R4, R0, #0x18
    MOV             R0, R4
    BL              __cpp(nnosStackMemoryBlockInitialize)
    MOV             R1, SP
    MOV             R0, R4
    BL              __cpp(nn::os::detail::Switch)
    ADD             SP, SP, #0x20
    MOV             R0, R4
    POP             {R4-R6,PC}

}

void DefaultAutoStackManager::Destruct(void* pStackBottom, bool isError){

}

void DefaultAutoStackManager::FreeStack(void* pStackBottom){
    nnosStackMemoryBlockFree((nnosStackMemoryBlock*)pStackBottom);
}

__asm void InvokeOnOtherStack(uptr stackBottom,void (*f)(void*),void* param ,uptr returnAddr){
    mov         sp, r0
    mov         r0, r2
    mov         lr, r3
    bx          r1
}

}
}
}