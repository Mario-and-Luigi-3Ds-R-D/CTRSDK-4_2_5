#include <nn/applet/applet_All.h>

namespace nn{
namespace applet{
namespace CTR{
namespace detail{
namespace APPLET{

const nn::Handle sSession = 0;

__asm Result AppletUtility(u32 id,u8 *pInParam,size_t inParamSize,u8 *pOutParam,size_t outParamSize,s32 *pReadLen){
    PUSH            {R4-R10,LR}
    LDR             R6, [SP,#0x24]
    LDR             R12, [SP,#0x20]
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R5, =0x4B00C2
    MOV             R9, #0
    STR             R5, [R4,#0x80]!
    ADD             R7, R4, #4
    STM             R7, {R0,R2,R12}
    MOV             R0, #0x400
    ORR             R0, R0, R2,LSL#14
    ORR             R0, R0, #2
    STRD            R0, R1, [R4,#0x10]
    MRC             p15, 0, R0,c13,c0, 3
    ADD             R5, R0, #0x180
    ORR             R0, R9, R12,LSL#14
    LDM             R5, {R7,R8}
    ORR             R0, R0, #2
    STM             R5, {R0,R3}
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32
    STM             R5, {R7,R8}
    ANDS            R1, R0, #0x80000000
    BMI             locret_12A374
    LDR             R0, [R4,#8]
    STR             R0, [R6]
    LDR             R0, [R4,#4]

locret_12A374
    POP             {R4-R10,PC}
}

__asm Result CancelLibraryApplet(bool isApplicationEnd){
    PUSH            {R0,R4,R5,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R0, =__cpp(0x003B0040)
    STR             R0, [R4,#0x80]!
    LDRB            R0, [SP,#0x0]
    STRB            R0, [R4,#4]
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R3-R5,PC}
}

__asm Result CancelParamater(bool isSenderCheck, AppletId senderId, bool isReceiverCheck, AppletId receiverId, bool* pIsCanceled){
    PUSH            {R0-R6,LR}
    LDR             R5, [SP,#0x20]
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R0, =0xF0100
    STR             R0, [R4,#0x80]!
    LDRB            R0, [SP,#0x0]
    STRB            R0, [R4,#4]
    STR             R1, [R4,#8]
    LDRB            R0, [SP,#0x8]
    STRB            R0, [R4,#0xC]
    LDR             R0, =__cpp(&sSession)
    STR             R3, [R4,#0x10]
    LDR             R0, [R0]
    SVC             0x32
    ANDS            R1, R0, #0x80000000
    BMI             loc_12A424
    LDRB            R0, [R4,#8]
    STRB            R0, [R5]
    LDR             R0, [R4,#4]

loc_12A424
    ADD             SP, SP, #0x10
    POP             {R4-R6,PC}
}

__asm Result CloseApplication(u8 *pParam,size_t paramSize,Handle handle){
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R12, =0x270044
    MOV             R3, #0
    STR             R12, [R4,#0x80]!
    ADD             LR, R4, #4
    STR             R2, [R4,#0xC]
    STM             LR, {R1,R3}
    ORR             R1, R3, R1,LSL#14
    STR             R0, [R4,#0x14]
    LDR             R0, =__cpp(&sSession)
    ORR             R1, R1, #2
    STR             R1, [R4,#0x10]
    LDR             R0, [R0]
    SVC             0x32
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

__asm Result Enable(AppletAttr appletAttr){
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R1, =0x30040
    STR             R1, [R4,#0x80]!
    STR             R0, [R4,#4]
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

__asm Result GetAppletManInfo(AppletPos appletPos,AppletPos *currentPos,AppletId *requestedAppletId,AppletId *homeMenuAppletId,AppletId *currentAppletId){
    PUSH            {R0-R8,LR}
    MOV             R5, R1
    MOV             R6, R2
    LDR             R8, [SP,#0x28]
    MOV             R7, R3
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R0, =0x50040
    STR             R0, [R4,#0x80]!
    LDRB            R0, [SP,#0x0]
    STRB            R0, [R4,#4]
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 
    ANDS            R1, R0, #0x80000000
    BMI             loc_11B548
    LDRB            R0, [R4,#8]
    STRB            R0, [R5]
    LDR             R0, [R4,#0xC]
    STR             R0, [R6]
    LDR             R0, [R4,#0x10]
    STR             R0, [R7]
    LDR             R0, [R4,#0x14]
    STR             R0, [R8]
    LDR             R0, [R4,#4]

loc_11B548
    ADD             SP, SP, #0x10
    POP             {R4-R8,PC}
}

__asm Result GetLockHandle(Handle *pMutexHandle,AppletAttr appletAttr,AppletAttr *pAttrDecided,bit32 *pMiscState){
    PUSH            {R4-R8,LR}
    MOV             R5, R0
    MOV             R6, R2
    MOV             R7, R3
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R0, =0x10040
    ADD             R4, R4, #0x80
    STRD            R0, R1, [R4]
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32
    ANDS            R1, R0, #0x80000000
    BMI             locret_10FB88
    LDR             R0, [R4,#8]
    STR             R0, [R6]
    LDR             R0, [R4,#0xC]
    STR             R0, [R7]
    LDR             R0, [R4,#0x14]
    STR             R0, [R5]
    LDR             R0, [R4,#4]

locret_10FB88
    POP             {R4-R8,PC}
}

__asm Result GlanceParameter(AppletId *pSenderId,AppletId receiverId,u32 *pCommand,u8 *pParam,size_t paramSize,s32 *pReadLen,Handle *pHandle){
    PUSH            {R4-R12,LR}
    MOV             R8, R0
    MOV             R9, R2
    ADD             R2, SP, #0x28
    LDM             R2, {R0,R10,R11}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R12, =0xE0080
    MOV             R2, #0
    STR             R12, [R4,#0x80]!
    STR             R1, [R4,#4]
    STR             R0, [R4,#8]
    MRC             p15, 0, R1,c13,c0, 3
    ADD             R5, R1, #0x180
    ORR             R0, R2, R0,LSL#14
    ORR             R0, R0, #2
    LDRD            R6, R7, [R5]
    STM             R5, {R0,R3}
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    ANDS            R1, R0, #0x80000000
    STRD            R6, R7, [R5]
    BMI             locret_12A4B4
    LDR             R0, [R4,#8]
    STR             R0, [R8]
    LDR             R0, [R4,#0xC]
    STR             R0, [R9]
    LDR             R0, [R4,#0x10]
    STR             R0, [R10]
    LDR             R0, [R4,#0x18]
    STR             R0, [R11]
    LDR             R0, [R4,#4]

locret_12A4B4
    POP             {R4-R12,PC}
}

__asm Result Initialize(AppletId appletId,AppletAttr appletAttr,Handle *pEventHandle_mesg,Handle *pEventHandle_cont){
    PUSH            {R4-R6,LR}
    MOV             R5, R2
    MOV             R6, R3
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R2, =0x20080
    STR             R2, [R4,#0x80]!
    STRD            R0, R1, [R4,#4]
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    ANDS            R1, R0, #0x80000000
    BMI             locret_10FB2C
    LDR             R0, [R4,#0xC]
    STR             R0, [R5]
    LDR             R0, [R4,#0x10]
    STR             R0, [R6]
    LDR             R0, [R4,#4]

locret_10FB2C
    POP             {R4-R6,PC}
}

__asm Result InquireNotification(AppletId appletId,AppletNotification *notification){
    PUSH            {R4-R6,LR}
    MOV             R5, R1
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R1, =0xB0040
    STR             R1, [R4,#0x80]!
    STR             R0, [R4,#4]
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    ANDS            R1, R0, #0x80000000
    BMI             locret_1239F0
    LDRB            R0, [R4,#8]
    STRB            R0, [R5]
    LDR             R0, [R4,#4]

locret_1239F0
    POP             {R4-R6,PC}
}

__asm Result IsRegistered(AppletId appletId,bool *pRegistered){
    PUSH            {R4-R6,LR}
    MOV             R5, R1
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R1, =0x90040
    STR             R1, [R4,#0x80]!
    STR             R0, [R4,#4]
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    ANDS            R1, R0, #0x80000000
    BMI             locret_1238A0
    LDRB            R0, [R4,#8]
    STRB            R0, [R5]
    LDR             R0, [R4,#4]

locret_1238A0
    POP             {R4-R6,PC}
}

__asm Result JumpToHomeMenu(u8 *pParam,size_t paramSize,Handle handle){
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R12, =0x2C0044
    MOV             R3, #0
    STR             R12, [R4,#0x80]!
    ADD             LR, R4, #4
    STR             R2, [R4,#0xC]
    STM             LR, {R1,R3}
    ORR             R1, R3, R1,LSL#14
    STR             R0, [R4,#0x14]
    LDR             R0, =__cpp(&sSession)
    ORR             R1, R1, #2
    STR             R1, [R4,#0x10]
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

__asm Result NotifyToWait(AppletId id){
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R1, =__cpp(0x00430040)
    STR             R1, [R4,#0x80]!
    STR             R0, [R4,#4]
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

__asm Result PrepareToStartSystemApplet(AppletId id){
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R1, =__cpp(0x00190040)
    STR             R1, [R4,#0x80]!
    STR             R0, [R4,#4]
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

__asm Result ReceiveParameter(AppletId *pSenderId,AppletId receiverId,u32 *pCommand,u8 *pParam,size_t paramSize,s32 *pReadLen,Handle *pHandle){
    PUSH            {R4-R12,LR}
    MOV             R8, R0
    MOV             R9, R2
    ADD             R2, SP, #0x28
    LDM             R2, {R0,R10,R11}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R12, =0xD0080
    MOV             R2, #0
    STR             R12, [R4,#0x80]!
    STR             R1, [R4,#4]
    STR             R0, [R4,#8]
    MRC             p15, 0, R1,c13,c0, 3
    ADD             R5, R1, #0x180
    ORR             R0, R2, R0,LSL#14
    ORR             R0, R0, #2
    LDRD            R6, R7, [R5]
    STM             R5, {R0,R3}
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    ANDS            R1, R0, #0x80000000
    STRD            R6, R7, [R5]
    BMI             locret_12A540
    LDR             R0, [R4,#8]
    STR             R0, [R8]
    LDR             R0, [R4,#0xC]
    STR             R0, [R9]
    LDR             R0, [R4,#0x10]
    STR             R0, [R10]
    LDR             R0, [R4,#0x18]
    STR             R0, [R11]
    LDR             R0, [R4,#4]

locret_12A540
    POP             {R4-R12,PC}
}

__asm Result ReplySleepNotificationComplete(){
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R1, =__cpp(0x003F0040)
    STR             R1, [R4,#0x80]!
    STR             R0, [R4,#4]
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

__asm Result ReplySleepQuery(AppletId id,AppletQueryReply reply){
    PUSH            {R0,R1,R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R1, =0x3E0080
    STR             R1, [R4,#0x80]!
    STR             R0, [R4,#4]
    LDRB            R0, [SP,#0x4]
    STRB            R0, [R4,#8]
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    ADD             SP, SP, #8
    POP             {R4,PC}
}

__asm Result SendCaptureBufferInfo(u8 *pParam,size_t paramSize){
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R3, =0x400042
    MOV             R2, #0
    STR             R3, [R4,#0x80]!
    STR             R1, [R4,#4]
    STR             R0, [R4,#0xC]
    LDR             R0, =__cpp(&sSession)
    ORR             R1, R2, R1,LSL#14
    ORR             R1, R1, #2
    STR             R1, [R4,#8]
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

__asm Result SendParameter(AppletId senderId,AppletId receiverId,u32 command,u8 *pParam,size_t paramSize,Handle pHandle){
    PUSH            {R4-R8,LR}
    ADD             R4, SP, #0x18
    LDM             R4, {R5,R12}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R7, =0xC0104
    MOV             R6, #0
    STR             R7, [R4,#0x80]!
    ADD             R8, R4, #4
    STM             R8, {R0-R2,R5,R6,R12}
    ORR             R0, R6, R5,LSL#14
    ADD             R6, R4, #0x1C
    ORR             R0, R0, #2
    STM             R6, {R0,R3}
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4-R8,PC}
}

__asm Result SleepSystem(bit64 awakeReason){
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R2, =0x420080
    STR             R2, [R4,#0x80]!
    STRD            R0, R1, [R4,#4]
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

__asm Result StartSystemApplet(AppletId id,u8 *pParam,size_t paramSize,Handle handle){
    PUSH            {R4-R6,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R5, =0x1F0084
    MOV             R12, #0
    STR             R5, [R4,#0x80]!
    ADD             R6, R4, #4
    STR             R3, [R4,#0x10]
    STM             R6, {R0,R2,R12}
    ORR             R0, R12, R2,LSL#14
    ORR             R0, R0, #2
    STRD            R0, R1, [R4,#0x14]
    LDR             R0, =__cpp(&sSession)
    LDR             R0, [R0]
    SVC             0x32 ; '2'
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4-R6,PC}
}

}
}
}
}
}