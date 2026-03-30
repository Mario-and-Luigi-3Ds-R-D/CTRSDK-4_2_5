#pragma once

namespace nn{
namespace dbg{
    enum BreakReason{
        BREAK_REASON_PANIC = 0,
        BREAK_REASON_ASSERT = 1,
        BREAK_REASON_USER = 2,
        BREAK_REASON_LOAD_RO = 3, // Hey, thats my line!
        BREAK_REASON_UNLOAD_RO = 4,
        BREAK_REASON_MAX_BIT = 0x80000000,
    };
}
}