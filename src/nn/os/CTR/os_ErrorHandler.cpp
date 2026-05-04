#include <nn/os/CTR/os_ErrorHandler.h>
#include <nn/err/CTR/err_Api.h>
#include <nn/dbg/dbg_Break.h>


namespace nn{
namespace os{
namespace CTR{
namespace detail{

void SetInternalErrorHandlingMode(bool preferFatal){
    nn::os::CTR::detail::sPreferFatal = preferFatal;
    return;
}

void HandleInternalError(Result result){
    // TODO
}

}
}
}
}