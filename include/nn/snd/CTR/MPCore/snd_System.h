#pragma once

#include "nn/types.h"
#include "nn/snd/CTR/MPCore/snd_PrivateDefinition.h"
#include "nn/os/os_Event.h"
#include "nn/os/os_CriticalSection.h"

using namespace nn::os;

namespace nn {
namespace snd {
namespace CTR {
    class Dspsnd;
namespace internal{
    extern Dspsnd sDspsnd;
}

typedef ushort DSPWord;
class Dspsnd{
protected:
    Event mEventInterrupt;
    Event mEventSemaphore;
    CriticalSection mCriticalSection;
    OutputCapture* mpOutputCapture;
    u8 mSaveData[4224];
    ushort* mpDirectIdOnShare[2];
    DspsndMasterDirect* mpMasterDirectOnShare[2];
    DspsndMasterStatus* mpMasterStatusOnShare[2];
    DspsndChannelDirect* mpChannelDirectOnShare[2][24];
    DspsndChannelStatus* mpChannelStatusOnShare[2][24];
    DspsndChannelOption* mpChannelOptionOnShare[2][24];
    s32* mpAuxBusOnShare[2][2];
    short* mpMixBusOnShare[2];
    ushort* mpCompressorTableOnShare[2];
    DspsndDspCycles* mpDspCyclesOnShare[2];
    bool mIsInitialized;
    u8 mProcessCount;
    ushort mDirectId;
    ushort mReadPage;
    ushort mWritePage;
    s32 mDspCyclesLimit;
    DspsndDspCycles mDspCycles;
    short* mpSpacialCoeffsOnShare[2];
    short* mpDirectionCoeffsSpOnShare[2];
    short* mpDirectionCoeffsHpOnShare[2];
    s32* mpSurroundlirCoeffsSpOnShare[2];
    s32* mpSurroundlirCoeffsHpOnShare[2];
    bool mIsAuxCallbackInSendParameterEnabled;
public:
    bool AppendChannelNextBuffer(u8* ch_no, WaveBuffer* pWaveBuffer, s32 index);
    bool AssignPCM(u8* ch_no, WaveBuffer* pWaveBuffer, DspsndAudioInfo i);
    bool EnableAuxBus(AuxBusId busId, bool flag);
    void Finalize(bool isSleep);
    int GetDroppedFrameCount();
    Result Initialize(bool isWakeup);
    bool InitializeChannelParameters(u8* ch_no);
    void InitializeVariables(bool isWakeup);
    bool ResetChannelNextBuffer(u8 channelId);
    void SendParameter();
    bool SetAuxFrontBypass(AuxBusId busId, bool flag);
    void SetAuxReturnVolume(AuxBusId busId, f32 volume);
    void SetChannelAdpcmParam(u8 ch_no, AdpcmParam* pParam);
    bool SetChannelIIRFilter_Biquad(u8 ch_no,s16 n0,s16 n1,s16 n2,s16 d1,s16 d2);
    bool SetChannelIIRFilter_Mono(u8 ch_no,s16 n0,s16 d1);
    bool SetChannelMix(u8 ch_no,MixParam *p_channelMix);
    bool SetChannelPlayStart(u8 ch_no);
    bool SetChannelPlayStop(u8 ch_no);
    bool SetChannelIRIM(u8 ch_no,DSPWord method,DSPWord coef);
    bool SetChannelSyncCount(u8 ch_no,short sync_count);
    bool SetChannelTimer(u8 ch_no, f32 timer);
    bool SetClippingMode(ClippingMode mode);
    bool SetDspDelayEffect(AuxBusId busId, DspFxDelayParams* params);
    bool SetDspReverbEffect(AuxBusId busId, DspFxReverbParams* params);

    inline bool ChangeState(u8 ch_no, bool state);
    inline s32* GetAusBusAddr(AuxBusId id){ return this->mpAuxBusOnShare[this->mReadPage][id]; }
    inline DspsndChannelDirect* GetChannelDirectAddr(u8 ch){ u32 page = this->getCurrentPage(); return this->mpChannelDirectOnShare[page][ch]; }
    inline DspsndChannelOption* GetChannelOptionAddr(u8 ch){ return this->mpChannelOptionOnShare[this->mWritePage][ch]; }
    inline DspsndChannelStatus* GetChannelStatusAddr(u8 ch){ return this->mpChannelStatusOnShare[this->mReadPage][ch]; }
    inline u32 getCurrentPage(){ this->mDirectId & 1; }
    inline ushort* GetDirectIdAddrOnShared(int page){ this->mpDirectIdOnShare[page]; }
    inline DspsndDspCycles* GetDspCyclesAddr(){ return this->mpDspCyclesOnShare[this->mReadPage]; }
    inline s32 GetDspCyclesFrame(){ return this->mDspCycles.ch0.frame; }
    inline Dspsnd* GetInstance(){ return &internal::sDspsnd; }
    inline DspsndMasterDirect* GetMasterDirectAddr(){ return this->mpMasterDirectOnShare[this->mWritePage]; }
    inline DspsndMasterStatus* GetMasterStatusAddr(){ return this->mpMasterStatusOnShare[this->mReadPage]; }
    inline short* GetMixBusAddr(){ return this->mpMixBusOnShare[this->mReadPage]; }
    inline u32 getNextPage(){ u32 page = this->getCurrentPage(); return page + 1 & 1; }
    inline bool SetIsHeadSet(bool flag);
};

} // namespace CTR
} // namespace snd
} // namespace nn