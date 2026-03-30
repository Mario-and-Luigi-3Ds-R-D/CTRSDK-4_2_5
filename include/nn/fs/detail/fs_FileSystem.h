#pragma once

#include "nn/fs/CTR/MPCore/fs_UserFileSystem.h"

namespace nn{
namespace fs{
namespace detail{
    class FileSystemBaseImpl{ // UserFileSystem

    };
    
    class FileSystemBase{
        FileSystemBaseImpl* mBaseImpl;
    };
}
}
}