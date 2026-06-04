// Filename: snd_Api.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/snd/CTR/MPCore/snd_Api.h>
#include <nn/snd/CTR/MPCore/snd_System.h>
#include <nn/snd/CTR/MPCore/snd_DspFxManager.h>
#include <nn/snd/CTR/MPCore/snd_MasterManager.h>
#include <nn/srv/srv_Api.h>
#include <nn/dsp/CTR/MPCore/dsp_Api.h>
#include <nn/os/ARM/os_MemoryBarrier.h>

namespace nn{
namespace snd{
namespace CTR{
namespace{
    static bool sInitialized;
    static bool sIsSleep;
    static bool sIsSleepPrepare;
    static bool sIsWaitingForFinalize;
    static bool sIsHeadphoneConnected;
    static s8 sSyncState;
    static os::LightEvent sSleepEvent; 
}

Result Initialize(){
    Result res;
    if(sInitialized == false){
        res.mResult = srv::Initialize().IsFailure();
//        if(res.mResult )
    }
}

/*Result Finalize(){
    Result res;
    if(sInitialized){
        sInitialized = false;
        dsp::CTR::ClearSleepWakeUpCallback(CTR::Sleep,CTR::WakeUp,CTR::OrderToWaitForFinalize);
        DspFxManager::GetInstance()->Finalize();
        MasterManager::GetInstance()->Finalize();
        VoiceManager::GetInstance()->Finalize();
        if(!sIsWaitingForFinalize){
            Dspsnd::GetInstance->Finalize(0);
        }
    }
    return ResultSuccess();
}*/



void Sleep(){
    if((sInitialized & ~ sIsSleep) != 0){
        sSleepEvent.Initialize(true);
        sIsSleepPrepare = true;
        internal::sDspsnd.Finalize(true);
        sIsSleep = true;
    }
}

void OrderToWaitForFinalize(){
    if(sInitialized){
        if(sIsSleep){
            sIsWaitingForFinalize = true;
            sIsSleep = false;
            sIsSleepPrepare = false;
            os::ARM::DataSynchronizationBarrier();
            sSleepEvent.Signal();
        }
    }
}

bool GetHeadphoneStatus(){
    return sIsHeadphoneConnected;
}



}
}
}