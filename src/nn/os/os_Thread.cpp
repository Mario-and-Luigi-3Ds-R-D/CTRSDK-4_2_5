#include <nn/os/os_Thread.h>
#include <nn/os/os_ThreadLocal.h>
#include <nn/os/CTR/os_CppException.h>
#include <nn/os/CTR/os_ErrorHandler.h>
#include <nn/svc/svc_Api.h>

extern "C" nn::os::AutoStackManager* spAutoStackManager;

namespace nn{
namespace os{
// The Offical SDK ASMs this one too.
//
// But it handles deconstructors, and exits it from the thread when done.

Thread            nn::os::Thread::sMainThread;
Thread::AutoStackManager*    Thread::spAutoStackManager = NULL;


__asm void Thread::CallDestructorAndExit(){    
    MOV             R2, #0 // Put false as the second argument
    MOV             R1, R0 // Put pStackBottom as the first argument
    LDR             R0, =__cpp(&spAutoStackManager) // Load the address of s_pAutoStackManager
    LDR             R0, [R0] // Load spAutoStackManager
    LDR             R3, [R0] // Load vtable addr
    LDR             R3, [R3,#0xC] // Load Func from vtable, in this case Destruct
    LDR             LR, =__cpp(nn::svc::ExitThread) // Load vtable whilst initializing ExitThread
    BX              R3
}

// Do the finalizing of a Thread
//
// Move on with fashion to the next.
__asm void Thread::FinalizeImpl(){
    PUSH            {R4,LR} // Push onto the stack
    MOV             R4, R0
    LDRB            R0, [R0,#4]
    SUB             SP, SP, #0x10
    CMP             R0, #0
    BNE             loc_121138
    LDR             R2, [R4]
    MOV             R0, #0xFFFFFFFF
    MOV             R1, R0
    STMEA           SP, {R0-R2}
    MOV             R3, #0
    MOV             R2, #1
    ADD             R1, SP, #8
    ADD             R0, SP, #0xC
    BL              __cpp(nn::svc::WaitSynchronizationN) // Load WairSynchronizationN
    MOVS            R1, R0,LSR#31 // this one is why i made it asm this one is hard
    BLNE            __cpp(nn::os::CTR::detail::HandleInternalError) // Link to HandleInternal error
    MOV             R0, #1

loc_121134
    STRB            R0, [R4,#4]

loc_121138
    ADD             SP, SP, #0x10
    POP             {R4,PC}
}

void Thread::NoParamaterFunc(void (*f)()){
    f();
}

void Thread::SetAutoStackManager(nn::os::AutoStackManager* pManager){
    nn::os::Thread::spAutoStackManager = pManager;
}

/*void Thread::SleepImpl(){

}*/

void Thread::ThreadStart(uptr p){

}

// Trys to Initalize and Start thread.
//
// Writes information that is passed to the thread to the stack region.
// At end it declares that, if -1, that thread cannot initialize and will fail.
__asm void Thread::TryInitializeAndStartImpl(nn::os::Thread::TypeInfo *typeInfo,nn::os::ThreadFunc f,void *p,uptr stackBottom,s32 priority, s32 coreNo,bool isAutoStack){
    PUSH            {R4-R10,LR}
    SUB             SP, SP, #0x10
    MOV             R8, R1
    ADD             R4, SP, #0x34
    LDR             R1, [SP,#0x3C]
    LDR             R6, [SP,#0x30]
    LDM             R4, {R5,R10}
    CMP             R1, #0
    LDR             R1, [R8]
    MOV             R4, R0
    MOV             R0, R6
    MOV             R9, R2
    SUB             R0, R0, R1
    LDR             R2, [R8,#4]
    BIC             R7, R0, #7
    MOVEQ           R6, #0
    MOV             R1, R7
    MOV             R0, R3
    BLX             R2
    LDR             R0, [R8,#8]
    SUB             R1, R7, #0x14
    BIC             R2, R1, #7
    ADD             R1, R2, #4
    STR             R0, [R2]
    LDR             R0, [R8,#0xC]
    STR             R6, [R2,#0x10]
    STR             R7, [R2,#0xC]
    STM             R1, {R0,R9}
    CMP             R5, #0x20
    MOV             R6, #0
    ADDLS           R0, R5, #0x20
    STR             R6, [SP,#0x8]
    BLS             loc_118CA8
    LDR             R0, =0xAEF62B00
    ADD             R0, R0, R5
    CMP             R0, #0x27
    ADDLS           R0, R0, #0x18
    BLS             loc_118CA8
    LDR             R0, =0x93725B00
    ADD             R0, R0, R5
    CMP             R0, #0x40
    MOVHI           R0, #0xFFFFFFFF

loc_118CA8
    STMEA           SP, {R0,R10}
    LDR             R1, =__cpp(nn::os::Thread::ThreadStart)
    MOV             R3, R2
    ADD             R0, SP, #0x8
    BL              __cpp(nn::svc::CreateThread)
    MOVS            R1, R0,LSR#31
    NOP
    BNE             loc_118CDC
    LDR             R0, [SP,#0x8]
    STR             R0, [R4]
    STRB            R6, [R4,#4]
    MOV             R0, R6
    STRB            R6, [R4,#5]

loc_118CDC
    ADD             SP, SP, #0x10
    POP             {R4-R10,PC}
}


}
}