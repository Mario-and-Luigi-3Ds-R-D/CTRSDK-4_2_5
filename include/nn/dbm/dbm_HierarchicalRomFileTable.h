#pragma once

#include "nn/types.h"
#include "nn/util/util_Int64.h"
#include "nn/fnd/fnd_Intrusive.h"

namespace nn{
namespace fs{
namespace CTR{
namespace MPCore{
namespace detail{
    class RomFsArchive;
}
}
}
}

namespace dbm{

struct RomFsStorage {
    bit8 *mBuffer;
    size_t mSize;
    fs::CTR::MPCore::detail::RomFsArchive *mpParent;
    u32 mOffset;
};

typedef struct RomFsStorage RomFsStorage, *PRomFsStorage;
typedef struct RomFsStorage DirectoryBucketStorage;
typedef DirectoryBucketStorage BucketStorage;
typedef struct RomFsStorage DirectoryEntryStorage;
typedef DirectoryEntryStorage EntryStorage;

struct KeyValueRomStorageTemplate {
    util::Int64<s64> mOffsetBucket;
    u32 mCountBucket;
    BucketStorage *mpBufBucket;
    util::Int64<s64> mOffsetKeyValue;
    u32 mSizeKeyValue;
    EntryStorage *mpBufKeyValue;
    u32 mTotalEntrySize;
    u32 mEntryCount;
};


struct RomFsStorage {
    bit8 *mBuffer;
    size_t mSize;
    struct RomFsArchive *mpParent;
    u32 mOffset;
};

struct EntryMapTable : public KeyValueRomStorageTemplate {

};

struct RomEntryKey{

};

typedef struct EntryMapTable DirectoryEntryMapTable;
typedef struct EntryMapTable FileEntryMapTable;

struct FileInfo{
public:
    util::Int64<s64> offset;
    util::Int64<s64> size;
};

class  HierarchicalRomFileTableTemplate {
public:
    DirectoryEntryMapTable mTableDirectory;
    FileEntryMapTable mTableFile;

    Result FindFileResource(EntryKey*);

    Result OpenFile(FileInfo* pFileInfo, u8* pFullPath){
        NN_NULL_TASSERT_(pFileInfo);
        NN_NULL_TASSERT_(pFullPath);
        Result res;

    }
};
}
}