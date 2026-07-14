// Filename: ndm_Interface.cpp
//
// Project: Horizon Decompilation

#include <nn/ndm/ndm_Interface.h>
#include <nn/os/ipc/os_Message.h>
#include <nn/svc.h>

namespace nn{
namespace ndm{
namespace CTR{
namespace detail{

nn::Handle Interface::sSession = 0;

Result Interface::OverrideDefaultDaemons(bit32 mask){
    MessageBuffer ipcMsg(GetMessageBuffer());
    ipcMsg.SetHeader(0x14, 1, 0, 0);
    ipcMsg.SetRaw(1, mask);


    nn::Result ipcResult = SendSyncRequest(sSession);
    if(ipcResult.IsFailure()){
        return ipcResult;
    }

    return ipcMsg.GetRaw<nn::Result>(1);
}

Result Interface::SuspendDaemons(bit32 mask){
    MessageBuffer ipcMsg(GetMessageBuffer());
    ipcMsg.SetHeader(6, 1, 0, 0);
    ipcMsg.SetRaw(1, mask);


    nn::Result ipcResult = SendSyncRequest(sSession);
    if(ipcResult.IsFailure()){
        return ipcResult;
    }

    return ipcMsg.GetRaw<nn::Result>(1);
}

}
}
}
}