#pragma once

#include <nn/Result.h>

namespace nn{
namespace ro{



NN_DEFINE_RESULT_CONST(ResultAlreadyInitialized, Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_RO, Result::DESCRIPTION_ALREADY_INITIALIZED);
NN_DEFINE_RESULT_CONST(ResultNotInitialized, Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_RO, Result::DESCRIPTION_NOT_INITIALIZED);

}
}