#include <nn/math/math_Vec3.h>
#include <nn/dbg/dbg_Break.h>

namespace nn{
namespace math{
class MTX34;

namespace ARMv6{

inline VEC3* VEC3TransformC(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV){
    VEC3 vTmp;
    VEC3* pDst = (pOut == pV) ? &vTmp : pOut;
    
    pDst->x = pM->matrix[0][0] * pV->x + pM->matrix[0][1] * pV->y + pM->matrix[0][2] * pV->z + pM->matrix[0][3];
    pDst->y = pM->matrix[1][0] * pV->x + pM->matrix[1][1] * pV->y + pM->matrix[1][2] * pV->z + pM->matrix[1][3];
    pDst->z = pM->matrix[2][0] * pV->x + pM->matrix[2][1] * pV->y + pM->matrix[2][2] * pV->z + pM->matrix[2][3];
    
    if (pDst == &vTmp){
        pOut->x = pDst->x;
        pOut->y = pDst->y;
        pOut->z = pDst->z;
    }
    return pOut;
}

}
}
}