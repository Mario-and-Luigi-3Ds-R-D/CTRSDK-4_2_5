#pragma once

#include "nn/fs/fs_IStream.h"
#include "nn/fs/fs_Paramaters.h"
#include "nn/fs/detail/fs_FileBase.h"
#include "nn/util/util_NonCopyable.h"
#include "nn/Result.h"

namespace nn{
namespace fs{

    class FileStream : public IStream, public detail::FileBase{ // public FileBase as well
    public:
        FileStream();
        virtual ~FileStream();
        virtual int Read(void*, size_t);
        virtual Result TryRead(s32* pOut, void* buffer, size_t size);
        virtual s32 Write(const void* buffer, size_t size, bool flush);
        virtual Result TryWrite(s32* pOut, const void* buffer, size_t size, bool flush);
        virtual void Seek(s64 position, PositionBase base);
        virtual Result TrySeek(s64 position, PositionBase base);
        virtual s64 GetPosition();
        virtual Result TryGetPosition(s64* pOut);
        virtual void SetPosition(s64 position);
        virtual Result TrySetPosition(s64 position);
        virtual s64 GetSize();
        virtual Result TryGetSize(s64* pOut);
        virtual void SetSize(s64 size);
        virtual Result TrySetSize(s64 size);
        virtual void Flush();
        virtual Result TryFlush();
    };

    class FileInputStream : public nn::fs::IInputStream, public nn::fs::detail::FileBase, nn::util::ADLFireWall::NonCopyable<FileInputStream>{
    public:
        FileInputStream();
        virtual ~FileInputStream();
        virtual s32 Read(void* buffer, size_t size);
        virtual Result TryRead(s32* pOut, void* buffer, size_t size);
        virtual void Seek(s64 position, PositionBase base);
        virtual Result TrySeek(s64 position, PositionBase base);
        virtual s64 GetPosition();
        virtual Result TryGetPosition(s64* pOut);
        virtual void SetPosition(s64 position);
        virtual Result TrySetPosition(s64 position);
        virtual s64 GetSize();
        virtual Result TryGetSize(s64* pOut);
    };

} // fs
} // nn