#include <nn/ptm/CTR/ptm_Api.h>
#include <nn/ptm/CTR/detail/ptm_PtmIpc.h>
#include <nn/srv/srv_Api.h>
#include <string.h>

// nasty ass butt hack used -O2 (smiley face)
namespace nn{
namespace ptm{
namespace CTR{

#pragma O2

Result Initialize(){
    const char* portName = PORT_NAMES[1];
    if(detail::PtmIpc::sSession != 0){
        goto done;
    }{
        u32 len = strlen(portName);
        Result res = nn::srv::GetServiceHandle(&detail::PtmIpc::sSession, portName, len, 0);
        u32 failed = res.mResult >> 31;
        if(failed)
            return res;
    }
done:
    Result isDone; isDone.mResult = 0;
    return isDone;
}

#pragma O3


Result Finalize(){
/*    if(detail::PtmIpc::sSession != 0){
        svc::CloseHandle(detail::PtmIpc::sSession);

    }*/
}
    
}
}
}