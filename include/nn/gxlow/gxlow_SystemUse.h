#pragma once

#include "nn/Result.h"
#include "nn/gxlow/gxlow_Parameters.h"

namespace nn{
namespace gxlow{
namespace CTR{
    Result AcquireGpuRight();
    void ImportDisplayCaptureInfo(DisplayCaptureInfo* pInfo);
    Result ReleaseGpuRight();
    Result RestoreVramSysArea();
    Result SaveVramSysArea();
}
}
}