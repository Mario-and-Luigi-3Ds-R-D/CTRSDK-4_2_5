#pragma once

#include "nn/hid/CTR/hid_HidBase.h"

namespace nn{
namespace hid{
namespace CTR{

struct TouchPanelStatus{
    ushort x;
    ushort y;
    u8 touch;
    s8 rev[3];
};

class TouchPanelReader{
protected:
    TouchPanel* mTouchPanel;
    s32 mIndexOfRead;
    s64 mTickOfRead;
public:
    bool ReadLatest(TouchPanelStatus* status);
};

}
}
}