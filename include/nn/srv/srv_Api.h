#pragma once

#include "nn/Handle.h"
#include "nn/Result.h"

namespace nn {
namespace srv {

    Result Initialize();
    Result GetServiceHandle(nn::Handle* pOut, const char* pService, s32, u32);
    Result StartNotification(void);

} // Namespace srv
} // Namespace nn