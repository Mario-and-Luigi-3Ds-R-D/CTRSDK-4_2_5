#pragma once

#include "nn/types.h"
#include "nn/math/math_Matrix33.h"
#include "nn/math/math_Vec3.h"

namespace nn{
namespace math{

class MTX34;

MTX34* MTX34Copy(MTX34* pOut, const MTX34* p);
bool   MTX34IsIdentity(const MTX34* p);

class MTX34{ // i would name it Matrix34_f32, but I cant static.crs which sucks but fuck it
public:
    float matrix[3][4];
public:
    static const int ROW_COUNT = 3;
    static const int COLUMN_COUNT = 4;
    
    /* Constructors */

    MTX34() {}
    MTX34(const MTX34& rhs)        { MTX34Copy(this, &rhs); }
    explicit MTX34(const f32* p)   { MTX34Copy(this, (MTX34*)p); }
    MTX34(f32 x00, f32 x01, f32 x02, f32 x03,f32 x10, f32 x11, f32 x12, f32 x13,f32 x20, f32 x21, f32 x22, f32 x23);

    /* Inlines */

    static const MTX34& Identity(){
        static const MTX34 identity(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,0.0f, 0.0f, 1.0f, 0.0f);
        return identity;
    }
    bool IsIdentity() const { return MTX34IsIdentity(this); }
};

inline bool MTX34IsIdentity(const MTX34& m) { return MTX34IsIdentity( &m ); }

inline bool MTX34IsIdentity(const MTX34* p) { 
    return p->matrix[0][0] == 1.f && p->matrix[0][1] == 0.f && p->matrix[0][2] == 0.f && p->matrix[0][3] == 0.f &&
           p->matrix[1][0] == 0.f && p->matrix[1][1] == 1.f && p->matrix[1][2] == 0.f && p->matrix[1][3] == 0.f &&
           p->matrix[2][0] == 0.f && p->matrix[2][1] == 0.f && p->matrix[2][2] == 1.f && p->matrix[2][3] == 0.f;
}

//
/* ARMv6*/
//

namespace ARMv6{

/* VEC3 */

VEC3* VEC3TransformAsm(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV);
inline VEC3* VEC3TransformC(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV);
inline VEC3* VEC3Transform(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV){
    #ifdef NN_DEBUG // Unoptimized check.
        return ARMv6::VEC3TransformC(pOut,pM,pV);
    #else
        return ARMv6::VEC3TransformAsm(pOut, pM, pV);
    #endif
}

/* MTX ASM */

MTX34* MTX34CopyAsm(nn::math::MTX34 *,nn::math::MTX34 const*);
MTX34* MTX34MultAsm(nn::math::MTX34 *,nn::math::MTX34 const*,math::MTX34 const*);
MTX34* MTX34MultAsm(nn::math::MTX34 *,nn::math::MTX34 const*,float);
MTX34* MTX34AddAsm(nn::math::MTX34 *,nn::math::MTX34 const*,nn::math::MTX34 const*);
MTX34* MTX34MultScaleAsm(nn::math::MTX34 *,nn::math::MTX34 const*,nn::math::VEC3 const*);
u32 MTX34InverseAsm(nn::math::MTX34 *,nn::math::MTX34 const*);
u32 MTX34InvTransposeAsm(nn::math::MTX34 *,nn::math::MTX34 const*);
MTX34* MTX34MultTranslateAsm(nn::math::MTX34 *,nn::math::VEC3 const*,nn::math::MTX34 const*);
MTX34* MTX34MultTranslateAsm(nn::math::MTX34 *,nn::math::MTX34 const*,nn::math::VEC3 const*);
MTX34* MTX34TransposeAsm(nn::math::MTX34 *,nn::math::MTX34 const*);
void MTX34ToMTX33Asm(nn::math::MTX33 *,nn::math::MTX34 const*);
u32 MTX34InverseC(MTX34* pOut, const MTX34* p);

inline u32 MTX34Inverse(MTX34* pOut, const MTX34* p){
    #ifdef NN_DEBUG
        return ARMv6::MTX34InverseC(pOut,p);
    #else
        return ARMv6::MTX34InverseAsm(pOut,p);
    #endif
}

} // ARMv6
} // math
} // nn