#pragma once

#include "nn/types.h"
#include "nn/Result.h"
#include "nn/fs/fs_Paramaters.h"

namespace nn{
namespace fs{
namespace detail{

    class FileBaseImpl{
        void* mFile;
    public:
    };

    class FileBase : public FileBaseImpl{
    protected:
        struct S64{
            s32 lo;
            s32 hi;
        };
        S64 mPosition;
        S64 mSize;
    public:
        Result TryRead(int*, void*, size_t);
        Result TryWrite(int*, const void*, size_t, bool);
        Result TrySeek(s64, nn::fs::PositionBase);
        Result TryGetPosition(s64*) const;
        Result TrySetPosition(s64);
        Result TryGetSize(s64*) const;
        Result TrySetSize(s64);
        Result TryFlush();
        int Read(void*, size_t);
        int Write(const void*, size_t, bool); // guess
        void Seek(s64 pSeekOut, nn::fs::PositionBase pPosBase);
        void SetPosition(s64);
        s64 GetPosition();
        s64 GetSize();
    };
} // detail
} // fs
} // nn