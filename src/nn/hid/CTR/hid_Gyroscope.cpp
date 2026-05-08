#include <nn/hid/CTR/hid_Gyroscope.h>

namespace nn{
namespace hid{
namespace CTR{

// Gyroscope

Gyroscope::~Gyroscope(){
    this->Close();
    return;
}

// GyroscopeReader

GyroscopeReader::GyroscopeReader(AccelerometerReader* pAccelerometerReader,Gyroscope& gyroscope) : mGyroscope(gyroscope){
    // TODO 
}

GyroscopeReader::~GyroscopeReader(){
    // TODO
}

void GyroscopeReader::EnableZeroDrift(){
    this->mEnableZeroDrift = true;
}

void GyroscopeReader::EnableAccRevise(){
    this->mEnableAccRevise = true;
}

void GyroscopeReader::EnableZeroPlay(){
    this->mEnableZeroPlay = true;
}

void GyroscopeReader::DisableAccRevise(){
    this->mEnableAccRevise = false;
}

void GyroscopeReader::DisableZeroDrift(){
    this->mEnableZeroDrift = false;
}

void GyroscopeReader::DisableZeroPlay(){
    this->mEnableZeroPlay = false;
}

void GyroscopeReader::CalculateDirection(){
    /*float xX = this->mCurrentStatus.direction.x.x;
    float xY = this->mCurrentStatus.direction.x.y;
    float xZ = this->mCurrentStatus.direction.x.z;
    float yX = this->mCurrentStatus.direction.y.x;
    float yY = this->mCurrentStatus.direction.y.y;
    float yZ = this->mCurrentStatus.direction.y.z;
    float zX = this->mCurrentStatus.direction.y.x;
    float zY = this->mCurrentStatus.direction.y.y;
    float zZ = this->mCurrentStatus.direction.y.z;*/
}

void GyroscopeReader::InitializeCalibrationData(){
    // TODO
}

void GyroscopeReader::ResetZeroDriftMode(){
    this->mZeroDriftMode = GYROSCOPE_ZERODRIFT_STANDARD;
    this->mZeroDriftRadius = 0.005;
    this->mZeroDriftCount = 100;
    this->mZeroDriftPower = 0.0199;
}

void GyroscopeReader::ResetAxisRotationMatrix(){
    // TODO
}

f32 GyroscopeReader::ReviseDirection_Acceleration(Direction& rev_dir, const nn::math::VEC3& acc){
    // TODO
}

void GyroscopeReader::SetZeroPlayParam(f32& radius){
    this->mZeroPlayRadius = 0.005;
}

void GyroscopeReader::SetZeroDriftMode(const ZeroDriftMode& mode){
    // TODO
}


}
}
}