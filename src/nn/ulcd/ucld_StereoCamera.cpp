// Filename: ucld_StereoCamera.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/ucld/CTR/ucld_StereoCamera.h>
#include <nn/cfg/CTR/cfg_Api.h>
#include <nn/cfg/CTR/cfg_DetailApi.h>
#include <nn/dbg/dbg_Break.h>

#include <string.h>

namespace nn{
namespace ulcd{
namespace CTR{
namespace{

void GetLookPose(const nn::math::MTX34 *view,nn::math::VEC3 *pos,Direction *dir){
    MTX34 im;

    math::ARMv6::MTX34Inverse(&im,view);
    pos->x = im.matrix[0][3];
    pos->y = im.matrix[1][3];
    pos->z = im.matrix[2][3];
    dir->right.x = im.matrix[0][0];
    dir->right.y = im.matrix[1][0];
    dir->right.z = im.matrix[2][0];
    dir->up.x = im.matrix[0][1];
    dir->up.y = im.matrix[1][1];
    dir->up.z = im.matrix[2][1];
    dir->target.x = im.matrix[0][2];
    dir->target.y = im.matrix[1][2];
    dir->target.z = im.matrix[2][2];
    math::ARMv6::VEC3Normalize(&dir->right,&dir->right);
    math::ARMv6::VEC3Normalize(&dir->up,&dir->up);
    math::ARMv6::VEC3Normalize(&dir->target,&dir->target);
}

}

f32 StereoCamera::CalculateMaxtrices(nn::math::MTX44 *projL,nn::math::MTX34 *viewL,nn::math::MTX44 *projR,nn::math::MTX34 *viewR, nn::math::MTX44 *projOriginal,nn::math::MTX34 *viewOriginal,f32 depthLevel,f32 factor,bool realSwitch){

}

f32 StereoCamera::CalculateMatricesReal(nn::math::MTX44* projL, nn::math::MTX34* viewL,nn::math::MTX44* projR, nn::math::MTX34* viewR, const f32 depthLevel, const f32 factor, const nn::math::PivotDirection pivot){

}

f32 StereoCamera::GetCoefficientForParallax(void) const{
    this->mCameraInterval / this->mLevelWidth;
}

void StereoCamera::SetBaseCamera(const nn::math::MTX34 *view){
    Direction direction;
    GetLookPose(view, &this->mBaseCamera.mPosition, &direction);
    
    memcpy(&this->mBaseCamera.mPosRight,&direction,0xc);
    memcpy(&this->mBaseCamera.mPosUp,&direction,0xc);
    memcpy(&this->mBaseCamera.mPosTarget,&direction,0xc);
}

void StereoCamera::SetBaseFrustum(const nn::math::MTX44 *proj){
    this->mBaseCamera.mNear = proj->matrix[2][3] / proj->matrix[2][2];
    this->mBaseCamera.mFar = proj->matrix[2][3] / (proj->matrix[2][2] - 1.0f);

    f32 inverseProjX = proj->matrix[2][3] / (proj->matrix[0][0] * proj->matrix[2][2]);
    f32 inverseProjY = proj->matrix[2][3] / (proj->matrix[1][1] * proj->matrix[2][2]);

    this->mBaseCamera.mLeft = (proj->matrix[0][2] - 1.0f) * inverseProjX;
    this->mBaseCamera.mRight = (proj->matrix[0][2] + 1.0f) * inverseProjX;
    this->mBaseCamera.mTop = (proj->matrix[1][2] + 1.0f) * inverseProjY;
    this->mBaseCamera.mBottom = (proj->matrix[1][2] - 1.0f) * inverseProjY;
}

// ROUGH DRAFT

void StereoCamera::Initialize(){
    Result res;
    if(IsInitialized == false){
        cfg::CTR::Initialize();
        //res = cfg::CTR::detail::GetConfig(sCfgData,0x20,0x500005);
        //memcpy
    }
}

void StereoCamera::Finalize(){
}

StereoCamera::StereoCamera(){
    this->mDepthLevel = 0.0;
    this->mCameraInterval = 0.0;
}

StereoCamera::~StereoCamera(){
}

}
}
}