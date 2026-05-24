#pragma once

#include "nn/Result.h"
#include "nn/Handle.h"
#include "nn/fs/fs_Paramaters.h"
#include "nn/fs/CTR/MPCore/fs_UserArchive.h"
#include "nn/fnd/fnd_UnitHeap.h"

namespace nn{
namespace fs{
namespace{
    extern u8 buf[0x8];
    extern CTR::MPCore::detail::IArchive* gSaveDataArchive;
}

namespace CTR{
namespace MPCore{
namespace detail{
namespace{
    extern nn::Handle gFileServerArchive;
    extern fnd::UnitHeapBase sArchiveHeap;
}
namespace{
    static fnd::TimeSpan ConstantWait;
}
namespace{
    extern bool sIsEmulateEndurance;
}

typedef nn::fslow::LowPath<const char*, const wchar_t*> Path;

Result OpenSpecialArchiveRaw(IArchive** pOut, bit32 archiveKind);

class ArchiveName{
public:
    ArchiveName(char const* pName);

};

class ArchiveTableEntry{
protected:
    bit64 id;
    IArchive* archive;
    s32 rev;
public:
    ArchiveTableEntry();
};

class UserFileSystem{
public:
    static Result  CloseFile(void*);
    static Result Initialize(nn::Handle handle);
    static Result TryGetFileSize(s64* pout,void*);
    static Result TrySetFileSize(void* p, s64 size);
    static Result TryWriteFile(s32* pOut, void* p, s64 offset, void* buffer, size_t size, bool flush);
    static Result TryReadFile(s32* pOut, void* p, s64 offset, void* buffer, size_t size);
    static Result TryOpenFile(void** pout, const wchar_t* pathName,bit32 mode);
    static Result TryFlush(void*);

};

}
}
}
}
}