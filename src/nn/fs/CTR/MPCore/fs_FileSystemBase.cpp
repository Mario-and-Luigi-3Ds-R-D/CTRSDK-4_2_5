#include <nn/fs/CTR/MPCore/fs_FileSystemBase.h>

#include <nn/fs/CTR/MPCore/fs_ArchiveHandle.h>
#include <nn/fslow/fslow_QueryOptimalBucketCount.h>
#include <nn/err/CTR/err_Api.h>

namespace nn{
namespace fs{
namespace{
    u8 buf[0x8];
    CTR::MPCore::detail::IArchive* gSaveDataArchive;
}

Result MountSaveData(const char* archive) {
    CTR::MPCore::detail::IArchive* p;
    Result result;

    if (gSaveDataArchive != 0) {
        return Result(0xc92044e7);
    }

    result = CTR::MPCore::detail::OpenSpecialArchiveRaw(&p, 4);
    if (result.IsSuccess()){
        result = CTR::MPCore::detail::RegisterArchive(archive,p,false,false);
        if(result.IsFailure()){
            p->DeleteObject();
        } else{
            gSaveDataArchive = p;
        }
    }
    return result;
}

Result FormatSaveData(size_t maxFiles, size_t maxDirectories, bool isDuplicated){
    // TODO
}

Result CommitSaveData(const char* pArchiveName){
    // TODO
}

Result MountRom(char *pArchiveName,size_t maxFile, size_t maxDirectory, void* workingMemory, size_t workingMemorySize, bool useCache){
    // TODO
}

Result MountRom(size_t maxFile, size_t maxDirectory, void* workingMemory, size_t workingMemorySize, bool useCache){
    MountRom("rom:", maxFile, maxDirectory, workingMemory, workingMemorySize, useCache);
}

Result Unmount(char* pArchiveName){
    // TODO
}

int GetRomRequiredMemorySize(size_t maxFile, size_t maxDirectory, bool useCache){
    ProgramDataPath path;
    GetRomRequiredMemorySizeImpl(maxFile, maxDirectory, useCache, &path);
}

int GetRomRequiredMemorySizeImpl(size_t maxFile, size_t maxDirectory, bool useCache, ProgramDataPath* pContentPath){
    // TODO
}

}
}