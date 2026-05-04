#pragma once

#include "nn/types.h"
#include "nn/math/math_Vec3.h"
#include "nn/math/math_Matrix44.h"
#include "nn/math/math_Matrix34.h"

using namespace nn::math;

namespace nn{
namespace ulcd{
namespace CTR{
namespace{
    struct Direction{
        VEC3 right;
        VEC3 up;
        VEC3 target;
    };
}
    void GetLookPose(const nn::math::MTX34 *view,nn::math::VEC3 *pos,Direction *dir);

    class StereoCamera{
    public:
        struct CameraInfo{
            f32 mLeft;
            f32 mRight;
            f32 mBottom;
            f32 mTop;
            f32 mNear;
            f32 mFar;

            VEC3 mPosition;
            VEC3 mPosRight;
            VEC3 mPosUp;
            VEC3 mPosTarget;
        };

    // StereoCamera Members
    CameraInfo mBaseCamera;
    f32 mLimitParallex;
    f32 mLevelWidth;
    f32 mDepthLevel;
    f32 mDistanceToNearClip;
    f32 mDistanceToFarClip;
    f32 mCameraInterval;

    // Theres more to this.
    f32 CalculateMaxtrices(MTX44 *projL,MTX34 *viewL,MTX44 *projR,MTX34 *viewR, MTX44 *projOriginal,MTX34 *viewOriginal,f32 depthLevel,f32 factor,bool realSwitch);
    f32 CalculateMatricesReal(nn::math::MTX44* projL, nn::math::MTX34* viewL,nn::math::MTX44* projR, nn::math::MTX34* viewR, const f32 depthLevel, const f32 factor, const nn::math::PivotDirection pivot = nn::math::PIVOT_UPSIDE_TO_TOP);
    f32 GetCoefficientForParallax(void) const;
    void SetBaseFrustum(const MTX44 *proj);
    void SetBaseCamera(const MTX34 *view);
    void Initialize();
    void Finalize();
    StereoCamera();
    ~StereoCamera();

}; // StereoCamera

namespace{
bool IsInitialized;

}
}
}
}