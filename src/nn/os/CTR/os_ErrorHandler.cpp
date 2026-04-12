#include <nn/os/CTR/os_ErrorHandler.h>
#include <nn/err/CTR/err_FatalErr.h>
#include <nn/dbg/dbg_Break.h>


namespace nn{
namespace os{
namespace CTR{
namespace detail{
void SetInternalErrorHandlingMode(bool preferFatal){
    nn::os::CTR::detail::sPreferFatal = preferFatal;
    return;
}

__asm void HandleInternalError(Result result){
var_4           = -4

    LDR             R2, =0x1FF80000
    LDR             R3, =0x6D305C // ARMCC Hates my guts so I hardwired it. It goes to nn::os::CTR::detail::sPreferFatal in the OG.
    PUSH            {R4,LR}
    TST             R0, #0x80000000
    LDRB            R2, [R2,#0x14]
    LDRSB           R3, [R3]
    MOV             R1, R0,LSR#27
    SUBNE           R1, R1, #0x20
    AND             R2, R2, #1
    ORRS            R2, R2, R3
    BEQ             loc_1210C4
    CMN             R1, #7

loc_1210AC
    CMPNE           R1, #1
    BEQ             locret_1210E0
    LDR             R2, [SP,#8+var_4]
    POP             {R4,LR}

loc_1210BC
    MOV             R1, #0
    B               __cpp(nn::err::CTR::ThrowFatalErr)

loc_1210C4
    CMN             R1, #1
    BNE             loc_1210D8
    LDR             R2, [SP,#8+var_4]
    MOV             R1, #0

loc_1210D4
    BL              __cpp(nn::err::CTR::ThrowFatalErr)

loc_1210D8
    POP             {R4,LR}
    B               __cpp(nndbgPanic)

locret_1210E0
    POP             {R4,PC}
}

}
}
}
}