#pragma once

#include "nn/handle.h"

namespace nn {
namespace dsp {
namespace CTR {
namespace detail {
    Result InitializeBase(nn::Handle* pSession, const char* name);
    Result FinalizeBase(nn::Handle* pSession);
}
namespace {
    const char PORT_NAME_DSP[] = "dsp::DSP";
}

inline Result InitializeIpc(nn::Handle* pSession) { return detail::InitializeBase(pSession, PORT_NAME_DSP); }
inline Result FinalizeIpc(nn::Handle* pSession)   { return detail::FinalizeBase(pSession); }

Result Initialize();
void   Finalize();

Result LoadComponent(const u8 pComponent[], size_t size, bit16 maskPram = 0xff, bit16 maskDram = 0xff);
Result LoadComponentCore(const u8 pComponent[], size_t size, bit16 maskPram = 0xff, bit16 maskDram = 0xff);
Result LoadDefaultComponent();
Result UnloadComponent();
Result UnloadComponentCore();

Result RegisterInterruptEvents(nn::Handle handle, s32 type, s32 port = 0);
Result RecvData(u16 regNo, u16* pValue);
Result SendData(u16 regNo, u16 value);
Result RecvDataIsReady(u16 regNo, bool* pStatus);
Result SendDataIsEmpty(u16 regNo, bool* pStatus);

Result GetVirtualAddress(uptr physicalAddress, uptr* pVirtualAddress);
Result GetPhysicalAddress(uptr address, uptr* pPhysicalAddress);
Result ConvertProcessAddressFromDspDram(uptr addressOnDsp, uptr* pAddressOnHost);

Result ReadPipeIfPossible(int port, void* buffer, u16 length, u16* pLengthRead);
Result WriteProcessPipe(int port, const void* buffer, u32 length);

Result CheckSemaphoreRequest(bool* pIsRequested);
Result ClearSemaphore(u16 mask);
Result MaskSemaphore(u16 mask);
Result GetSemaphore(u16* pMask);
Result SetSemaphore(u16 mask);
Result GetSemaphoreEventHandle(nn::Handle*);
Result SetSemaphoreEventMask(bit16);

Result FlushDataCache(uptr addr, size_t size);
Result InvalidateDataCache(uptr addr, size_t size);

bool IsComponentLoaded();
bool Sleep();
void WakeUp();
void Awake();
void OrderToWaitForFinalize();

bool RegisterSleepWakeUpCallback(void (*sleepCallback)(),void (*wakeUpCallback)(),void (*orderToWaitForFinalizeCallback)() = nullptr);
bool ClearSleepWakeUpCallback(void (*sleepCallback)(),void (*wakeUpCallback)(),void (*orderToWaitForFinalizeCallback)() = nullptr);

Result GetHeadphoneStatus(bool* isConnected);
Result ForceHeadphoneOut(bool forceout);
bool   IsDspOccupied();

} // namespace CTR
} // namespace dsp
} // namespace nn