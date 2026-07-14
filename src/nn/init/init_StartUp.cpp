// Filename: init_StartUp.cpp
//
// Project: Horizon CTRSDK

#include <nn/os/os_Initialize.h>
#include <nn/os/CTR/os_ErrorHandler.h>
#include <nn/ndm/ndm_Setup.h>
#include <nn/applet/CTR/applet_API.h>

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