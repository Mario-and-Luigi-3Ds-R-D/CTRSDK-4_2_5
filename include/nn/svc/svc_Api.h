#pragma once

#include "nn/types.h"
#include "nn/Result.h"

namespace nn{
namespace svc{
    Result ControlMemory();
    void ExitProcess();
    void QueryMemory();
    void CreateThread();
    void ExitThread();
    void SleepThread();
    Result GetThreadPriority();
    Result CreateMutex();
    Result CreateEvent();
};
}