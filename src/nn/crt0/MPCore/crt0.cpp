#include <nn/svc/svc_Api.h>
#include <nn/init/init_Default.h>
#include <nn/util/detail/util_Symbol.h>
#include <rt_locale.h>
#include <rt_sys.h>

extern "C" __weak void __cpp_initialize__aeabi_(void);

extern "C"{
    void nninitRegion(); // native
    void nninitLocale(); // native
    void nninitSystem(); // init_Startup.cpp
    void nninitStartUp(); // init_Startup.cpp

    u32* __rt_locale(void); // ARMCC
    void _fp_init(void); // ARMCC

    void nninitCallStaticInitializers(); // init_Startup.cpp
    void nninitSetup(); // init_Startup.cpp

    extern u8 Image$$ZI$$ZI$$Limit[]; // ARMCC
    extern u8 Image$$ZI$$ZI$$Base[]; // ARMCC

#pragma arm
__asm void __ctr_start(){
    PRESERVE8
    bl __cpp(nninitRegion) // Region
    bl __cpp(nninitLocale) // Locale
    bl __cpp(nninitSystem) // System
    bl __cpp(nninitStartUp) // Startup
    blx __cpp(__cpp_initialize__aeabi_) // Initialize CPP ARM
    bl __cpp(nninitCallStaticInitializers) // Static Initializer Manager
    bl __cpp(nninitSetup) // Initializes Setup
    bl __cpp(nnMain) // Main Application Loop
    b __cpp(nn::svc::ExitProcess) // Exit Process if needed
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