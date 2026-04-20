#include <nn/ucld/CTR/ucld_StereoCamera.h>

namespace nn{
namespace ulcd{
namespace CTR{
f32 StereoCamera::CalculateMaxtrices(nn::math::MTX44 *projL,nn::math::MTX34 *viewL,nn::math::MTX44 *projR,nn::math::MTX34 *viewR, nn::math::MTX44 *projOriginal,nn::math::MTX34 *viewOriginal,f32 depthLevel,f32 factor,bool realSwitch){

}

f32 StereoCamera::GetParallex(){

}

void StereoCamera::Initialize(){

}

StereoCamera::StereoCamera(){
    this->mDepthLevel = 0.0;
    this->mCameraInterval = 0.0;
}

}
}
}