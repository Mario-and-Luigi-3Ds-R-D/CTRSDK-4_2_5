#pragma once

#include "nn/types.h"
#include "nn/math/math_Vec3.h"
/*#include "nn/math/math_Matrix44.h"
#include "nn/math/math_Matrix34.h"*/

namespace nn{
namespace ulcd{
namespace CTR{
    class StereoCamera{
    public:
        struct CameraInfo{
        public:
            f32 mLeft;
            f32 mRight;
            f32 mBottom;
            f32 mTop;
            f32 mNear;
            f32 mFar;
            nn::math::VEC3 mPosition;
            nn::math::VEC3 mRightDir;
            nn::math::VEC3 mUpDir;
            nn::math::VEC3 mTarget;
        };
    nn::ulcd::CTR::StereoCamera::CameraInfo mBaseCamera;
    f32 mLimitParallex;
    f32 mLevelWidth;
    f32 mDepthLevel;
    f32 mDistanceToNearClip;
    f32 mDistanceToFarClip;
    f32 mCameraInterval;

/*    f32 CalculateMaxtrices(Matrix44 *projL,Matrix34 *viewL,Matrix44 *projR,Matrix34 *viewR, Matrix44 *projOriginal,Matrix34 *viewOriginal,f32 depthLevel,f32 factor,bool realSwitch)
    f32 GetParallex();
    void Initialize();
    StereoCamera();
*/
}; // StereoCamera

namespace{

//void GetLookPose(Matrix34 *view,Vector3 *pos,Direction *dir)

}// _annoymous_
}// ctr
}// ulcd
}