#include <nn/svc/svc_Api.h>
#include <rt_locale.h>
#include <rt_sys.h>

extern "C" __weak void __cpp_initialize__aeabi_();

extern "C"{
    void nninitRegion(); // native
    void nninitLocale(); // native
    void nninitSystem(); // init_Startup.cpp
    void nninitStartUp(); // init_Startup.cpp

    u32* __rt_locale(void);
    void _fp_init(void);

    void nnMain();
    void nninitCallStaticInitializers(); // init_Startup.cpp
    void nninitSetup(); // init_Startup.cpp

    extern u8 Image$$ZI$$ZI$$Limit[]; // ARMCC thingies
    extern u8 Image$$ZI$$ZI$$Base[]; // ARMCC thingies

#pragma arm

__asm void __ctr_start(){
    bl __cpp(nninitRegion)
    bl __cpp(nninitLocale)
    bl __cpp(nninitSystem)
    bl __cpp(nninitStartUp)
    blx __cpp(__cpp_initialize__aeabi_) // BLX, Moddimation makes it BL'n yet ghidra saids otherwise.Plus raw bytes do to.
    bl __cpp(nninitCallStaticInitializers)
    bl __cpp(nninitSetup)
    bl __cpp(nnMain)
    b __cpp(nn::svc::ExitProcess)
}

__asm void nninitRegion(){
    ldr     r0,=__cpp(Image$$ZI$$ZI$$Base) ; BADGE::PARAM
    ldr     r1,=__cpp(Image$$ZI$$ZI$$Limit) ; 
    mov     r2,#0x0
region_loop
    cmp     r0,r1
    strcc   r2,[r0],#4
    bcc     region_loop
    bx      lr
};

__asm void nninitLocale(){
    LDR             R1, =0x4000000
    MOV             R0, #0
    PUSH            {R4,LR}
    NOP
    LDR             R1, =0x4000026
    MOV             R0, #0
    NOP
    BL              __cpp(__rt_locale)
    MOV             R4, R0
    MOV             R1, #0
    MOV             R0, R1
    BL              __cpp(_get_lc_ctype)
    ADD             R0, R0, #1
    MOV             R1, #0
    STR             R0, [R4,#4]
    MOV             R0, R1
    BL              __cpp(_get_lc_numeric)
    STR             R0, [R4,#0xC]
    POP             {R4,PC}
}

} // extern "C"