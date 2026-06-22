#pragma once

#include <nn/types.h>
#include <nn/assert.h>

#ifdef  __cplusplus
extern "C" {
#endif

    typedef enum nngxMemAccessPrioMode{
        NN_GX_MEM_ACCESS_PRIO_MODE_0 = 0x00000000,
        NN_GX_MEM_ACCESS_PRIO_MODE_1 = 0x00000205,
        NN_GX_MEM_ACCESS_PRIO_MODE_2 = 0x00000203,
        NN_GX_MEM_ACCESS_PRIO_MODE_3 = 0x00000305,
        NN_GX_MEM_ACCESS_PRIO_MODE_4 = 0x00000105,
        
        NN_GX_MEM_ACCESS_PRIO_MODE_MAX = 0x7FFFFFFF
    } nngxMemAccessPrioMode;
    
    typedef enum nngxInternalDriverPrioMode{
        NN_GX_INTERNAL_DRIVER_PRIO_MODE_HIGH,
        NN_GX_INTERNAL_DRIVER_PRIO_MODE_LOW
    } nngxInternalDriverPrioMode;

    void nngxSetMemAccessPrioMode(nngxMemAccessPrioMode mode);

    bool nngxIsStereoVisionAllowed(void);

    void nngxSetInternalDriverPrioMode(nngxInternalDriverPrioMode mode);

    void nngxSetAutoWaitMode(s32 paramIndex);

#ifdef  __cplusplus
} // extern "C"
#endif // __cplusplus

#ifdef  __cplusplus
namespace nn {
namespace gx {
namespace CTR {

    enum MemAccessPrioMode{

        MEM_ACCESS_PRIO_MODE_0 = NN_GX_MEM_ACCESS_PRIO_MODE_0,

        MEM_ACCESS_PRIO_MODE_1 = NN_GX_MEM_ACCESS_PRIO_MODE_1,

        MEM_ACCESS_PRIO_MODE_2 = NN_GX_MEM_ACCESS_PRIO_MODE_2,

        MEM_ACCESS_PRIO_MODE_3 = NN_GX_MEM_ACCESS_PRIO_MODE_3,

        MEM_ACCESS_PRIO_MODE_4 = NN_GX_MEM_ACCESS_PRIO_MODE_4,
        
        MEM_ACCESS_PRIO_MODE_MAX = NN_GX_MEM_ACCESS_PRIO_MODE_MAX
    };

    inline void SetMemAccessPrioMode( MemAccessPrioMode mode ){
        nngxSetMemAccessPrioMode(static_cast<nngxMemAccessPrioMode>(mode));
    }

    inline bool IsStereoVisionAllowed( void ){
        return nngxIsStereoVisionAllowed();
    }

    enum InternalDriverPrioMode{
        INTERNAL_DRIVER_PRIO_MODE_HIGH = NN_GX_INTERNAL_DRIVER_PRIO_MODE_HIGH,
        INTERNAL_DRIVER_PRIO_MODE_LOW  = NN_GX_INTERNAL_DRIVER_PRIO_MODE_LOW
    };
    inline void SetInternalDriverPrioMode( InternalDriverPrioMode mode ){
        nngxSetInternalDriverPrioMode(static_cast<nngxInternalDriverPrioMode>(mode));
    }
    inline void SetAutoWaitMode( s32 paramIndex ){
        nngxSetAutoWaitMode(paramIndex);
    }
}
}
}
#endif // __cplusplus