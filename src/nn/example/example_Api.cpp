#include "example_Api.h"
#include <nn/types.h>
#include <nn/util/util_Result.h>

namespace nn{
namespace LF_Library{
namespace{
    const char PORT_NAME_YOUR_MOM[] = "lf:yourmom";
    static bool sInitialized;
}
namespace ipc{
    extern Handle sSession;
}

void Initialize(){
    size_t nameLen;
    Result res;
    if(!sInitialized){
        /* Initialize Service Port. */

        res = srv::Initialize();
        nameLen = strlen(PORT_NAME_YOUR_MOM);

        /* ipc Session, PortName, nameLen STRLEN, 0 for flags. */

        if(srv::GetServiceHandle(&ipc::sSession, PORT_NAME_YOUR_MOM, nameLen, 0).IsFailure()){
            NN_TPANIC_("[LF_Library::Initialize()] Not initialized.\n");
        }

        /* Set Initialize to true, making the lib initialized. */
        sInitialized = true;
    }
}

void Finalized(){
    Result res;
    if(sInitialized){
      if(svc::CloseHandle(ipc::sSession).IsFailure()){
        NN_TPANIC_("Library still initialized.\n");
        sInitialized = false;
      }
    }
}
}
}