#pragma once

#include "nn/hid/CTR/hid_HidBase.h"
#include "nn/hid/hid_Api.h"
#include "nn/util/util_NonCopyable.h"

namespace nn{
namespace hid{
namespace CTR{

struct TouchPanelStatus{
    ushort x;
    ushort y;
    u8 touch;
    s8 rev[3];
};

class TouchPanelReader : private nn::util::NonCopyable<TouchPanelReader>{
protected:
    TouchPanel& mTouchPanel;
    s32 mIndexOfRead;
    s64 mTickOfRead;
public:
    TouchPanelReader(TouchPanel& touchPanel = CTR::GetTouchPanel( )) : mTouchPanel(touchPanel), mIndexOfRead(-1), mTickOfRead(-1){ };
    bool ReadLatest(TouchPanelStatus* status);

    static const s8 MAX_READ_NUM = 7;
};

}
}
}