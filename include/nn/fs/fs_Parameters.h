#pragma once

#include <nn/types.h>
#include <nn/util/util_Int64.h>

namespace nn{
namespace fs{
namespace detail { struct ArchiveHandleTag {}; }
typedef nn::util::Int64<bit64, detail::ArchiveHandleTag> ArchiveHandle;

    static const size_t MAX_ARCHIVE_NAME_LENGTH = 7;
    static const size_t MAX_SUB_PATH_LENGTH = 253;
    static const size_t MAX_FILE_PATH_LENGTH = MAX_ARCHIVE_NAME_LENGTH + 1 + MAX_SUB_PATH_LENGTH;
    
    struct Attributes{
        bool mIsDirectory;
        bool mIsHidden;
        bool mIsArchive;
        bool mIsReadOnly;
    };

    struct ShortName{
        char body[10];
        char ext[4];
        bool valid;
        bit8 pad;
    };

    struct DirectoryEntry{
        wchar_t entryName[MAX_FILE_PATH_LENGTH + 1];
        ShortName shortName;
        nn::fs::Attributes attributes;
        s64 entrySize;
    };

    enum OpenMode{
        OPEN_MODE_READ    = (1u << 0),
        OPEN_MODE_WRITE   = (1u << 1),
        OPEN_MODE_CREATE  = (1u << 2)
    };

    struct ProgramDataPath{
        int mTag;
        util::Int64<ProgramDataPath> mId;
    };

    struct ContentPath{
        int mContentPath;
        s64 mContentId;
    };

    struct TitleId{
        s64 fs_TitleId;
    };

    struct ExtSaveDataSpecifier{
        s8 mMediaType;
        s8 mStorageAttribute;
        s8 pad[0x2];
        s64 mExtSaveDataId;
    };

    struct TitleDataSpecificer{
        TitleId mId;
        s8 mMedia;
        s8 unkpad_1[3];
        int unkflag1;
    };

    struct DataContentArchivePath{
        TitleId mFs_TitleId;
        int mDataConPath;
        int mContentIdx;
    };

    struct WriteOption{
        bool mFlush;
        bool mUpdateTimeStampOld;
        bool mUpdateTimeStamp;
        s8 mDestroySignature;

        WriteOption(bool flush, bool updateTimeStamp){
            mFlush = flush;
            mUpdateTimeStampOld = false;
            mUpdateTimeStamp = updateTimeStamp;
        }
    };

    struct Transaction{
        bit32 mDummy;
    };


    enum MediaType{
        MEDIA_TYPE_NAND = 0,
        MEDIA_TYPE_SDMC,
        MEDIA_TYPE_CTRCARD
    };

    enum PositionBase{
        BASE_BEGIN = 0,
        BASE_CURRENT,
        BASE_END,
    };

    enum SystemMediaType{
        CTR_NAND = 0,
        TWL_NAND,
        SDMC,
        TWL_PHOTO,
    };

    enum StorageAttribute{
        NORMAL = 0,
        FIXED,
        NEW,
    };
    
}
}