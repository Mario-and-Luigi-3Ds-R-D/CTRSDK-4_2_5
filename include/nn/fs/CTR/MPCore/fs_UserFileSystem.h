#pragma once

#include "nn/Result.h"
#include "nn/Handle.h"
#include "nn/fs/fs_Paramaters.h"
#include "nn/fs/CTR/MPCore/fs_UserArchive.h"
#include "nn/fnd/fnd_UnitHeap.h"

namespace nn{
namespace fs{
    Result MountSaveData(char* pArchiveName = "data:");
    Result MountSaveData(const char* archiveName, bit32 uniqueId);
    Result MountSaveData(const char* archiveName, bit32 uniqueId, bit8 variation);

    Result FormatSaveData(size_t pMaxFiles, size_t pMaxDirectories, bool pIsDuplicated);
    Result CommitSaveData(const char* archiveName = "data:");

    Result MountRom(char *pArchiveName,size_t pMaxFile,size_t pMaxDirectory,void *pWorkingMemory, size_t pWorkingMemorySize,bool pUseCache);
    Result MountRom(size_t pMaxFile, size_t pMaxDirectory, void* pWorkingMemory, size_t pWorkingMemorySize, bool pUseCache);
    Result Unmount(char* pArchiveName);

    /* Memory Size */
    int GetRomRequiredMemorySize(size_t pMaxFile, size_t pMaxDirectory, bool pUseCache);
    int GetRomRequiredMemorySizeImpl(size_t pMaxFile, size_t pMaxDirectory, bool pUseCache, ProgramDataPath* pContentPath);

namespace CTR{
namespace MPCore{
namespace detail{

struct RomFsStorage{
    bit8* mBuffer;
    size_t mSize;
    RomFsArchive mParent;
    u32 mOffset;
};

class ArchiveName{
public:
    ArchiveName(char const* pName);

};

class ArchiveTableEntry{
public:
    ArchiveTableEntry();
};

class UserFileSystem{
public:
    void CloseFile();
    bool Initialize();
    static int TryGetFileSize(long long* pout,void*);
    //static Result(void** pout,ushort pathName,bit32 mode);

};

class RomFsArchive : public IArchive{
protected:
    struct BucketStorage{
        bit8* mBuffer;
        size_t mSize;
        RomFsArchive* mParent;
        u32 mOffset;
    };

    struct EntryStorage{
        bit8* mBuffer;
        size_t mSize;
        RomFsArchive* mParent;
        u32 mOffset;
    };

    struct TableDirectoryTemplate{
        s64 mOffsetBucket;
        u32 mCountBucket;
        BucketStorage* mBufBucket;
        s64 mOffsetKeyValue;
        u32 mSizeKeyValue;
        EntryStorage* mBufKeyValue;
        u32 mTotalEntrySize;
        u32 mEntryCount;
    };

    struct RomFsStorage{
        bit8* mBuffer;
        size_t mSize;
        RomFsArchive* mParent;
        u32 mOffset;
    };

    struct RomFileTable{
        TableDirectoryTemplate mTableDirectory;
        TableDirectoryTemplate mTableFile;
    };

    s32 mArchivePriority;
    IFile* mBaseFile;
    IFile* mPriorFiles[5];
    RomFsStorage mStorageDirectoryBucket;
    RomFsStorage mStorageDirectoryEntry;
    RomFsStorage mStorageFileBucket;
    RomFsStorage mStorageFileEntry;
    u32 mEntrySize;
    int rev;
    fnd::UnitHeapTemplate<RomFsArchive> mFileHeap;
    fnd::UnitHeapTemplate<RomFsArchive> mDirectoryHeap;
public:

    virtual Result OpenFile (IFile**, const Path&, bit32);
    virtual Result OpenDirectory (IDirectory**, const Path&);
    virtual Result DeleteFile (const Path&);
    virtual Result RenameFile (const Path&, const Path&);
    virtual Result DeleteDirectory (const Path&);
    virtual Result TryDeleteDirectoryRecursively (const Path&);
    virtual Result CreateFile (const Path&);
    virtual Result CreateDirectory (const Path&);
    virtual Result RenameDirectory (const Path&, const Path&);
    virtual ~RomFsArchive ();
    virtual void DuplicateHandle();
    virtual void OpenLinkHandle();

    class File : public IFile{
    public:
        RomFsArchive* mParent;
        s64 mHead;
        s64 mTail;
        s32 mPriority;

        virtual Result TryRead (s32*, s64, size_t);
        virtual Result TryWrite (s32*, s64, size_t, bool);
        virtual Result TryGetSize (s64*);
        virtual Result TrySetSize (s64);
        virtual Result TryFlush ();
        virtual Result DuplicateHandle (Handle*, s64, s64);
        virtual Handle GetFileHandle () const;
        virtual void DetachFileHandle ();
        virtual void Close ();
        virtual ~File () {}
    };

    class Directory : public IDirectory{
        //virtual Result TryRead (s32*, DirectoryEntry, s32) = 0;
        virtual void Close ();
        virtual ~Directory () {}
    };
};


class ContentRomFsArchive : public RomFsArchive{
public:
    int* AllocateBuffer();
    ContentRomFsArchive();
    virtual void DeleteObject();
    virtual ~ContentRomFsArchive();
    virtual void OpenDirect();
};

}
}
}
}
}