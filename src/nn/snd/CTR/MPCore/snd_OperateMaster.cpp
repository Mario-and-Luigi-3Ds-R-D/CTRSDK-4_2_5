#include <nn/snd/CTR/MPCore/snd_OperateMaster.h>
#include <nn/snd/CTR/Common/snd_Const.h>
#include <nn/snd/CTR/MPCore/snd_MasterManager.h>
#include <nn/snd/CTR/MPCore/snd_Class.h>
#include <nn/snd/CTR/MPCore/snd_DspFxManager.h>
#include <nn/snd/CTR/MPCore/snd_Voice.h>
#include <nn/dsp/CTR/MPCore/dsp_Api.h>
#include <nn/os/os_Thread.h>
#include <nn/Assert.h>

#include <string.h>

#define NN_SND_DSP_OUTPUT_BUFFER_COUNT_MIN = 2;
#define NN_SND_DSP_OUTPUT_BUFFER_COUNT_MAX = 3;


#define NN_SND_RCF_SRCSEL_NONE = 0;
#define NN_SND_RCF_SRCSEL_LINEAR = 1;
#define NN_SND_RCF_SRCSEL_POLYPHASE = 1;

namespace nn {
namespace snd {
namespace CTR {

bool Dspsnd::AppendChannelNextBuffer(u8 ch_no, WaveBuffer* pWaveBuffer, s32 index){
    NN_TASSERT_(0 <= ch_no && ch_no < NN_SND_VOICE_NUM);
}

bool Dspsnd::AssignPCM(u8 ch_no, WaveBuffer* pWaveBuffer, DspsndAudioInfo i){
    NN_TASSERT_(0 <= ch_no && ch_no < NN_SND_VOICE_NUM);
}

bool Dspsnd::ChangePlayState(u8 ch_no, bool state){
    NN_TASSERT_(0 <= ch_no && ch_no < NN_SND_VOICE_NUM);
    if(dsp::CTR::IsComponentLoaded()){
        DspsndChannelDirect* pChannelDirect = this->GetChannelDirectAddr(ch_no);
        if(state){
            *(ushort*)&pChannelDirect->play_vars = *(ushort*)&pChannelDirect->play_vars & 0xff00 | 1;
        }
        else{
            *(ushort*)&pChannelDirect->play_vars = *(ushort*)&pChannelDirect->play_vars & 0xff00;
        }
        pChannelDirect->ctrl |= 0x10000;
        return true;
    }
    else{
        return false;
    }
}

bool Dspsnd::EnableAuxBus(AuxBusId busId, bool flag){
    if(dsp::CTR::IsComponentLoaded()){
        DspsndMasterDirect* pMasterDirect = this->GetMasterDirectAddr();
        pMasterDirect->param.isAuxEnabled[busId] = flag;
        if(busId == 0)
            pMasterDirect->ctrl |= 0x100;
        else if(busId == 1)
            pMasterDirect->ctrl |= 0x200;
        return true;
    }
    else{
        return false;
    }
}

Result Dspsnd::Initialize(bool isWakeUp){
    if (!dsp::CTR::IsComponentLoaded())
        return Result(0xC8A0A801);


    if (this->mIsInitialized)
        return ResultSuccess();
    this->mEventInterrupt.Initialize(true);

    Result result = dsp::CTR::RegisterInterruptEvents(this->mEventInterrupt.GetHandle(),2,2);
    
    if (result.IsFailure()){
        this->mEventInterrupt.Finalize();
        return result;
    }
    Handle h;
    result = dsp::CTR::GetSemaphoreEventHandle(&h);

    if (result.IsFailure())
        return result;
    if (h.IsValid())
        this->mEventSemaphore.SetHandle(h);
    else
        return result;

    dsp::CTR::SetSemaphoreEventMask(0x2000);

    this->mCriticalSection.Initialize();

    this->InitializeVariables(isWakeUp);

    if (isWakeUp){
        VoiceManager::GetInstance()->ForceUpdateParams();
        MasterManagerImpl::GetInstance()->ForceUpdateParams();
        DspFxManager::GetInstance();
        DspFxManagerImpl::GetInstance()->ForceUpdateParams();
    }
    else{
        this->mIsAuxCallbackInSendParameterEnabled = true;
        this->mpOutputCapture = NULL;
    }
    return ResultSuccess();
}

void Dspsnd::Finalize(bool isSleep){
    SndCommand cmd;
    fnd::TimeSpan span;
    ushort reply;
    Result res;
    if(isSleep){
        cmd.command = 3;
    }
    else{
        cmd.command = 1;
    }
    dsp::CTR::WriteProcessPipe(2,&cmd,4);
    while(true){
        reply = 0;
        bool ready;
        dsp::CTR::RecvDataIsReady(0,&ready);
        
        if (ready){
            dsp::CTR::RecvData(0,&reply);
        }
        if(reply == 1) break;
        os::Thread::Sleep(span.FromMilliSeconds(5));
    }
    if (isSleep) {
        memcpy(this->mSaveData,this->mpMasterStatusOnShare[0],0x1080);
    }
    this->mCriticalSection.Enter();
    this->mIsInitialized = false;
    this->mEventInterrupt.Finalize();
    dsp::CTR::RegisterInterruptEvents(this->mEventInterrupt.GetHandle(), 2,2);
    svc::CloseHandle(this->mEventSemaphore.GetHandle());
    this->mEventSemaphore.GetHandle();
    this->mEventSemaphore.ClearHandle();
    this->mCriticalSection.Leave();
    this->mCriticalSection.Finalize();
}

bool Dspsnd::InitializeChannelParameters(u8 ch_no){
    NN_TASSERT_(0 <= ch_no && ch_no < NN_SND_VOICE_NUM);
    if(dsp::CTR::IsComponentLoaded()){
        DspsndChannelDirect* pChannelDirect = this->GetChannelDirectAddr(ch_no);
        pChannelDirect->ctrl |= 0x20000000;
        return true;
    }
}

void Dspsnd::InitializeVariables(bool isWakeUp){
    // TODO
}

bool Dspsnd::ResetChannelNextBuffer(u8 channelId){
    NN_TASSERT_(0 <= ch_no && ch_no < NN_SND_VOICE_NUM);
    if(dsp::CTR::IsComponentLoaded()){
        DspsndChannelDirect* pChannelDirect = this->GetChannelDirectAddr(channelId);
        pChannelDirect->ctrl |= 0x10;
        return true;
    }
}

void Dspsnd::SendParameter(){
    if(dsp::CTR::IsComponentLoaded()){
        DspFxManager* pDspInstance = DspFxManager::GetInstance();
        s32* auxA = this->GetAusBusAddr(AUX_BUS_A);
        s32* auxB = this->GetAusBusAddr(AUX_BUS_B);
        if(this->mIsAuxCallbackInSendParameterEnabled){
            MasterManager::GetInstance()->AuxUserCallback(AUX_BUS_A,(uptr)auxA);
            MasterManager::GetInstance()->AuxUserCallback(AUX_BUS_B,(uptr)auxB);
        }
        MasterManager::GetInstance()->ExecuteEffect(AUX_BUS_A,(uptr)auxA);
        MasterManager::GetInstance()->ExecuteEffect(AUX_BUS_B,(uptr)auxB);
        VoiceManager::GetInstance()->UpdateParams();
        VoiceManager::GetInstance()->UpdateWaveBufferList();
        VoiceManager::GetInstance()->AdjustVoicePlayState(
            (this->mDspCyclesLimit - MasterManager::GetInstance()->GetDspCycles()) - pDspInstance->GetDspCycles(), 
            this->GetDspCyclesFrame());
        ushort* id = this->GetDirectIdAddrOnShared(this->mWritePage);
        *id = this->mDirectId;
        this->mDirectId++;
        this->mEventSemaphore.Signal();
        this->mWritePage = this->getCurrentPage();
        this->mProcessCount++;
    }
}

bool Dspsnd::SetAuxFrontBypass(AuxBusId busId, bool flag){
    if(dsp::CTR::IsComponentLoaded()){
        DspsndMasterDirect* pMasterDirect = this->GetMasterDirectAddr();
        pMasterDirect->param.isFrontBypassAux[busId] = flag;
        if(busId == 0)
            pMasterDirect->ctrl |= 0x40;
        else if(busId == 1)
            pMasterDirect->ctrl |= 0x80;
        return true;
    }
    else
        return false;
}

void Dspsnd::SetAuxReturnVolume(AuxBusId busId, f32 fVolume){
    if(dsp::CTR::IsComponentLoaded()){
        DspsndMasterDirect* pMasterDirect = this->GetMasterDirectAddr();
        pMasterDirect->param.volAux[busId].f32value = fVolume;
        if(busId == 0)
            pMasterDirect->ctrl |= 0x1000000;
        else if(busId == 1)
            pMasterDirect->ctrl |= 0x2000000;
    }
}

bool Dspsnd::SetChannelAdpcmParam(u8 ch_no, AdpcmParam* pParam){
    NN_TASSERT_(0 <= ch_no && ch_no < NN_SND_VOICE_NUM);
    if(dsp::CTR::IsComponentLoaded()){
        DspsndChannelDirect* pChannelDirect = this->GetChannelDirectAddr(ch_no);
        memcpy(this->GetChannelOptionAddr(ch_no),pParam,0x20);
        pChannelDirect->ctrl |= 4;
        return true;
    }
}

bool Dspsnd::SetChannelIIRFilter_Biquad(u8 ch_no, short n0, short n1, short n2, short d1, short d2){
    NN_TASSERT_(0 <= ch_no && ch_no < NN_SND_VOICE_NUM);
    if(dsp::CTR::IsComponentLoaded()){
        DspsndChannelDirect* pChannelDirect = this->GetChannelDirectAddr(ch_no);
        pChannelDirect->play_param.iir_coef_biqd[0] = d2;
        pChannelDirect->play_param.iir_coef_biqd[1] = d1;
        pChannelDirect->play_param.iir_coef_biqd[2] = n2;
        pChannelDirect->play_param.iir_coef_biqd[3] = n1;
        pChannelDirect->play_param.iir_coef_biqd[4] = n0;
        pChannelDirect->ctrl |= 0x1000000;
        return true;
    }
}

bool Dspsnd::SetChannelIIRFilter_Mono(u8 ch_no, short n0, short d1){
    NN_TASSERT_(0 <= ch_no && ch_no < NN_SND_VOICE_NUM);
    if(dsp::CTR::IsComponentLoaded()){
        DspsndChannelDirect* pChannelDirect = this->GetChannelDirectAddr(ch_no);
        pChannelDirect->play_param.iir_coef_mono[0] = n0;
        pChannelDirect->play_param.iir_coef_mono[1] = d1;
        pChannelDirect->ctrl |= 0x800000;
        return true;
    }
}

bool Dspsnd::SetChannelIiRFilterType(u8 ch, FilterType type){
    NN_TASSERT_(0 <= ch_no && ch_no < NN_SND_VOICE_NUM);
    if(dsp::CTR::IsComponentLoaded()){
        DspsndChannelDirect* pChannelDirect = this->GetChannelDirectAddr(ch);
        pChannelDirect->play_param.iir_type = type;
        pChannelDirect->ctrl |= 0x400000;
        return true;
    }
}

bool Dspsnd::SetChannelMix(u8 ch_no, MixParam* pChannelMix){
    NN_TASSERT_(0 <= ch_no && ch_no < NN_SND_VOICE_NUM);
    if(dsp::CTR::IsComponentLoaded()){
        DspsndChannelDirect* pChannelDirect = this->GetChannelDirectAddr(ch_no);
        memcpy16(&pChannelDirect->play_param,pChannelMix,0x10); // could all be wrong lmao
        memcpy16(&pChannelDirect->play_param.vol + 1,pChannelMix->auxBusA,0x10);
        memcpy16(&pChannelDirect->play_param.vol + 2,pChannelMix->auxBusB,0x10);
        pChannelDirect->ctrl |= 0xe000000;
        return true;
    }
}

bool Dspsnd::SetChannelPlayStart(u8 ch_no){
    return this->ChangePlayState(ch_no, true);
}

bool Dspsnd::SetChannelPlayStop(u8 ch_no){
    return this->ChangePlayState(ch_no, false);
}

bool Dspsnd::SetChannelRIM(u8 ch_no, DSPWord method, DSPWord coef){
    NN_TASSERT_(0 <= ch_no && ch_no < NN_SND_VOICE_NUM);
    if(dsp::CTR::IsComponentLoaded()){
        NN_TASSERT_(method == NN_SND_RCF_SRCSEL_POLYPHASE || 
            method == NN_SND_RCF_SRCSEL_LINEAR || 
            method == NN_SND_RCF_SRCSEL_NONE);
        DspsndChannelDirect* pChannelDirect = this->GetChannelDirectAddr(ch_no);
        pChannelDirect->play_param.rimSelect = pChannelDirect->play_param.rimSelect & 0xff00 | method & 0xff;
        if(!method){
            // NN_TASSERT_(co) idk what a snd_rcf is
            pChannelDirect->play_param.rimSelect = (pChannelDirect->play_param.rimSelect & 0xff) | (coef << 8);
        }
        pChannelDirect->ctrl |= 0x20000;
        return true;
    }
    else{
        return false;
    }
}

bool Dspsnd::SetChannelSyncCount(u8 ch_no, short synccount){
    if(dsp::CTR::IsComponentLoaded()){
        NN_TASSERT_(0 <= ch_no && ch_no < NN_SND_VOICE_NUM);
        DspsndChannelDirect* pChannelDirect = this->GetChannelDirectAddr(ch_no);
        pChannelDirect->play_vars.syncCount = synccount;
        pChannelDirect->ctrl |= 0x10000000;
        return true;
    } 
}

bool Dspsnd::SetChannelTimer(u8 ch_no, f32 timer){
    if(dsp::CTR::IsComponentLoaded()){
        NN_TASSERT_(mode == CLIPPING_MODE_NORMAL || 
            mode == CLIPPING_MODE_SOFT);
        DspsndChannelDirect* pChannelDirect = this->GetChannelDirectAddr(ch_no);
        pChannelDirect->play_param.timer = timer;
        pChannelDirect->ctrl |= 0x40000;
        return true;
    } 
}

bool Dspsnd::SetClippingMode(ClippingMode mode){
    if(dsp::CTR::IsComponentLoaded()){
        NN_TASSERT_(mode == CLIPPING_MODE_NORMAL || 
            mode == CLIPPING_MODE_SOFT);
        DspsndMasterDirect* pMasterDirect = this->GetMasterDirectAddr();
        pMasterDirect->param.clippingMode = mode;
        pMasterDirect->ctrl |= 0x8000000;
        return true;
    }
    else{
        return false;
    }
}

bool Dspsnd::SetDspDelayEffect(AuxBusId busId, DspFxDelayParams* params){
    if(dsp::CTR::IsComponentLoaded()){
        DspsndMasterDirect* pDirect = GetMasterDirectAddr();

        if(params->ctrl & 1)
            pDirect->param.fxDelayParams[busId].enable = params->enable;

        if(params->ctrl & 4){
            pDirect->param.fxDelayParams[busId].channels = params->channels;
            pDirect->param.fxDelayParams[busId].delayFrames = params->delayFrames;
            pDirect->param.fxDelayParams[busId].delayFeedbackGain = params->delayFeedbackGain;
            for(int i = 0; i < 2; i++)
                pDirect->param.fxDelayParams[busId].aLpfCoefs[i] = params->aLpfCoefs[i];
        }

        if(params->ctrl & 2)
            pDirect->param.fxDelayParams[busId].delayBufferAddress = params->delayBufferAddress;

        pDirect->param.fxDelayParams[busId].ctrl = pDirect->param.fxDelayParams[busId].ctrl | params->ctrl;

        if(busId == 0)
            pDirect->ctrl = pDirect->ctrl | 0x400;
        else if(busId == 1)
            pDirect->ctrl = pDirect->ctrl | 0x800;

        return true;
    }
    else{
        return false;
    }
}

bool Dspsnd::SetDspReverbEffect(AuxBusId busId, DspFxReverbParams* params){
    if(dsp::CTR::IsComponentLoaded()){
        DspsndMasterDirect* pDirect = GetMasterDirectAddr();
        if(params->ctrl & 1)
            pDirect->param.fxReverbParams[busId].enable = params->enable;

        if(params->ctrl & 4){
            pDirect->param.fxReverbParams[busId].channels = params->channels;
            pDirect->param.fxReverbParams[busId].earlyDelayFrames = params->earlyDelayFrames;
            pDirect->param.fxReverbParams[busId].preDelayFrames = params->preDelayFrames;
            for(int i = 0; i < 2; i++)
                pDirect->param.fxReverbParams[busId].combFrames[i] = params->combFrames[i];
            pDirect->param.fxReverbParams[busId].allPassFrames = params->allPassFrames;
            pDirect->param.fxReverbParams[busId].earlyGain = params->earlyGain;
            pDirect->param.fxReverbParams[busId].fusedGain = params->fusedGain;
            pDirect->param.fxReverbParams[busId].allPassCoef = params->allPassCoef;
            for(int i = 0; i < 2; i++)
                pDirect->param.fxReverbParams[busId].aCombCoefs[i] = params->aCombCoefs[i];
            for(int i = 0; i < 2; i++)
                pDirect->param.fxReverbParams[busId].aLpfCoefs[i] = params->aLpfCoefs[i];
        }

        if(params->ctrl & 2){
            pDirect->param.fxReverbParams[busId].earlyDelayBufferAddress = params->earlyDelayBufferAddress;
            pDirect->param.fxReverbParams[busId].preDelayBufferAddress = params->preDelayBufferAddress;
            pDirect->param.fxReverbParams[busId].combBufferAddress[0] = params->combBufferAddress[0];
            pDirect->param.fxReverbParams[busId].combBufferAddress[1] = params->combBufferAddress[1];
            pDirect->param.fxReverbParams[busId].allPassBufferAddress = params->allPassBufferAddress;
        }
        pDirect->param.fxReverbParams[busId].ctrl = pDirect->param.fxReverbParams[busId].ctrl | params->ctrl;

        if(busId == 0)
            pDirect->ctrl = pDirect->ctrl | 0x1000;
        else if(busId == 1)
            pDirect->ctrl = pDirect->ctrl | 0x2000;

        return true;
    }
    else{
        return false;
    }
}

bool Dspsnd::SetIsHeadsetConnected(bool isConnected){
    if(dsp::CTR::IsComponentLoaded()){
        DspsndMasterDirect* pMasterDirect = this->GetMasterDirectAddr();
        pMasterDirect->param.isHeadsetConnected = isConnected;
        pMasterDirect->ctrl |= 0x10000000;
    }
}

void Dspsnd::SetMasterVolume(f32 fVolume){
    if(dsp::CTR::IsComponentLoaded()){
        DspsndMasterDirect* pMasterDirect = this->GetMasterDirectAddr();
        pMasterDirect->param.volMaster.f32value = fVolume;
        pMasterDirect->ctrl |= 0x10000;
    }
}

void Dspsnd::SetOutputBufferCount(s32 n){
    NN_TASSERT_(n >= NN_SND_DSP_OUTPUT_BUFFER_COUNT_MIN && n <= NN_SND_DSP_OUTPUT_BUFFER_COUNT_MAX);
    if(dsp::CTR::IsComponentLoaded()){
        DspsndMasterDirect* pMasterDirect = this->GetMasterDirectAddr();
        pMasterDirect->param.outputBufferCount = n;
        pMasterDirect->ctrl |= 0x8000;
    }
}

bool Dspsnd::SetRearRatio(ushort ratio){
    if(dsp::CTR::IsComponentLoaded()){
        if(0x8000 < ratio)
            ratio = 0x8000;
        DspsndMasterDirect* pMasterDirect = this->GetMasterDirectAddr();
        pMasterDirect->param.rearRatio = ratio;
        pMasterDirect->ctrl |= 0x80000000;
        return true;
    }
    else{
        return false;
    }
}

bool Dspsnd::SetSoundOutputMode(OutputMode mode){
    if(dsp::CTR::IsComponentLoaded()){
        NN_TASSERT_(mode == OUTPUT_MODE_MONO || 
            mode == OUTPUT_MODE_STEREO || 
            mode == OUTPUT_MODE_3DSURROUND);
        DspsndMasterDirect* pMasterDirect = this->GetMasterDirectAddr();
        pMasterDirect->param.outputMode = mode;
        pMasterDirect->ctrl |= 0x4000000;
        return true;
    }
    else{
        return false;
    }
}

bool Dspsnd::SetSurroundDepth(ushort depth){
    if(dsp::CTR::IsComponentLoaded()){
        if(0x7fff < depth)
            depth = 0x7fff;
        DspsndMasterDirect* pMasterDirect = this->GetMasterDirectAddr();
        pMasterDirect->param.surroundDepth = depth;
        pMasterDirect->ctrl |= 0x20000000;
        return true;
    }
    else{
        return false;
    }
}

bool Dspsnd::SetSurroundSpeakerPosition(SurroundSpeakerPosition pos){
    if(dsp::CTR::IsComponentLoaded()){
        if((pos == SURROUND_SPEAKER_POSITION_SQUARE) || (pos == SURROUND_SPEAKER_POSITION_WIDE)){
            DspsndMasterDirect* pMasterDirect = this->GetMasterDirectAddr();
            pMasterDirect->param.surroundSpPosMode = pos;
            pMasterDirect->ctrl |= 0x40000000;
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

void Dspsnd::SetSyncMode(SyncMode mode){
    if(dsp::CTR::IsComponentLoaded()){
        DspsndMasterDirect* pMasterDirect = this->GetMasterDirectAddr();
        pMasterDirect->param.syncMode = mode;
        pMasterDirect->ctrl |= 0x10000;
    }
}

void Dspsnd::SyncFrameData(){
    if((dsp::CTR::IsComponentLoaded()) && (this->mIsInitialized)){
        u16* directId = this->GetDirectIdAddrOnShared(this->getNextPage());
        if(this->UpdateSlotId(*directId)){
            for(int id = 0; id < 0x18; id++){
                //VoiceManager::GetInstance()->UpdateStatus(id,this->GetChannelStatusAddr(id));
            }
            memcpy(&this->mDspCycles,this->GetDspCyclesAddr(),sizeof(DspsndDspCycles));
            if((this->mpOutputCapture) && (this->mpOutputCapture->mIsEnabled)){
                this->mpOutputCapture->Write(this->GetMixBusAddr(),0xa0);
            }
            MasterManager::GetInstance()->UpdateDroppedSoundFrameCount();
        }
    }
}

bool Dspsnd::UpdateChannelNextBuffer(u8 channelId, WaveBuffer* pWaveBuffer){
    NN_TASSERT_(0 <= channelId && channelId < NN_SND_VOICE_NUM);
    if(dsp::CTR::IsComponentLoaded()){
        DspsndChannelDirect* pDirect = this->GetChannelDirectAddr(channelId);
        DspsndChannelStatus* pStatus = this->GetChannelStatusAddr(channelId);

        if(pStatus->play_vars_rps.currentBufferId == pWaveBuffer->bufferId){
            pDirect->src_inf.bufferId = pWaveBuffer->bufferId;
            pDirect->src_inf.adpcmContext.yn1 = (pDirect->src_inf.adpcmContext.yn1 & ~2) | ((pWaveBuffer->loopFlag << 1) & 2);
            pDirect->src_inf.srcIniPlayLen = (pWaveBuffer->sampleLength >> 16) | (pWaveBuffer->sampleLength << 16);
            pDirect->ctrl = pDirect->ctrl | 8;
        }
        return true;
    }
    return false;
}

void Dspsnd::WaitPipe(){
    NN_TASSERT_(this->mEventInterrupt.IsValid());
    os::CriticalSection::ScopedLock lock(this->mCriticalSection);
    this->mEventInterrupt.Wait();
    this->mEventInterrupt.ClearSignal();
    this->mProcessCount++;
}

}
}
}