#include <nn/os/CTR/os_ErrorHandler.h>

namespace nn{
namespace os{
namespace CTR{
namespace detail{
void SetInternalErrorHandlingMode(bool preferFatal){
    nn::os::CTR::detail::sPreferFatal = preferFatal;
    return;
}

void HandleInternalError(Result result){

}

}
}
}
}