#pragma once

#include <nn/fs/CTR/MPCore/fs_FileBase.h>

namespace nn{
namespace fs{
namespace detail{

class FileBase : public FileBaseImpl{
protected:
    typedef util::Int64<s64> S64;
    S64 mPosition;
    mutable S64 mSize;
public:
    FileBase() : mPosition(0), mSize(0) {}
    FileBase(const char* pathName, bit32 mode){ Initialize(pathName, mode); }
    FileBase(const wchar_t* pathName, bit32 mode){ Initialize(pathName, mode); }
    Result TryRead(int*, void*, size_t);
    Result TryWrite(int*, const void*, size_t, bool);
    Result TrySeek(s64, nn::fs::PositionBase);
    Result TrySetPosition(s64);
    Result TryGetSize(s64*) const;
    Result TrySetSize(s64);
    Result TryFlush();
        /* Use these instead of calling it directly! */

    s32 Read(void* buffer, size_t size){
        s32 ret;
        NN_ERR_THROW_FATAL_ALL(TryRead(&ret, buffer, size));
        return ret;
    }

    s32 Write(const void* buffer, size_t size, bool flush){
        s32 ret;
        NN_ERR_THROW_FATAL_ALL(TryWrite(&ret, buffer, size, flush));
        return ret;
    }

    void Seek(s64 position, PositionBase base){
        NN_ERR_THROW_FATAL_ALL(TrySeek(position, base));
    }

    s64 GetPosition() const{
        s64 ret;
        NN_ERR_THROW_FATAL_ALL(TryGetPosition(&ret));
        return ret;
    }

    void SetPosition(s64 position){
        NN_ERR_THROW_FATAL_ALL(TrySetPosition(position));
    }

    s64 GetSize() const{
        s64 ret;
        NN_ERR_THROW_FATAL_ALL(TryGetSize(&ret));
        return ret;
    }

    void SetSize(s64 size){
        NN_ERR_THROW_FATAL_ALL(TrySetSize(size));
    }

    void Flush(){
        NN_ERR_THROW_FATAL_ALL(TryFlush());
    }

    Result TryGetPosition(s64* pOut) const{
        *pOut = mPosition;
        return ResultSuccess();
    }

    Result TryInitialize(const wchar_t* pathName, bit32 mode){
        this->mPosition = this->mSize = 0;
        return TryOpenImpl(pathName, mode);
    }

    Result TryInitialize(const char* pathName, bit32 mode){
        // TODO
    }

    void Initialize(const wchar_t* pathName, bit32 mode){
        Result result = TryInitialize(pathName, mode);
            if (result.IsFailure()){
            NN_SLOG_("file open failed: ");
            NN_SLOG_("%lls\n", pathName);
            NN_ERR_THROW_FATAL_ALL(result);
        }
    }

    void Initialize(const char* pathName, bit32 mode){
        Result result = TryInitialize(pathName, mode);
            if (result.IsFailure()){
            NN_SLOG_("file open failed: ");
            NN_SLOG_("%lls\n", pathName);
            NN_ERR_THROW_FATAL_ALL(result);
        }
    }
};

}
}
}