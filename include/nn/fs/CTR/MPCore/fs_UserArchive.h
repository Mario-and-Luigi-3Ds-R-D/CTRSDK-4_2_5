#pragma once

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/fs/fs_Paramaters.h>
#include <nn/fslow/fslow_Path.h>

namespace nn {
namespace fs {
namespace CTR {
namespace MPCore {
namespace detail{

typedef nn::fslow::LowPath<const char*, const wchar_t*> Path;

class IFile{
public:
    virtual Result TryRead (s32*, s64, size_t) = 0; // 0x0
    virtual Result TryWrite (s32*, s64, size_t, bool) = 0; // 0x4
    virtual Result TryGetSize (s64*) = 0; // 0x8
    virtual Result TrySetSize (s64) = 0; // 0xC
    virtual Result TryFlush () = 0; // 0x10
    virtual Result DuplicateHandle (Handle*, s64, s64) = 0; // 0x14
    virtual Handle GetFileHandle () const {} // 0x18
    virtual void DetachFileHandle () {} // 0x1C
    virtual void Close () = 0; // 0x20
    virtual ~IFile () {}
};

class IDirectory{
public:
    //virtual Result TryRead (s32*, DirectoryEntry, s32) = 0;
    virtual void Close () = 0;
    virtual ~IDirectory () {}
};

class IArchive{
public:
    virtual Result OpenFile (IFile**, const Path&, bit32) = 0;
    virtual Result OpenDirectory (IDirectory**, const Path&) = 0;
    virtual Result DeleteFile (const Path&) = 0;
    virtual Result RenameFile (const Path&, const Path&) = 0;
    virtual Result DeleteDirectory (const Path&) = 0;
    virtual Result TryDeleteDirectoryRecursively (const Path&) = 0;
    virtual Result CreateFile (const Path&) = 0;
    virtual Result CreateDirectory (const Path&) = 0;
    virtual Result RenameDirectory (const Path&, const Path&) = 0;
    virtual Result GetFreeBytes (s64* pOut) {}
    virtual ~IArchive () {}
};


} // namespace detail
} // namespace MPCore
} // namespace CTR
} // namespace fs
} // namespace nn