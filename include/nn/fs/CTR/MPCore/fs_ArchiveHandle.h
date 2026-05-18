#pragma once

#include "nn/fs/CTR/MPCore/fs_UserArchive.h"

namespace nn{
namespace fs{
namespace CTR{
namespace MPCore{
namespace detail{
    Result RegisterArchive(const char* path, IArchive* archive, bool isAddOnContent, bool isAlias);
    IArchive* FindArchive(ushort* path);
    uint OpenDataContent(int,int,int,int);
    Result OpenSpecialArchiveRaw(IArchive** pOut, bit32 archiveKind);
}
}
}
}
}