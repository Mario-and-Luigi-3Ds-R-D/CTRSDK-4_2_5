#include <nn/fs/fs_Api.h>
#include <nn/fs/fs_Paramaters.h>
#include <nn/err/CTR/err_Api.h>
#include <nn/cfg/CTR/cfg_Api.h>
#include <nn/srv/srv_Api.h>
#include <string.h>

namespace nn{
namespace fs{
// hacky but it matches kinda
#ifdef NONMATCHING_STRBNE
#endif

void InitializeLatencyEmulation(void) {

}

// Not Finished
void Initialize(){
    Result servHandle;
    size_t nameLen;
    Result isInit = IsInitialized().IsFailure();

    servHandle = srv::Initialize().IsFailure();
    if(servHandle != 0){
        NN_ERR_THROW_FATAL_ALL(servHandle);
    }
    nameLen = strlen(detail::PORT_NAME_USER);
    servHandle = srv::GetServiceHandle(&sFileServerSession, detail::PORT_NAME_USER,nameLen,0).IsFailure();
    if(servHandle != 0){
        NN_ERR_THROW_FATAL_ALL(servHandle);
    }
}

}
}