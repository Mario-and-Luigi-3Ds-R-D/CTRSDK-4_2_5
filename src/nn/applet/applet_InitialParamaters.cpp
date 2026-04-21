#include <nn/applet/CTR/applet_InitialParamaters.h>

namespace nn{
namespace applet{ 
namespace CTR { 
namespace detail {
namespace {
    //u8* sInitializeParamBuffer[4096];
    bool sIsInitializedParamVaild;
    u8 sInitialWakeupState;
    short rev;
    int sSenderId;
    int sInitialSize;
}
namespace {
    u8* sInitializeParamBuffer[4096];
}

u8* GetInitialParamBuffer(){
    return (u8*)sInitializeParamBuffer;
}

void SetInitialParamSenderId(AppletId id){
    sSenderId = id;
}

void SetInitialParamSenderSize(s32 size){
    sInitialSize = size;
}

void SetInitialParamValid(){
    sIsInitializedParamVaild = 1;
}

void SetInitialWakeupState(WakeupState state){
    sInitialWakeupState = state;
}

}
}
}
}