#pragma once

#include "nn/Result.h"
#include "nn/Handle.h"
#include "nn/fs/fs_Paramaters.h"

namespace nn{
namespace fs{
namespace ipc{
    class FileSystem{
        nn::Handle mSession;
    public:
        Result GetPriority(int* pOut);
        Result OpenArchive(bit64* pArchiveHandle, bit32 pArchiveType, bit32 pPathType, bit8* pPath, size_t pPathLength);
        Result SetPriority(int pPriority);
        Result CloseArchive(bit64 pArchiveHandle);
        Result ControlArchive(bit64 pArchiveHandle, bit32 pTag, void* pInBuffer, size_t pInSize, void* pOutBuffer, size_t pOutSize);
        Result FormatSaveData(bit32 pArchiveType,bit32 pPathType,bit8 *pPath,size_t pPathLength, u32 pSizeBlock,u32 pCountDirectoryEntry,u32 pCountFileEntry,u32 pCountDirectoryEntryBucket ,u32 pCountFileEntryBucket,bool pIsDuplicateAll);
        Result OpenFileDirectly(nn::Handle *pOut, nn::fs::Transaction pTransaction,bit32 pArchiveType, bit32 pArchivePathType,bit8 *pNewPath,size_t pNewPathLength,bit32 pPathType,bit8 *pPath, size_t pPathLength,bit32 pMode,nn::fs::Attributes pAttributes);
        Result InitializeWithSdkVersion(bit32 pSdkVersion);
        Result OpenFile(nn::Handle *pOut, nn::fs::Transaction pTransaction, bit64 pArchiveHandle, bit32 pPathType, bit8 *pPath,size_t pPathLength,bit32 pMode,nn::fs::Attributes pAttributes);
    };
    
    class File{
        nn::Handle mSession;
    public:
        Result SetPriority(int pPriority);
        Result OpenLinkFIle(nn::Handle pOut);
        Result Read(int* pRead, s64 pOffset, void* pBuffer, size_t pSize);
        Result Close();
        Result Write(int* pWritten, s64 pOffset, void* pBuffer, size_t pSize, nn::fs::WriteOption pOption);
        Result GetSize(s64* pOut);
        Result SetSize(s64 pSize);
    };
}
}
}