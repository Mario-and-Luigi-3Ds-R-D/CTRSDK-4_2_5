#pragma once

#include "nn/types.h"
#include "nn/Result.h"
#include "nn/Handle.h"
#include "nn/dbg/dbg_Break.h"
#include "nn/os/os_Api.h"

namespace nn{
namespace svc{
    Result ControlMemory(uint*,uint,uint,uint,uint,uint);
    void ExitProcess();
    void QueryMemory(nn::os::MemoryInfo*,nn::os::PageInfo*,uint);
    void CreateThread(nn::Handle*, void*, uint, uint,uint,int,int);
    void ExitThread();
    void SleepThread(long long);
    Result GetThreadPriority();
    Result CreateMutex(nn::Handle*,bool);
    Result CreateEvent(nn::Handle*,nn::os::ResetType);
    s32 CreateAddressArbiter(nn::Handle*);
    void ArbirateAddress(nn::Handle,uint,nn::os::ArbitrationType,int,long long);
    void Break(nn::dbg::BreakReason,const void*,int);
    void CloseHandle(nn::Handle);
    void ConnectToPort(nn::Handle*, const char*);
    void DuplicateHandle(nn::Handle*);
    void GetProcessId(uint*, nn::Handle);
    void GetResourceLimit(nn::Handle*);
    void GetSystemTick();
    void GetThreadId(uint*,nn::Handle);
    void WaitSynchronizationN(int*, const nn::Handle*, int,bool,long long);
};
}