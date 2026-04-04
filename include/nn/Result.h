#pragma once

#include "nn/types.h"

struct Result {
private:
    u32 mResult;
public:

    enum Level{
            LEVEL_INFO      = 1,
            LEVEL_SUCCESS   = 0,
            LEVEL_FATAL     = -1,
            LEVEL_RESET     = -2,
            LEVEL_REINIT    = -3,
            LEVEL_USAGE     = -4,
            LEVEL_PERMANENT = -5,
            LEVEL_TEMPORARY = -6,
            LEVEL_STATUS    = -7,
            LEVEL_END
    };

    enum Summary{
            SUMMARY_SUCCESS              = 0,
            SUMMARY_NOTHING_HAPPENED     = 1,
            SUMMARY_WOULD_BLOCK          = 2,
            SUMMARY_OUT_OF_RESOURCE      = 3,
            SUMMARY_NOT_FOUND            = 4,
            SUMMARY_INVALID_STATE        = 5,
            SUMMARY_NOT_SUPPORTED        = 6,
            SUMMARY_INVALID_ARGUMENT     = 7,
            SUMMARY_WRONG_ARGUMENT       = 8,
            SUMMARY_CANCELLED            = 9,
            SUMMARY_STATUS_CHANGED       = 10,
            SUMMARY_INTERNAL             = 11,
            SUMMARY_INVALID_RESULT_VALUE = 63
    };

    enum Module{
            MODULE_COMMON,
            MODULE_NN_KERNEL,
            MODULE_NN_UTIL,
            MODULE_NN_FILE_SERVER,
            MODULE_NN_LOADER_SERVER,
            MODULE_NN_TCB,
            MODULE_NN_OS,
            MODULE_NN_DBG,
            MODULE_NN_DMNT,
            MODULE_NN_PDN,
            MODULE_NN_GX,
            MODULE_NN_I2C,
            MODULE_NN_GPIO,
            MODULE_NN_DD,
            MODULE_NN_CODEC,
            MODULE_NN_SPI,
            MODULE_NN_PXI,
            MODULE_NN_FS,
            MODULE_NN_DI,
            MODULE_NN_HID,
            MODULE_NN_CAMERA,
            MODULE_NN_PI,
            MODULE_NN_PM,
            MODULE_NN_PMLOW,
            MODULE_NN_FSI,
            MODULE_NN_SRV,
            MODULE_NN_NDM,
            MODULE_NN_NWM,
            MODULE_NN_SOCKET,
            MODULE_NN_LDR,
            MODULE_NN_ACC,
            MODULE_NN_ROMFS,
            MODULE_NN_AM,
            MODULE_NN_HIO,
            MODULE_NN_UPDATER,
            MODULE_NN_MIC,
            MODULE_NN_FND,
            MODULE_NN_MP,
            MODULE_NN_MPWL,
            MODULE_NN_AC,
            MODULE_NN_HTTP,
            MODULE_NN_DSP,
            MODULE_NN_SND,
            MODULE_NN_DLP,
            MODULE_NN_HIOLOW,
            MODULE_NN_CSND,
            MODULE_NN_SSL,
            MODULE_NN_AMLOW,
            MODULE_NN_NEX,
            MODULE_NN_FRIENDS,
            MODULE_NN_RDT,
            MODULE_NN_APPLET,
            MODULE_NN_NIM,
            MODULE_NN_PTM,
            MODULE_NN_MIDI,
            MODULE_NN_MC,
            MODULE_NN_SWC,
            MODULE_NN_FATFS,
            MODULE_NN_NGC,
            MODULE_NN_CARD,
            MODULE_NN_CARDNOR,
            MODULE_NN_SDMC,
            MODULE_NN_BOSS,
            MODULE_NN_DBM,
            MODULE_NN_CFG,
            MODULE_NN_PS,
            MODULE_NN_CEC,
            MODULE_NN_IR,
            MODULE_NN_UDS,
            MODULE_NN_PL,
            MODULE_NN_CUP,
            MODULE_NN_GYROSCOPE,
            MODULE_NN_MCU,
            MODULE_NN_NS,
            MODULE_NN_NEWS,
            MODULE_NN_RO,
            MODULE_NN_GD,
            MODULE_NN_CARDSPI,
            MODULE_NN_EC,
            MODULE_NN_WEBBRS,
            MODULE_NN_TEST,
            MODULE_NN_ENC,
            MODULE_NN_PIA,
            MODULE_APPLICATION = 254,
            MODULE_INVALID_RESULT_VALUE
    };

    enum Description{
            DESCRIPTION_SUCCESS              = 0,
            DESCRIPTION_INVALID_SELECTION    = 1000,
            DESCRIPTION_TOO_LARGE            = 1001,
            DESCRIPTION_NOT_AUTHORIZED       = 1002,
            DESCRIPTION_ALREADY_DONE         = 1003,
            DESCRIPTION_INVALID_SIZE         = 1004,
            DESCRIPTION_INVALID_ENUM_VALUE   = 1005,
            DESCRIPTION_INVALID_COMBINATION  = 1006,
            DESCRIPTION_NO_DATA              = 1007,
            DESCRIPTION_BUSY                 = 1008,
            DESCRIPTION_MISALIGNED_ADDRESS   = 1009,
            DESCRIPTION_MISALIGNED_SIZE      = 1010,
            DESCRIPTION_OUT_OF_MEMORY        = 1011,
            DESCRIPTION_NOT_IMPLEMENTED      = 1012,
            DESCRIPTION_INVALID_ADDRESS      = 1013,
            DESCRIPTION_INVALID_POINTER      = 1014,
            DESCRIPTION_INVALID_HANDLE       = 1015,
            DESCRIPTION_NOT_INITIALIZED      = 1016,
            DESCRIPTION_ALREADY_INITIALIZED  = 1017,
            DESCRIPTION_NOT_FOUND            = 1018,
            DESCRIPTION_CANCEL_REQUESTED     = 1019,
            DESCRIPTION_ALREADY_EXISTS       = 1020,
            DESCRIPTION_OUT_OF_RANGE         = 1021,
            DESCRIPTION_TIMEOUT              = 1022,
            DESCRIPTION_INVALID_RESULT_VALUE = 1023,
    };

    Result() : mResult(0){
    };
    bool Failed() const{
        return mResult & 0x80000000;
    }
    bool Succeeded() const {
        return !Failed();
    }
    // Add description,modtype, etc later since github deleted my shit.
};