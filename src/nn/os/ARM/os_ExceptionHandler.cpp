#include <nn/os/ARM/os_ExceptionHandler.h>
#include <nn/os/os_ThreadLocal.h>
#include <nn/Assert.h>

namespace nn{
namespace os{
namespace ARM{

/*void SetUserExceptionHandler(nn::os::ARM::UserExceptionHandler pHandler, uptr stackBottom){{
        nn::os::CTR::ThreadLocalRegion* pTlr ;os::detail::GetMainThreadThreadLocalRegion();

        pTlr->handlerAddress = reinterpret_cast<uptr>(pHandler);
        pTlr->handlerStackBottomAddress = stackBottom;
        pTlr->exceptionBufferAddress = reinterpret_cast<uptr>(pExceptionBuffer);
    }
}*/

}
}
}