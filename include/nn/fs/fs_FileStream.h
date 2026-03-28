#pragma once

#include "nn/fs/fs_IStream.h"
#include "nn/fs/fs_Paramaters.h"
#include "nn/fs/detail/fs_FileBase.h"
#include "nn/Result.h"

// FUN_ is based of Mario & Luigi Dream Team US 1.0. and NEEDS research
//
// Research Based on publically av AXF found in Bowling3DS & SpiderMan Edge of Time
// All most of these do is return filebase shit lmao

namespace nn{
namespace fs{
    class FileStream : public IStream, public detail::FileBase{ // public FileBase as well
    public:
        FileStream();
        virtual ~FileStream();
        virtual Result TrySeek(s64, nn::fs::PositionBase);
        virtual void Seek(s64, nn::fs::PositionBase);
        virtual int FUN_005e0480();
        virtual FileStream* FUN_005e0478();
        virtual s64 FUN_00128140();
        virtual void SetPosition(s64);
        virtual Result TryGetSize(s64*);
        virtual s64 GetSize();
        virtual Result TryRead(int*, void*, size_t);
        virtual int Read(void*, size_t);
        virtual int Write(const void*, size_t, bool);
        virtual Result TryWrite(int*, const void*, size_t, bool);
        virtual void FUN_0045c5dc();
        virtual void FUN_0045e9e8();
        virtual void FUN_0045c57c();
        virtual void FUN_0045ea3c();
    };

    class FileInputStream : public IInputStream, detail::FileBase{
    public:
        virtual ~FileInputStream();
        virtual Result TrySeek(s64, nn::fs::PositionBase);
        virtual void Seek(s64, nn::fs::PositionBase);
        virtual int FUN_005f5784();
        virtual s64 FUN_005f57b8();
        virtual Result TrySetPosition(s64);
        virtual void SetPosition(s64);
        virtual Result TryGetSize(s64*);
        virtual long long GetSize();
        virtual Result TryRead(int*, void*, size_t);
        virtual s32 Read(void*, size_t);
    };
    
    class FileOutputStream : public IOutputStream, detail::FileBase{
    public:
    
    };
} // fs
} // nn