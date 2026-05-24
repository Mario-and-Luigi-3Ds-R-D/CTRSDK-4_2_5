#pragma once

#include <cmath>

namespace nn {
namespace math {
    
    struct VEC3{
        VEC3() {}
        explicit VEC3(const f32* p) { x = p[0]; y = p[1]; z = p[2]; }
        VEC3(const VEC3& v) { x = v.x; y = v.y; z = v.z; }
        VEC3(f32 fx, f32 fy, f32 fz) { x = fx; y = fy; z = fz; }

        float x;
        float y;
        float z;
    };
namespace ARMv6{
    inline VEC3* VEC3NormalizeC(VEC3* pOut, const VEC3* p){
        register f32 x, y, z, mag;
    
        x = p->x;
        y = p->y;
        z = p->z;
    
        mag = (x * x) + (y * y) + (z * z);

        mag = 1.0f / ::std::sqrtf(mag);
    
        x *= mag;
        y *= mag;
        z *= mag;

        pOut->x = x;
        pOut->y = y;
        pOut->z = z;

        return pOut;
    }
    inline VEC3* VEC3NormalizeC_FAST(VEC3* pOut, const VEC3* p){

        register f32 x, y, z, mag;
        
        x = p->x;
        y = p->y;
        z = p->z;
        
        mag = (x * x) + (y * y) + (z * z);

        mag = 1.0f / ::std::sqrtf(mag);
        
        x *= mag;
        y *= mag;
        z *= mag;

        pOut->x = x;
        pOut->y = y;
        pOut->z = z;

        return pOut;
    }
    


    inline VEC3* VEC3Normalize(VEC3* pOut, const VEC3* p){
        #ifdef NN_DEBUG // Unoptimized check.
            return ARMv6::VEC3NormalizeC(pOut, p);
        #else  
            return ARMv6::VEC3NormalizeC_FAST(pOut, p);
        #endif
    }
}
}
}