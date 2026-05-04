#pragma once

#include <nn/Result.h>
#include <nn/snd/CTR/Common/snd_Types.h>
#include <nn/snd/CTR/MPCore/snd_Voice.h>
#include <nn/snd/CTR/MPCore/snd_OutputCapture.h>
#include <nn/snd/CTR/MPCore/snd_FxDelay.h>
#include <nn/snd/CTR/MPCore/snd_FxReverb.h>

namespace nn {
namespace snd {
namespace CTR {

static const s32 NN_SND_DSP_MAXIMUM_CYCLES = 622535;

Result Initialize();
Result Finalize();

void InitializeWaveBuffer(WaveBuffer* pWaveBuffer);

Result StartSoundThread(void (*callback)(uptr), uptr arg, uptr stackBuffer, size_t stackSize, s32 prio);
Result StartUserSoundThread(uptr stackBuffer, size_t stackSize, s32 prio);
Result StartSoundThread(const ThreadParameter* mainThreadParam, void (*mainThreadCallback)(uptr), uptr mainThreadArg, const ThreadParameter* userThreadParam, void (*userThreadCallback)(uptr), uptr userThreadArg, s32 coreNo);

void FinalizeSoundThread();
inline void FinalizeUserSoundThread() {}

void EnableSoundThreadTickCounter(bool enable);
nn::os::Tick GetSoundThreadTick();

void LockSoundThread();
void UnlockSoundThread();

Result FlushDataCache(uptr addr, size_t size);
Result InvalidateDataCache(uptr addr, size_t size);

void WaitForDspSync();
void WaitForDspSync(nn::os::Tick* pTick);
void SendParameterToDsp();

s32 GetSampleLength(s32 size, SampleFormat format, s32 channelCount);

void SetMasterVolume(f32 volume);
f32  GetMasterVolume();

void SetAuxReturnVolume(AuxBusId busId, f32 volume);
f32  GetAuxReturnVolume(AuxBusId busId);

void RegisterAuxCallback(AuxBusId busId, AuxCallback callback, uptr userData);
void GetAuxCallback(AuxBusId busId, AuxCallback* pCallback, uptr* pUserData);
void ClearAuxCallback(AuxBusId busId);
bool SetAuxFrontBypass(AuxBusId busId, bool flag);

bool         SetSoundOutputMode(OutputMode mode);
OutputMode   GetSoundOutputMode();

bool         SetClippingMode(ClippingMode mode);
ClippingMode GetClippingMode();

bool SetRearRatio(f32 depth);
bool SetSurroundDepth(f32 depth);
bool SetSurroundSpeakerPosition(SurroundSpeakerPosition pos);

void SetMaximumDspCycles(s32 cycles);
s32  GetMaximumDspCycles();
s32  GetDspCycles();

void Sleep();
void WakeUp();
void OrderToWaitForFinalize();

bool GetHeadphoneStatus();
bool UpdateHeadphoneStatus();

inline Result SetHeadphoneOutOnShellClose(bool forceout) { return dsp::ForceHeadphoneOut(forceout); }

bool GetMixedBusData(s16* pData, s32 nSamplesPerFrame);

s32  GetDroppedSoundFrameCount();
void ClearDroppedSoundFrameCount();

void EncodeAdpcmData(s16* pInput, u8* pOutput, s32 nSamples, s32 sampleRate, s32 loopStart, s32 loopEnd, DspsndAdpcmHeader* pInfo);
void DecodeAdpcmData(const u8* pInput, s16* pOutput, const AdpcmParam& param, AdpcmContext& context, s32 nSamples);
s32  GetAdpcmOutputBufferSize(s32 nSamples);
u32  ConvertAdpcmPos2Nib(u32 nPos);
u32  ConvertAdpcmNib2Pos(u32 nNib);

bool SetEffect(AuxBusId busId, FxDelay* fx);
bool SetEffect(AuxBusId busId, FxReverb* fx);
void ClearEffect(AuxBusId busId);

void     SetOutputBufferCount(s32 count);
s32      GetOutputBufferCount();
void     SetSyncMode(SyncMode mode);
SyncMode GetSyncMode();

} // namespace CTR
} // namespace snd
} // namespace nn