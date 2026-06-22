// Filename: snd_Api.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/snd/CTR/MPCore/snd_Api.h>
#include <nn/snd/CTR/MPCore/snd_OperateMaster.h>
#include <nn/snd/CTR/MPCore/snd_DspFxManager.h>
#include <nn/snd/CTR/MPCore/snd_MasterManager.h>
#include <nn/snd/CTR/MPCore/snd_Voice.h>
#include <nn/srv/srv_Api.h>
#include <nn/dsp/CTR/MPCore/dsp_Api.h>
#include <nn/os/ARM/os_MemoryBarrier.h>
#include <nn/os/os_Thread.h>

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

bool UpdateHeadphoneStatus(){
    // TODO
}

Result Initialize(){
    Result res;
    if(!sInitialized){
        NN_UTIL_RETURN_IF_FAILED(srv::Initialize());
        NN_UTIL_RETURN_IF_FAILED(internal::sDspsnd.Initialize(false));
        UpdateHeadphoneStatus();
        VoiceManager::GetInstance()->Initialize();
        MasterManager::GetInstance()->Initialize();
        DspFxManager::GetInstance()->Initialize();
        dsp::CTR::RegisterSleepWakeUpCallback(Sleep,WakeUp,OrderToWaitForFinalize);
        sIsSleep = false;
        sIsSleepPrepare = false;
        sIsWaitingForFinalize = false;
        sSyncState = 1;
        sInitialized = true;
        return ResultSuccess();
    }
    else{
        return Result(0x820abf9);
    }
}

Result Finalize(){
    Result res;
    if(!sInitialized){
        return ResultSuccess();
    }
    else{
        sInitialized = false;
        dsp::CTR::ClearSleepWakeUpCallback(Sleep,WakeUp,OrderToWaitForFinalize);
        DspFxManager::GetInstance()->Finalize();
        MasterManager::GetInstance()->Finalize();
        VoiceManager::GetInstance()->Finalize();
        if(!sIsWaitingForFinalize){
            internal::sDspsnd.Finalize(false);
        }
        return ResultSuccess();
    }
}



void Sleep(){
    if((sInitialized & ~ sIsSleep) != 0){
        sSleepEvent.Initialize(true);
        sIsSleepPrepare = true;
        internal::sDspsnd.Finalize(true);
        sIsSleep = true;
    }
}

void OrderToWaitForFinalize(){
    if((sInitialized) && (sIsSleep)){
        sIsWaitingForFinalize = true;
        sIsSleep = false;
        sIsSleepPrepare = false;
        os::ARM::DataSynchronizationBarrier();
        sSleepEvent.Signal();
    }
}

bool GetHeadphoneStatus(){
    return sIsHeadphoneConnected;
}

f32 GetSystemMasterVolume(){
    return MasterManager::GetInstance()->mMasterVolume;
}

bool SetSurroundDepth(f32 depth){
    return MasterManager::GetInstance()->SetSurroundDepth(depth);
}

void SetOutputBufferCount(s32 outputBufferCount){
    return MasterManager::GetInstance()->SetOutputBufferCount(outputBufferCount);
}

void SetMasterVolume(f32 fVolume){
    MasterManager::GetInstance()->SetMasterVolume(fVolume);
}

void SetSurroundSpeakerPosition(SurroundSpeakerPosition pos){
    return MasterManager::GetInstance()->SetSurroundSpeakerPosition(pos);
}

void WaitForDspSync(){
    NN_TASSERT_(sInitialized);
    NN_TASSERT_(sSyncState == SYNC_STATE_SEND);
    // TODO in decomp.me
}

void SendParameterToDsp(){
    NN_TASSERT_(sInitialized);
    if((!sIsSleep) && (!sIsWaitingForFinalize)){
        if(sSyncState){
            WaitForDspSync();
        }
        UpdateHeadphoneStatus();
        internal::sDspsnd.SendParameter();
        sSyncState = 1;
    }
}

Voice* AllocVoice(s32 priority, VoiceDropCallbackFunc callback, uptr userArg){
    NN_TASSERT_(sInitialized);
    VoiceManager::GetInstance()->AllocVoice(priority,callback,userArg);
}

void FreeVoice(Voice* pVoice){
    NN_TASSERT_(sInitialized);
    VoiceManager::GetInstance()->FreeVoice(pVoice);
}

}
}
}