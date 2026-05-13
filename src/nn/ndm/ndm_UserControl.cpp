#include <nn/ndm/ndm_UserControl.h>
#include <nn/ndm/ndm_Interface.h>
#include <nn/os/os_CriticalSection.h>
#include <nn/srv/srv_Api.h>
#include <nn/util/util_Result.h>
#include <nn/dbg/dbg_Break.h>
#include <string.h>

namespace nn{
namespace ndm{
namespace{
    static os::CriticalSection sCs;
}
namespace{
    static int sInitializedCount;
}

Result Initialize(){
    nn::os::CriticalSection::ScopedLock locker(sCs);
    size_t nameLen;
    Result result;

    if (sInitializedCount == 0){
        nn::srv::Initialize();
        nameLen = strlen(PORT_NAME_USER);
        result = nn::srv::GetServiceHandle(&CTR::detail::Interface::sSession, PORT_NAME_USER, nameLen, 0);
        NN_UTIL_RETURN_IF_FAILED(result);
    }
    ++sInitializedCount;
    return ResultSuccess();
}
// Suspends the current Daemons.
__asm Result SuspendDaemons(bit32 mask){
    NOP
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R1, =0x60040
    STR             R1, [R4,#0x80]!
    STR             R0, [R4,#4]
    LDR             R0, =__cpp(&CTR::detail::Interface::sSession)
    LDR             R0, [R0]
    SVC             0x32
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

}
}