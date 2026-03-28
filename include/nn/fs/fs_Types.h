#pragma once

#include "nn/types.h"

namespace nn{
namespace fs{
    struct ArchiveResource{
        uint mSectorSize;
        uint mClusterSize;
        uint mTotalClusters;
        uint mFreeClusters;
    };

    enum CardType{
        TYPE_CTR = 0,
        TYPE_DS = 1,
        TYPE_UNKNOWN = 2,
    };

    enum PositionBase{
        BASE_BEGIN = 0,
        BASE_CURRENT = 1,
        BASE_END = 2,
    };

    struct SdmcLog{
    };

    struct SdmcSpeedInfo{
        bool mCardHighSpeed;
        bool mSdIfMaxSpeed;
        ushort mSdIfCtrlValue;
    };
} // fs
}