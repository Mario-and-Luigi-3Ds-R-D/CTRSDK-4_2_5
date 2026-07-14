// Filename: hid_GyroscopeReader.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/hid/CTR/hid_GyroscopeReader.h>
#include <nn/hid/CTR/hid_IpcClient.h>
#include <nn/module.h>

namespace nn{
namespace hid{
namespace CTR{
namespace{
    int sNumOfInstance;
    int rev;
    int sTickOfStart;

    NN_MAKE_MODULE_SDK(sDetectableString, "Gyroscope");
}

GyroscopeReader::GyroscopeReader(AccelerometerReader* pAccelerometerReader,Gyroscope& gyroscope) :   
    mIsFirstRead(true),
    mDefaultAccelerometerReader(),
    mGyroscope(gyroscope),
    mIndexOfRead(-1),
    mTickOfRead(-1){
    NN_REFER_MODULE(sDetectableString);
    detail::Ipc::EnableGyroscopeLow();
    if (pAccelerometerReader)
        mpAccelerometerReader = pAccelerometerReader;
    else
        mpAccelerometerReader = &mDefaultAccelerometerReader;
    // TODO

}

GyroscopeReader::~GyroscopeReader(){
    detail::Ipc::DisableGyroscopeLow();
    sNumOfInstance--;
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
    math::MTX34::Identity();
    //this->SetAxis
    this->mpAccelerometerReader->ResetAxisRotationMatrix();
}

f32 GyroscopeReader::ReviseDirection_Acceleration(Direction& rev_dir, const nn::math::VEC3& acc){
    
}

void GyroscopeReader::SetZeroPlayParam(f32& radius){
    this->mZeroPlayRadius = 0.005;
}

void GyroscopeReader::SetZeroDriftMode(const ZeroDriftMode& mode){
    this->mZeroDriftMode = mode;
}


}
}
}