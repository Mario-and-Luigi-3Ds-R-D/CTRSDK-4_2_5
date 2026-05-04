#pragma once

#include "nn/Result.h"
#include "nn/Handle.h"
#include "nn/fs/fs_Paramaters.h"

namespace nn{
namespace fs{
    Result MountSaveData(char* pArchiveName = "data:");

    Result FormatSaveData(size_t pMaxFiles, size_t pMaxDirectories, bool pIsDuplicated);
    Result CommitSaveData(const char* archiveName = "data:");

    Result MountRom(char *pArchiveName,size_t pMaxFile,size_t pMaxDirectory,void *pWorkingMemory, size_t pWorkingMemorySize,bool pUseCache);
    Result MountRom(size_t pMaxFile, size_t pMaxDirectory, void* pWorkingMemory, size_t pWorkingMemorySize, bool pUseCache);
    Result Unmount(char* pArchiveName);

    // Memory Size 
    int GetRomRequiredMemorySize(size_t pMaxFile, size_t pMaxDirectory, bool pUseCache);
    int GetRomRequiredMemorySizeImpl(size_t pMaxFile, size_t pMaxDirectory, bool pUseCache, ProgramDataPath* pContentPath);

}
}