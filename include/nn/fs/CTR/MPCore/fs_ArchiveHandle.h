#pragma once

#include "nn/fs/CTR/MPCore/fs_UserArchive.h"

namespace nn{
namespace fs{
namespace CTR{
namespace MPCore{
namespace detail{
bool RegisterArchive(const char* path, IArchive* archive);
IArchive* FindArchive(ushort* path);
uint OpenDataContent(int,int,int,int);
}
}
}
}
}