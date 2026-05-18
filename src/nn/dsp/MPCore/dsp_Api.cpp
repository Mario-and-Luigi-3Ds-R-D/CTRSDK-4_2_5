#include <nn/dsp/CTR/MPCore/dsp_Api.h>

namespace nn{
namespace dsp{
namespace CTR{
namespace{
    static bool sIsSleepAcceptedCallbackCalled; // 0
    static bool sIsComponentLoaded; // 0x1
    static bool sIsSleeping; // 0x2
    static short sRegisteredProgMask; // 0x4
    static short sRegisteredDataMask; // 0x6
    static DSP* spDspSession; // 0x8
    static int sDspEventUsedFlag; // 0xc
    static DSP sDspSessionObject; // 0x10
    static int uunk; // 0x14
    static int sRegisteredComponent;
    static int sRegisteredComponentSize;
}

void Awake(){
    if(sIsSleepAcceptedCallbackCalled != false){
        WakeUp();
    }
}

Result ConvertProcessAddressFromDspDram(uptr addressOnDsp, uptr* pAddressOnHost){
    *pAddressOnHost = 0xffffffff;
    if(spDspSession != 0){
        //spDspSession->DSP::ConvertProcessAddressFromDspDram(addressOnDsp,pAddressOnHost);
    }
    return (Result)0xc8a0a7f8;
}

Result FlushDataCache(uptr addr, size_t size){
    Result res;
    if(spDspSession != 0){
        res; // spDspSession->FlushDataCache(addr,size);
        return res;
    }
    return (Result)0xc8a0a7f8;
}

}
}
}