#pragma once

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

}
}