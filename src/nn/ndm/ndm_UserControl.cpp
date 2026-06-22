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

    if (!sInitializedCount){
        nn::srv::Initialize();
        nameLen = strlen(PORT_NAME_USER);
        result = nn::srv::GetServiceHandle(&CTR::detail::Interface::sSession, PORT_NAME_USER, nameLen, 0);
        NN_UTIL_RETURN_IF_FAILED(result);
    }
    ++sInitializedCount;
    return ResultSuccess();
}

Result SuspendDaemons(bit32 mask){
    return CTR::detail::Interface::SuspendDaemons(mask);
}

}
}