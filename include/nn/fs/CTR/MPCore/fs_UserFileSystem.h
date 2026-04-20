#pragma once

#include "nn/Result.h"
#include "nn/Handle.h"
#include "nn/fs/fs_Paramaters.h"

namespace nn{
namespace fs{
namespace CTR{
namespace MPCore{
namespace detail{

class ArchiveName{
public:
    ArchiveName(char const* pName);

};

class ArchiveTableEntry{
public:
    ArchiveTableEntry();
};

class RomFsArchive{
public:

};

class ContentRomFsArchive{
public:
    virtual void DeleteObject();
    virtual ~ContentRomFsArchive();
    virtual void OpenDirect();
};

}
}
}
}
}