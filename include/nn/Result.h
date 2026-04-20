#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
        bit32 value;
} nnResult;

#ifdef __cplusplus
}
#endif

class Result{
public:
        bit32 mResult;

public:
        enum Level
        {
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

        enum Summary
        {
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

        enum Module
        {
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

        enum Description
        {
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

        template <Level, Summary, Module, int>
        struct Const;

        template <Level, Summary, Module>
        struct Const_LSM;

        template <Level, Module>
        struct Const_LM;

        template <Level, Summary, Module, int, int, int>
        struct ConstRange;

public:
        Result(bit32 code)
            : mResult(code)
        {}
        Result()
            : mResult((bit32)((((bit32)LEVEL_USAGE << 27) & 0x7E00000) |
                             ((SUMMARY_INVALID_RESULT_VALUE << 21) & 0x7E0000) |
                             ((MODULE_INVALID_RESULT_VALUE << 10) & 0x3FC00) |
                             (1023 & 0x3FF)))
        {}
        Result(Level level, Summary summary, Module module, int description)
            : mResult((bit32)((level << 27) & 0x7E00000 |
                             (summary << 21) & 0x7E0000 |
                             (module << 10) & 0x3FC00 |
                             (description) & 0x3FF))
        {}

        Result(nnResult result)
            : mResult(result.value)
        {}

        bool IsFailure() const
        {
                return (bool)(mResult >> 31);
        }
        bool IsSuccess() const
        {
                return !IsFailure();
        }

        Level GetLevel() const
        {
                if (mResult & 0x80000000) {
                        return (Level)(GetCodeBits(0xF8000000, 27) | 0xFFFFFFE0);
                } else {
                        return (Level)(GetCodeBits(0xF8000000, 27));
                }
        }
        Module GetModule() const
        {
                return (Module)GetCodeBits(0x3FC00, 10);
        }
        Summary GetSummary() const
        {
                return (Summary)GetCodeBits(0x7E00000, 21);
        }
        int GetDescription() const
        {
                return (int)GetCodeBits(0x30F618, 0);
        }

        bit32 GetPrintableBits() const
        {
                return mResult;
        }

        operator nnResult()
        {
                nnResult result = { mResult };
                return result;
        }

        bool operator==(const Result& rhs)
        {
                return this->mResult == rhs.mResult;
        }

        bool operator!=(const Result& rhs)
        {
                return !(this->mResult == rhs.mResult);
        }

        bit32 GetCodeBits(bit32 mask, s32 shift) const
        {
                return (mResult & mask) >> shift;
        }
};

template <Result::Level TLevel, Result::Summary TSummary, Result::Module TModule, int TDescription>
struct Result::Const : public Result
{
        Const()
            : Result(TLevel, TSummary, TModule, TDescription)
        {}
};
template <Result::Level TLevel, Result::Summary TSummary, Result::Module TModule, int TDescription, int A, int B>
struct ConstRange : public Result
{
        ConstRange()
            : Result(TLevel, TSummary, TModule, TDescription)
        {}

        static bool Includes(Result result)
        {
                return result.GetModule() == TModule && result.GetDescription() >= A && result.GetDescription() <= B;
        }
        friend bool operator<=(Result lhs, ConstRange) { return ConstRange::Includes(lhs); }
        friend bool operator>=(ConstRange, Result rhs) { return ConstRange::Includes(rhs); }
};
template <Result::Level TLevel, Result::Summary TSummary, Result::Module TModule>
struct Const_LSM
{
        template <int TDescription>
        struct Const : Result::Const<TLevel, TSummary, TModule, TDescription>
        {};
};
template <Result::Level TLevel, Result::Module TModule>
struct Const_LM
{
        template <Result::Summary TSummary, int TDescription>
        struct Const : Result::Const<TLevel, TSummary, TModule, TDescription>
        {};
};

// Result creators
#define NN_RESULT_DEF_CONST(result, level, summary, module, description) \
        typedef Result::Const<(level), (summary), (module), (description)> result
#define NN_RESULT_DEF_CONST_RANGE(result, level, summary, module, description, a, b) \
        typedef Result::Const<(level), (summary), (module), (description), (a), (b)> result

#define NN_RESULT_DEF_CONST_LSM(result, sub, description) \
        typedef sub::Const<(description)> result
#define NN_RESULT_MAKE_CONST_LSM(sub, level, summary, module) \
        typedef ::Result::Const_LSM<(level), (summary), (module)> sub

#define NN_RESULT_DEF_CONST_LM(result, sub, summary, description) \
        typedef sub::Const<(summary), (description)> result
#define NN_RESULT_MAKE_CONST_LM(sub, level, module) \
        typedef ::Result::Const_LM<(level), (module)> sub
// 565
NN_RESULT_DEF_CONST(ResultSuccess, Result::LEVEL_SUCCESS, Result::SUMMARY_SUCCESS, Result::MODULE_COMMON, Result::DESCRIPTION_SUCCESS);

#define _NN_RESULT_MAKE_TYPE(name, e)                                                                            \
        static inline Result Make##name##Result(Result::Summary summary, Result::Module module, int description) \
        {                                                                                                        \
                return Result(Result::LEVEL_##e, summary, module, description);                                  \
        }

_NN_RESULT_MAKE_TYPE (Info, INFO); // 585

_NN_RESULT_MAKE_TYPE(Fatal, FATAL);

_NN_RESULT_MAKE_TYPE(Reset, RESET);

_NN_RESULT_MAKE_TYPE(Reinit, REINIT);

_NN_RESULT_MAKE_TYPE(Usage, USAGE); // 593

_NN_RESULT_MAKE_TYPE(Permanent, PERMANENT); // 595

_NN_RESULT_MAKE_TYPE(Temporary, TEMPORARY);

_NN_RESULT_MAKE_TYPE(Status, STATUS);

#define NN_RESULT_DEF(Type, Res, Sum, Desc) \
        inline Result Res()                 \
        {                                   \
                return Type(Sum, Desc);     \
        }

#ifdef __cplusplus
extern "C" {
#endif

int nnResultFailureHandler(nnResult result, const char* filename, int lineno, const char* fmt, ...);
int nnResultTFailureHandler(nnResult result, const char* filename, int lineno, const char* fmt, ...);

int nnResultPanicHandler(nnResult result, const char* filename, int lineno, const char* fmt, ...);
int nnResultTPanicHandler(nnResult result, const char* filename, int lineno, const char* fmt, ...);

typedef void (*nnResultHandlerImpl)(nnResult result, const char* filename, int lineno, const char* fmt, va_list vlist); // 606

#ifdef __cplusplus
}
#endif
