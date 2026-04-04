#pragma once

#include "nn/types.h"

namespace nn{
namespace util{

    class Crc8{
    
        struct Crc8Table{
            u8 mCrc8Table[256];
        };
    
    nn::util::Crc8::Crc8Table mTable;
    public:

    Crc8(void);
    };

    class Crc16{
    public:
    
        struct Crc16Table{
            u16 mCrc16Table[256]; // Tech Ushort but whatever..
        };
    
    nn::util::Crc16::Crc16Table mTable;
    };

    class Crc32{
    public:
    
        struct Crc32Table{
            u32 mCrc32Table[256]; // Tech Ushort but whatever..
        };
    
    nn::util::Crc32::Crc32Table mTable;
    };


    class Crc16Ccitt{
        struct Context{
            u16 mContext;
        };
    nn::util::Crc16Ccitt::Context mCrc16Context;
    nn::util::Crc16::Crc16Table mTable;
    };

    class Crc32Posix{
        struct Context{
            u32 mContext;
        };
    nn::util::Crc32Posix::Context mCrc32Context;
    nn::util::Crc32::Crc32Table mTable;
    };
}
}