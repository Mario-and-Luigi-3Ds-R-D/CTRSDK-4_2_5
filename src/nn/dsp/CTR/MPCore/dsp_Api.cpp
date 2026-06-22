#include <nn/dsp/CTR/MPCore/dsp_Api.h>
#include <nn/dsp/CTR/dsp_Result.h>
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
void (*sSleepCallback[8])(void);
void (*sWakeUpCallback[8])(void);
void (*sFinalizeCallback[8])(void);
}


/*Result Initialize(){
    if (spDspSession != NULL)
        return ResultSuccess();

    NN_UTIL_RETURN_IF_FAILED(nn::srv::Initialize());

    NN_UTIL_RETURN_IF_FAILED(InitializeIpc(&sDspSessionHandle));

    spDspSession = &sDspSessionObject;
    sDspSessionObject = DSP(sDspSessionHandle);

    for (int i = 0; i < 8; i++){
        sFinalizeCallback[i] = NULL;
        sWakeUpCallback[i]   = NULL;
        sSleepCallback[i]    = NULL;
    }

    sIsComponentLoaded       = false;
    sRegisteredComponent     = NULL;
    sRegisteredComponentSize = 0;
    sRegisteredProgMask      = 0;
    sRegisteredDataMask      = 0;
    sIsSleeping              = false;

    sSleepAcceptedCallbackInfo.applet::CTR::SysSleepAcceptedCallbackInfo::Register();

    return ResultSuccess();
}*/

void Finalize(){
    if (spDspSession == NULL)
        return;

    sSleepAcceptedCallbackInfo.Unregister();

    svc::CloseHandle(sDspSessionHandle);

    spDspSession = NULL;
    sDspSessionHandle = nn::Handle(); // invalid handle value
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
        return ResultNotInitialized();
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
    Result res;
    ResultNotInitialized();
    if(spDspSession){
        res = spDspSession->RecvData(regNo,pValue);
    }
    return res;
}

Result RecvDataIsReady(u16 regNo, bool* pStatus){
    Result res;
    ResultNotInitialized();
    if(spDspSession){
        res = spDspSession->RecvDataIsReady(regNo,pStatus);
    }
    return res;
}

Result ConvertProcessAddressFromDspDram(uptr addressOnDsp, uptr* pAddressOnHost){
    Result res;
    ResultNotInitialized();
    *pAddressOnHost = 0xffffffff;
    if(spDspSession){
        spDspSession->ConvertProcessAddressFromDspDram(addressOnDsp,pAddressOnHost);
    }
    return res;
}

Result ReadPipeIfPossible(int port, void* buffer, u16 length, u16* pLengthRead){
    // TODO
}

Result WriteProcessPipe(int port, const void* buffer, u32 length){
    Result res;
    ResultNotInitialized();
    if(spDspSession){
        res = spDspSession->WriteProcessPipe(port,(u8*)buffer,length);
    }
    return res;
}

Result FlushDataCache(uptr addr, size_t size){
    Result res;
    ResultNotInitialized();
    if(spDspSession){
        Handle h;
        res = spDspSession->FlushDataCache(h,addr,size);
    }
    return res;
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
    sSleepCallback[i] = sleepCallback;
    sWakeUpCallback[i] = wakeUpCallback;
    sFinalizeCallback[i] = orderToWaitForFinalizeCallback;
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