#include <nn/os/os_Initialize.h>
#include <nn/os/CTR/os_ErrorHandler.h>
#include <nn/ndm/ndm_UserControl.h>
#include <nn/applet/CTR/applet_Api.h>

namespace nn {
namespace applet {
namespace CTR {
namespace detail {
    __declspec(noinline) Result Initialize(AppletAttr appletAttr){ // TODO MACRO
        return ResultSuccess();
    }
}
}
}
}

#define NN_SYSTEM_DEFAULT_HEAP_SIZE     0x00800000

typedef void (*nninitStaticInitFunc)(void);
extern "C" nninitStaticInitFunc Image$$STATIC_INIT$$RO$$Base[];
extern "C" nninitStaticInitFunc Image$$STATIC_INIT$$RO$$Limit[];

extern "C"{

void nninitStartUpDefault(); // init_Default.cpp 
void nninitSetupDefault(); // init_Default.cpp

__weak void nninitSystem(){
   nn::os::Initialize();
}

__weak void nninitSetupDameons(){
    nn::ndm::SetupDaemonsDefault();
}

void nninitCallStaticInitializers(){
    for(nninitStaticInitFunc* f = Image$$STATIC_INIT$$RO$$Base;
         f < Image$$STATIC_INIT$$RO$$Limit;
         ++f ){
        (*f)();
    }
}

void nninitSetup(){
    nninitSetupDefault();
    nn::os::CTR::detail::SetInternalErrorHandlingMode(false);
    nn::applet::CTR::detail::Initialize(0);
    nninitSetupDameons();
}

}