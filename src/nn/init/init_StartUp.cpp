#include <nn/os/os_Initialize.h>
#include <nn/ndm/ndm_UserControl.h>

typedef void (*nninitStaticInitFunc)(void);
extern "C" nninitStaticInitFunc Image$$STATIC_INIT$$RO$$Base[];
extern "C" nninitStaticInitFunc Image$$STATIC_INIT$$RO$$Limit[];

extern "C"{

void nninitStartUpDefault(); // init_Default.cpp 
void nninitSetupDefault(); // init_Default.cpp

void nninitSystem(){
   nn::os::Initialize();
}

__weak void nninitStartUp(){
    nninitStartUpDefault();

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
    nninitSetupDameons();
}

}