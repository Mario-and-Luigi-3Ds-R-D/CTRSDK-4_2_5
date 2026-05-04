#include <nn/applet/applet_All.h>
//#include <nn/gxlow/gxlow_SystemUse.h>
#include <nn/err/CTR/err_Api.h>

const nn::Handle nn::applet::CTR::HANDLE_NONE = (nn::Handle)0;

namespace nn{
namespace applet{
namespace CTR{
namespace detail{

bool sIsApplet;
bool sIsVramSaved;
bool sIsInitialized;
bool sIsGpuRightGiven;
bool sIsDspSleeping;

void Enable(bool isSleepEnable){
    
}

/*void Enable(bool isSleepEnable){
    nn::applet::CTR::AppletAttr Attribute;
    Result result;
    u8 *InitialParamBuffer;
    nn::applet::CTR::WakeupState wakeupState;
    nn::applet::CTR::AppletId id;
    s32 size;

    if(isSleepEnable){
        EnableSleep(0);
    }
    detail::LockAndConnect();
    Attribute = GetAttribute();
    result = detail::APPLET::Enable(Attribute);
    if(result.IsFailure() != 0){
        uptr pc = __current_pc();
        err::CTR::ThrowFatalErr(result,pc);
    }
    detail::DisconnectAndUnlock();
    if(IsApplication() && (GetAttribute() & 0x20) == 0){
        SetTransitionType(TRANSITION_ENABLE_APPLET);
        InitialParamBuffer = detail::GetInitialParamBuffer();
        wakeupState = WaitForStarting(&id,InitialParamBuffer,0x1000u,&size,0,WAIT_INFINITE);
        SetInitialParamSenderId(id);
        SetInitialParamSenderSize(size);
        SetInitialParamValid();
        SetInitialWakeupState(wakeupState);
    }
}*/

__asm void CallUtility(u32 utilityId, u8* pInParam, size_t inParamSize, u8* pOutParam, size_t outParamSize, s32* pReadSize){
    PUSH            {R4-R10,LR}
    SUB             SP, SP, #0x18
    MOV             R4, #0
    MOV             R10, R0
    MOV             R8, R1
    MOV             R9, R2
    MOV             R5, R3
    LDRD            R6, R7, [SP,#0x38]
    STR             R4, [SP,#0x8]
    STR             R4, [SP,#0xC]
    BL              __cpp(nn::applet::CTR::detail::LockAndConnect)
    CMP             R5, #0
    ADD             R0, SP, #0x10
    BEQ             loc_123348
    CMP             R6, #0
    MOVNE           R1, R6
    MOVEQ           R1, #1
    MOVNE           R3, R5
    STR             R0, [SP,#0x4]
    STR             R1, [SP,#0x0]
    BNE             loc_1232E4

loc_1232E0
    ADD             R3, SP, #0xC

loc_1232E4
    CMP             R8, #0
    MOVEQ           R2, #1
    BEQ             loc_123304
    CMP             R9, #0
    MOVEQ           R9, #1
    MOV             R2, R9
    MOVNE           R1, R8
    BNE             loc_123308

loc_123304
    ADD             R1, SP, #0x8

loc_123308
    MOV             R0, R10
    BL              __cpp(nn::applet::CTR::detail::APPLET::AppletUtility)
    MOV             R8, R0
    MOV             R1, PC
    MOVS            R2, R0,LSR#31
    BLNE            __cpp(nn::err::CTR::ThrowFatalErr)
    CMP             R5, #0
    CMPNE           R6, #0
    STREQ           R4, [SP,#0x10]
    CMP             R7, #0
    LDRNE           R0, [SP,#0x10]
    STRNE           R0, [R7]
    BL              __cpp(nn::applet::CTR::detail::DisconnectAndUnlock)
    ADD             SP, SP, #0x18
    MOV             R0, R8
    POP             {R4-R10,PC}

loc_123348
    MOV             R1, #1
    STR             R0, [SP,#0x4]
    STR             R1, [SP,#0x0]
    B               loc_1232E0
}

bool WaitForRegister(AppletId appletId,nn::fnd::TimeSpan span){

}

Result CloseApplication(u8 *pParam,size_t paramSize,nn::Handle handle){
    // TODO
}

/*__asm void AssignGpuRight(bool flag){
        LDR             R1, =__cpp(&nn::applet::CTR::detail::sIsApplet)
        CMP             R0, #0
        PUSH            {R4,LR}
        BEQ             loc_11AB78
        MOV             R0, #1
        STRB            R0, [R1,#3]
        BL              __cpp(nn::gxlow::CTR::AcquireGpuRight)
        MOV             R1, PC
        MOVS            R2, R0,LSR#31
        BNE             loc_11ABB0

locret_11AB74
        POP             {R4,PC}

loc_11AB78
        LDRB            R0, [R1,#3]
        CMP             R0, #0
        BEQ             locret_11AB74
        MOV             R0, #0
        STRB            R0, [R1,#3]
        BL              __cpp(nn::gxlow::CTR::ReleaseGpuRight)
        LDR             R1, =0xD8A02A05
        CMP             R0, R1
        LDRNE           R1, =0xD9001BF7
        CMPNE           R0, R1
        BEQ             locret_11AB74
        MOV             R1, PC
        MOVS            R2, R0,LSR#31
        BEQ             locret_11AB74

loc_11ABB0
        POP             {R4,LR}
        B               __cpp(nn::err::CTR::ThrowFatalErr)
}*/

void AssignDspRight(bool flag){
    // TODO
}

Result CancelLibraryAppletIfRegistered(bool isApplicationEnd, nn::applet::CTR::AppletWakeupState *pWakeupState){
    // TODO
}

__asm bool CancelParamater(bool isSenderCheck, nn::applet::CTR::AppletId senderId, bool isReceiverCheck, nn::applet::CTR::AppletId receiverId){
    PUSH            {R4-R7,LR}
    SUB             SP, SP, #0xC
    MOV             R4, R0
    MOV             R5, R1
    MOV             R6, R2
    MOV             R7, R3
    BL              __cpp(nn::applet::CTR::detail::LockAndConnect)
    ADD             R12, SP, #0x04
    MOV             R3, R7
    MOV             R2, R6
    MOV             R1, R5
    MOV             R0, R4
    STR             R12, [SP,#0x0]
    BL              __cpp(nn::applet::CTR::detail::APPLET::CancelParamater)
    MOV             R1, PC
    MOVS            R2, R0,LSR#31
    BLNE            __cpp(nn::err::CTR::ThrowFatalErr)
    BL              __cpp(nn::applet::CTR::detail::DisconnectAndUnlock)
    LDRSB           R0, [SP,#0x04]
    ADD             SP, SP, #0xC
    POP             {R4-R7,PC}
}

__asm Result JumpToHomeMenu(u8 *pParam,size_t paramSize,Handle handle){
    PUSH            {R4-R8,LR}
    SUB             SP, SP, #0x18
    MOV             R8, R0
    LDR             R7, [SP,#0x30]
    MOV             R4, R1
    MOV             R5, R2
    MOV             R6, R3
    BL              __cpp(nn::applet::CTR::detail::LockAndConnect)
    ADD             R1, SP, #0x10
    STR             R1, [SP,#0x0]
    ADD             R3, SP, #0xC
    ADD             R2, SP, #0x8
    ADD             R1, SP, #0x4
    MOV             R0, R8
    BL              __cpp(nn::applet::CTR::detail::APPLET::GetAppletManInfo)
    MOV             R1, PC
    MOVS            R2, R0,LSR#31
    BLNE            __cpp(nn::err::CTR::ThrowFatalErr)
    BL              __cpp(nn::applet::CTR::detail::DisconnectAndUnlock)
    CMP             R4, #0
    LDRBNE          R0, [SP,#0x4]
    STRBNE          R0, [R4]
    CMP             R5, #0
    LDRNE           R0, [SP,#0x8]
    STRNE           R0, [R5]
    CMP             R6, #0
    LDRNE           R0, [SP,#0xC]
    STRNE           R0, [R6]
    CMP             R7, #0
    LDRNE           R0, [SP,#0x10]
    STRNE           R0, [R7]
    ADD             SP, SP, #0x18
    POP             {R4-R8,PC}
}

void PrepareToJumpToHomeMenu(){

}

void GetAppletManInfo(AppletPos requestPos,AppletPos *pCurrentPos,AppletId *pRequestedId,AppletId *pHomeMenuId,AppletId *pCurrentId){

}

__asm void UnlockTransition(u32 action){
    PUSH            {R0,LR}
    SUB             SP, SP, #8
    MOV             R3, #0
    ADD             R1, SP, #0x8
    MOV             R0, #7
    MOV             R2, #4
    STR             R3, [SP,#0x0]
    STR             R3, [SP,#0x4]
    BL              __cpp(nn::applet::CTR::detail::CallUtility)
    ADD             SP, SP, #0xC
    POP             {PC}
}

__asm void LockTransition(u32 action,bool isForced){
    PUSH            {LR}
    SUB             SP, SP, #0x14
    MOV             R3, #0
    STR             R0, [SP,#0xC]
    STRB            R1, [SP,#0x10]
    ADD             R1, SP, #0x8
    MOV             R0, #5
    MOV             R2, #8
    STR             R3, [SP,#0x0]
    STR             R3, [SP,#0x4]
    BL              __cpp(nn::applet::CTR::detail::CallUtility)
    ADD             SP, SP, #0x14
    POP             {PC}
}

__asm void SleepIfShellClosed(){
    MOV             R1, #0
    PUSH            {LR}
    SUB             SP, SP, #0xC
    MOV             R0, #4
    MOV             R3, R1
    MOV             R2, R1
    STR             R1, [SP,#0x0]
    STR             R1, [SP,#0x4]
    BL              __cpp(nn::applet::CTR::detail::CallUtility)
    ADD             SP, SP, #0xC
    POP             {PC}
}

void ReplySleepQueryToManager(QueryReply reply){
    // TODO
}

} // detail

bool IsInitialized(){
    return CTR::detail::sIsInitialized;
}
}
}
}