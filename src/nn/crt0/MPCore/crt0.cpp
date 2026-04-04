#include <nn/svc/svc_Api.h>
#include <nn/Module.h>
#include <rt_locale.h>
#include <rt_sys.h>

/*namespace {
NN_MAKE_MODULE_SDK (s_SdkVersion, "CTR_SDK-4_2_5_200_none");
NN_MAKE_MODULE_SDK (s_FirmwareVersion, "Firmware-02_30_20");
}*/

extern "C"{
    void nninitRegion(); // native
    void nninitLocale(); // native
    void nninitSystem(); // init_Startup.cpp
    void nninitStartUp(); // init_Startup.cpp

    void __cpp_initialize_aeabi_(){} // {} here
    //u32* __rt_locale(void);

    void nnMain();
    void nninitCallStaticInitializers(); // init_Startup.cpp
    void nninitSetup(); // init_Startup.cpp

__asm void __ctr_start(){
    bl __cpp(nninitRegion)
    bl __cpp(nninitLocale)
    bl __cpp(nninitSystem)
    bl __cpp(nninitStartUp)
    blx __cpp(__cpp_initialize_aeabi_) // BLX, Moddimation makes it BL'n yet ghidra saids otherwise.Plus raw bytes do to.
    bl __cpp(nninitCallStaticInitializers)
    bl __cpp(nninitSetup)
    bl __cpp(nnMain)
    b __cpp(nn::svc::ExitProcess)
}

__asm void nninitRegion(){
    ldr     r0,=__cpp(0x006E14A8) ; BADGE::PARAM
    ldr     r1,=__cpp(0x0071211C) ; 
    mov     r2,#0x0
region_loop
    cmp     r0,r1
    strcc   r2,[r0],#4
    bcc     region_loop
    bx      lr
};

__asm void nninitLocale(){
    bx lr
}

} // extern "C"