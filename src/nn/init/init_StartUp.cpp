#include <nn/os/os_Initialize.h>

extern "C"{

void nninitStartUpDefault(); // init_Default.cpp 
void nninitSetupDaemonsDefault(){} // nn::ndm::SetupDaemonsDefault
void nninitSetupDefault(); // init_Default.cpp

void nninitSystem(){
    nn::os::Initialize();
}

__weak void nninitStartUp(){
    nninitStartUpDefault();
}

__weak void nninitSetupDameons(){
    nninitSetupDaemonsDefault();
}

__asm void nninitCallStaticInitializers(){
        PUSH            {R4,R5,R6,LR}
        LDR             R4,=0x6C8124
        LDR             R5,=0x6C8124
        CMP             R4, R5
        BCS             returnpop
static_loop
        LDR             R0, [R4]
        BLX             R0
        ADD             R4, R4, #4
        CMP             R4, R5
        BCC             static_loop
returnpop
        POP             {R4,R5,R6,PC}
}

void nninitSetup(){

}
}