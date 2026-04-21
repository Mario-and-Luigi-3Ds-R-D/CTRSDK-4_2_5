#include <nn/ptm/CTR/ptm_Api.h>
#include <nn/ptm/CTR/detail/ptm_PtmIpc.h>
#include <nn/srv/srv_Api.h>
#include <string.h>

// nasty ass butt hack used -O2 (smiley face)
namespace nn{
namespace ptm{
namespace CTR{

Result Initialize(){
    const char* portName = PORT_NAMES[1];
    if(detail::PtmIpc::sSession != 0){
        goto done;
    }
    {
        u32 len = strlen(portName);
        Result rc = nn::srv::GetServiceHandle(&detail::PtmIpc::sSession, portName, len, 0);
        u32 failed = rc.mResult >> 31;
        if(failed)
            return rc;
    }
done:
    Result isDone;
    isDone.mResult = 0;
    return isDone;
}

#ifdef NONMATCHING
#endif

Result Finalize(){
    Result pResult;
    if(detail::PtmIpc::sSession != 0){
        __asm{svc 0x23}
        if(pResult.IsFailure()){
            return pResult;
        }
        detail::PtmIpc::sSession = 0;
    }
    Result ret;
    ret.mResult = 0;
    return ret;
}
    
}
}
}