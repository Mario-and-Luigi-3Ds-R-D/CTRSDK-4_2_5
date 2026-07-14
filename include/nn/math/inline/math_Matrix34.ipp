#pragma once

#include <cmath>
#include <nn/math/math_Vec3.h>
#include <nn/Assert.h>

namespace nn {
namespace math {

inline MTX34* MTX34TextureProjectionFrustum(MTX34* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT){

    f32 reverseWidth = 1.0f / (r - l);

    f32 (*const mtx)[4] = pOut->matrix;

    mtx[0][0] = ((2.0f * n) * reverseWidth) * scaleS;
    mtx[0][1] = 0.0f;
    mtx[0][2] = (((r + l) * reverseWidth) * scaleS) - translateS;
    mtx[0][3] = 0.0f;

    f32 reverseHeight = 1.0f / (t - b);
    mtx[1][0] = 0.0f;
    mtx[1][1] = ((2.0f * n) * reverseHeight) * scaleT;
    mtx[1][2] = (((t+ b) * reverseHeight) * scaleT) - translateT;
    mtx[1][3] = 0.0f;

    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = -1.0f;
    mtx[2][3] = 0.0f;
    return pOut;
}

inline MTX34* MTX34TextureProjectionPerspective(MTX34* pOut, f32 fovy, f32 aspect, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT){
    f32 angle = fovy * 0.5f;
    f32 cot = 1.0f / math::TanRad(angle);

    f32 (*const mtx)[4] = pOut->matrix;

    mtx[0][0] = (cot / aspect) * scaleS;
    mtx[0][1] = 0.0f;
    mtx[0][2] = -translateS;
    mtx[0][3] = 0.0f;

    mtx[1][0] = 0.0f;
    mtx[1][1] = cot * scaleT;
    mtx[1][2] = -translateT;
    mtx[1][3] = 0.0f;

    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = -1.0f;
    mtx[2][3] = 0.0f;

    return pOut;
}
}
}