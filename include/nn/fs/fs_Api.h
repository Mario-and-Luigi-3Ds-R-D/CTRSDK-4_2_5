#pragma once

#include "nn/Result.h"
#include "nn/fs/fs_Paramaters.h"

namespace nn{
namespace fs{
    void Initialize();
    bool IsInitialized(void);
    Result SetPriority(int pPritority);
    Result GetPriotity(int pOut);
    Result CommitSaveData(char* pPath);
    Result FormatSaveData(size_t pMaxFiles, size_t pMaxDirectories, bool pIsDuplicated);


    /* Mounting */
    Result MountSaveData(char* pArchiveName);
    Result MountRom(size_t pMaxFile, size_t pMaxDirectory, void* pWorkingMemory, size_t pWorkingMemorySize, bool pUseCache);
    Result MountRom(char *pArchiveName,size_t pMaxFile,size_t pMaxDirectory,void *pWorkingMemory, size_t pWorkingMemorySize,bool pUseCache);
    Result Unmount(char* pArchiveName);

    /* Memory Size */
    int GetRomRequiredMemorySize(size_t pMaxFile, size_t pMaxDirectory, bool pUseCache);
    int GetRomRequiredMemorySizeImpl(size_t pMaxFile, size_t pMaxDirectory, bool pUseCache, ProgramDataPath* pContentPath);
};
}