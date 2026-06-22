#pragma once

#include "nn/gxlow/gxlow_GpuClient.h"

typedef enum nngxlowInterrupt {
    NN_GXLOW_INTERRUPT_GPU_PSC_0=0,
    NN_GXLOW_INTERRUPT_GPU_PSC_1=1,
    NN_GXLOW_INTERRUPT_GPU_PDC_0=2,
    NN_GXLOW_INTERRUPT_GPU_PDC_1=3,
    NN_GXLOW_INTERRUPT_GPU_PPF=4,
    NN_GXLOW_INTERRUPT_GPU_P3D=5,
    NN_GXLOW_INTERRUPT_DMAC_0=6,
    NN_GXLOW_NUM_INTERRUPTS=7
} nngxlowInterrupt;

typedef uptr (*nngxlowFuncPtr)(void);

#ifdef __cplusplus
extern "C" {
#endif

void nngxlowInitialize();
bool nngxlowIsFirstInitialization();

void nngxlowFinalize();

s32 nngxlowGetNumSpeculativeRequests();

nngxlowFuncPtr nngxlowRegisterInterruptHandler(nngxlowFuncPtr interruptHandler,nngxlowInterrupt type);

void nngxlowLock();
void nngxlowUnlock();

void nngxlowYieldThread();



#ifdef __cplusplus
}
#endif
namespace nn{
namespace gxlow{
namespace CTR{
    class InterruptReceiver;

    void Initialize();
    bool IsInitialized();
    bool IsFirstInitialization();

    void Finalize();

    s32 GetNumSpeculativeRequests();

    nngxlowFuncPtr RegisterInterruptHandler(nngxlowFuncPtr interruptHandler,nngxlowInterrupt type);

    void Lock();
    void Unlock();

    void YieldThread();

    void SetAppletMode();

    void StartLcdDisplay();
    void StopLcdDisplay();

namespace detail{
    InterruptReceiver* GetInterruptReceiver();

    bool IsAppletMode();
    bool IsFatalErrMode();

    Gpu* GetGpuIpc();
inline bool IsContinousMemory(uptr addr){ return addr >= 0x14000000 && addr < 0x1C000000 ;}
inline bool IsVram(uptr addr){ return addr >= 0x1F000000 && addr <= 0x1F5FFFFF; }
}
}
}
}