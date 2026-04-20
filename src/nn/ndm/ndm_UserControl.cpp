#include <nn/ndm/ndm_UserControl.h>
#include <nn/ndm/ndm_Interface.h>
#include <nn/dbg/dbg_Break.h>

namespace nn{
namespace ndm{

Result Initialize(){
    
}
// Suspends the current Daemons.
__asm Result SuspendDaemons(bit32 mask){
    NOP
    PUSH            {R4,LR}
    MRC             p15, 0, R4,c13,c0, 3
    LDR             R1, =0x60040
    STR             R1, [R4,#0x80]!
    STR             R0, [R4,#4]
    LDR             R0, =__cpp(&CTR::detail::Interface::sSession)
    LDR             R0, [R0]
    SVC             0x32
    AND             R1, R0, #0x80000000
    CMP             R1, #0
    LDRGE           R0, [R4,#4]
    POP             {R4,PC}
}

}
}