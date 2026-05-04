#include <nn/ucld/CTR/ucld_StereoCamera.h>

namespace nn{
namespace ulcd{
namespace CTR{

void GetLookPose(const nn::math::MTX34 *view,nn::math::VEC3 *pos,Direction *dir){

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
    // TODO
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

void StereoCamera::Initialize(){

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