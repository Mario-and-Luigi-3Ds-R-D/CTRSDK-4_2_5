#include <nn/dsp/CTR/MPCore/dsp_Api.h>
#include <nn/applet/CTR/applet_Wrapper.h>
#include <nn/err/CTR/err_Api.h>

#include <string.h>

u8 DSPSND_BEGIN[0xc234];

namespace nn{
namespace dsp{
namespace CTR{
namespace{
    static bool sIsSleepAcceptedCallbackCalled; // 0
    static bool sIsComponentLoaded; // 0x1
    static bool sIsSleeping; // 0x2
    static ushort sRegisteredProgMask; // 0x4
    static ushort sRegisteredDataMask; // 0x6
    static DSP* spDspSession; // 0x8
    static int sDspEventUsedFlag; // 0xc
    static DSP sDspSessionObject; // 0x10
    static Handle sDspSessionHandle; // 0x14
    static const u8* sRegisteredComponent;
    static size_t sRegisteredComponentSize;
}
namespace{
    static applet::CTR::SysSleepAcceptedCallbackInfo sSleepAcceptedCallbackInfo;
}

namespace{
    static uint sSleepCallback[8];
}
namespace{
    static uint sWakeUpCallback[8];
}
namespace{
    static uint sFinalizeCallback[8];
}


Result Initialize(){
    // TODO
}

void Finalize(){
    // TODO
}

inline Result LoadComponent(const u8* pComponent, size_t size, bit16 maskPram, bit16 maskDram){
    sRegisteredComponent = pComponent;
    sRegisteredComponentSize = size;
    sRegisteredProgMask = maskPram;
    sRegisteredDataMask = maskDram;
    return LoadComponentCore(pComponent, size, maskPram, maskDram);
}

inline Result LoadComponentCore(const u8* pComponent, size_t size, bit16 maskPram, bit16 maskDram){
    Result res;
    if((spDspSession == 0) || (sIsComponentLoaded)){
        return *(Result*)0xc8a0a7fc;
    }
    else{
        spDspSession->LoadComponent(pComponent,size,maskPram,maskDram,&sIsComponentLoaded);
    }
    return res;
}

Result LoadDefaultComponent(){
    return LoadComponent(DSPSND_BEGIN,0xc234);
}

Result UnloadComponent(){
    return UnloadComponentCore();
}

inline Result UnloadComponentCore(){
    Result res = ResultSuccess();
    if(sIsComponentLoaded){
        res = spDspSession->UnloadComponent();
        sIsComponentLoaded = false;
    }
    return res;
}

Result RegisterInterruptEvents(nn::Handle handle, s32 type, s32 port){
    // TODO
}

Result RecvData(u16 regNo, u16* pValue){
    // TODO
}

Result SendData(u16 regNo, u16 value){
    // TODO
}

Result RecvDataIsReady(u16 regNo, bool* pStatus){
    // TODO
}

Result SendDataIsEmpty(u16 regNo, bool* pStatus){
    // TODO
}

Result ConvertProcessAddressFromDspDram(uptr addressOnDsp, uptr* pAddressOnHost){
    *pAddressOnHost = 0xffffffff;
    if(spDspSession != 0){
        //spDspSession->DSP::ConvertProcessAddressFromDspDram(addressOnDsp,pAddressOnHost);
    }
    return (Result)0xc8a0a7f8;
}

Result ReadPipeIfPossible(int port, void* buffer, u16 length, u16* pLengthRead){
    // TODO
}

Result WriteProcessPipe(int port, const void* buffer, u32 length){
    // TODO
}

Result InvalidateDataCache(uptr addr, size_t size){
    // TODO
}

Result FlushDataCache(uptr addr, size_t size){
    Result res;
    if(spDspSession != 0){
        res; // spDspSession->FlushDataCache(addr,size);
        return res;
    }
    return (Result)0xc8a0a7f8;
}

bool IsComponentLoaded(){
    return sIsComponentLoaded;
}

bool Sleep(){
    if(!IsComponentLoaded())
        return false;
    if(sIsSleeping)
        return false;
    for(int i = 0; i < 8; i++)
        if(sSleepCallback[i])
            ((void (*)(void))sSleepCallback[i])();
    UnloadComponentCore();
    bool isSleep = true;
    sIsSleeping = true;
    return isSleep;
}

void WakeUp(){
    sIsSleepAcceptedCallbackCalled = 0;
    if(sIsSleeping){
        Result res;
        res = LoadComponentCore(sRegisteredComponent,sRegisteredComponentSize,sRegisteredProgMask,sRegisteredDataMask);
        NN_ERR_THROW_FATAL(res);
        for(int i = 0; i < 8; i++)
            if(sWakeUpCallback[i])
                ((void (*)(void))sSleepCallback[i])();
        sIsSleeping = false;
    }
}

void Awake(){
    if(sIsSleepAcceptedCallbackCalled)
        WakeUp();
}

void OrderToWaitForFinalize(){
    if(sIsSleeping){
        for(int i = 0; i < 8; i++){
            if(sFinalizeCallback[i])
                ((void (*)(void))sFinalizeCallback[i])();
        }
        sIsSleeping = false;
    }
}

bool RegisterSleepWakeUpCallback(void (*sleepCallback)(),void (*wakeUpCallback)(),void (*orderToWaitForFinalizeCallback)()){
    int i;
    for(i = 0; ; i++){
        if(i >= 8)
            return false;
        if((void(*)(void))sSleepCallback[i] == sleepCallback) break;
    }
    sSleepCallback[i] = (uint)sleepCallback;
    sWakeUpCallback[i] = (uint)wakeUpCallback;
    sFinalizeCallback[i] = (uint)orderToWaitForFinalizeCallback;
    return true;
}

bool ClearSleepWakeUpCallback(void (*sleepCallback)(),void (*wakeUpCallback)(),void (*orderToWaitForFinalizeCallback)()){
    int i;
    for(i = 0; ; i++){
        if(i >= 8)
            return false;
        if((void(*)(void))sSleepCallback[i] == sleepCallback) break;
    }
    sSleepCallback[i] = 0;
    sWakeUpCallback[i] = 0;
    sFinalizeCallback[i] = 0;
    return true;
}

}
}
}