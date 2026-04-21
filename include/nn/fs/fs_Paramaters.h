#pragma once

#include "nn/types.h"

namespace nn{
namespace fs{
    struct ArchiveResource{
        uint mSectorSize;
        uint mClusterSize;
        uint mTotalClusters;
        uint mFreeClusters;
    };

    struct Attributes{
        bool mIsDirectory;
        bool mIsHidden;
        bool mIsArchive;
        bool mIsReadOnly;
    };

    struct SdmcLog{
    };

    struct SdmcSpeedInfo{
        bool mCardHighSpeed;
        bool mSdIfMaxSpeed;
        ushort mSdIfCtrlValue;
    };

    struct CtrCardCompatibilityInfo{
        u64 mCompatibilityInfo;
    };

    struct CtrCardLatencyParamater{
        u64 mLatencyInfo;
    };

    struct ProgramDataPath{
        int mTag;
        s64 mId;
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

    struct Fs9CompatibilityInfo : public CtrCardCompatibilityInfo{
    };

    struct FsCompatibilityInfo : public Fs9CompatibilityInfo{
    };

    struct WriteOption{
        bool mFlush;
        bool mUpdateTimeStampOld;
        bool mUpdateTimeStamp;
        s8 mDestroySignature;
    };

    struct Transaction{
        bit32 mDummy;
    };

    enum CardType{
        TYPE_CTR = 0,
        TYPE_DS = 1,
        TYPE_UNKNOWN = 2,
    };

    enum PositionBase{
        BASE_BEGIN = 0,
        BASE_CURRENT = 1,
        BASE_END = 2,
    };

    enum MediaType{
        MEDIA_NAND = 0,
        MEDIA_SDMC = 1,
        MEDIA_CTRCARD = 2,
    };

    enum SystemMediaType{
        CTR_NAND = 0,
        TWL_NAND = 1,
        SDMC = 2,
        TWL_PHOTO = 3,
    };

    enum CardSpiBusMode{
        BIT_1 = 0,
        BIT_4 = 3,
    };

    enum CardSpiBaudRate{
        KHZ_512 = 0,
        MHZ_1 = 1,
        MHZ_2 = 2,
        MHZ_4 = 3,
        MHZ_8 = 4,
        MHZ_16 = 5,
    };

    enum StorageAttribute{
        NORMAL = 0,
        FIXED = 1,
        NEW = 2,
    };

    struct LatencyEmulationState {
        u8 mIsLatencyEmuEnabled;            
        __packed union {
            u32 mIsEmulationEndurance; 
            u8  mIsDebugMode;     
        };
        u8  _pad[0x13];           
        s32 mLatencyParamLo;      
        s32 mLatencyParamHi;      
    };

    extern LatencyEmulationState pLatencyState;
    
} // fs
} // nn