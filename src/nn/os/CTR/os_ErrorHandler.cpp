// Filename: os_ErrorHandler.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/os/CTR/os_ErrorHandler.h>
#include <nn/err/CTR/err_Api.h>
#include <nn/dbg/dbg_Break.h>


namespace nn{
namespace os{
namespace CTR{
namespace detail{

void SetInternalErrorHandlingMode(bool preferFatal){
    nn::os::CTR::detail::sPreferFatal = preferFatal;
}

void HandleInternalError(Result result){
    // TODO
}

}
}
}
}