#include <nn/fs/CTR/MPCore/fs_FileSystemBase.h>

#include <nn/fs/CTR/MPCore/fs_ArchiveHandle.h>
#include <nn/fslow/fslow_QueryOptimalBucketCount.h>
#include <nn/err/CTR/err_Api.h>

namespace nn{
namespace fs{
namespace{
    extern u8 buf[0x8];
    extern CTR::MPCore::detail::IArchive* gSaveDataArchive;
}
Result MountSaveData(char* pArchiveName){

}

Result FormatSaveData(size_t maxFiles, size_t maxDirectories, bool isDuplicated){
    u32 countDirectoryEntryBucket = fslow::QueryOptimalBucketCount(maxDirectories);
    u32 countFileEntryBucket = fslow::QueryOptimalBucketCount(maxFiles);
    CTR::MPCore::detail::Path path;
    //ipc::FileSystem filesys[2];
    //filesys[0].mSession = gFileServerArchive;
    //filesys.FormatSaveData(4, 1, path.mData, 1, 0x200, maxDirectories, maxFiles, countDirectoryEntryBucket, countFileEntryBucket, isDuplicated);
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

/* Add "NN_USE_SDMC" to your complier flags to use these. */

#ifdef NN_USE_SDMC

#endif

}
}