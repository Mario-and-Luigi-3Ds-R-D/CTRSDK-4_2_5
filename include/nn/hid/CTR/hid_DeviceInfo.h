#include "nn/types.h"

namespace nn {
namespace hid {
namespace CTR {
    const bit32 BUTTON_A                = 0x00000001;
    const bit32 BUTTON_B                = 0x00000002;
    const bit32 PSEUDO_BUTTON_SELECT    = 0x00000004;
    const bit32 BUTTON_SELECT           = 0x00000004;
    const bit32 BUTTON_START            = 0x00000008;
    const bit32 BUTTON_RIGHT            = 0x00000010;
    const bit32 BUTTON_LEFT             = 0x00000020;
    const bit32 BUTTON_UP               = 0x00000040;
    const bit32 BUTTON_DOWN             = 0x00000080;
    const bit32 BUTTON_R                = 0x00000100;
    const bit32 BUTTON_L                = 0x00000200;
    const bit32 BUTTON_X                = 0x00000400;
    const bit32 BUTTON_Y                = 0x00000800;
    const bit32 BUTTON_DEBUG            = 0x00001000;
    const bit32 BUTTON_RESERVED         = 0x00002000;
    const bit32 BUTTON_EMULATION_RIGHT  = 0x10000000;
    const bit32 BUTTON_EMULATION_LEFT   = 0x20000000;
    const bit32 BUTTON_EMULATION_UP     = 0x40000000;
    const bit32 BUTTON_EMULATION_DOWN   = 0x80000000;
}
}
}