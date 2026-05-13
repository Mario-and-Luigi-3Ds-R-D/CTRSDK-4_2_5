#include <nn/hid/CTR/hid_Accelerometer.h>
#include <nn/hid/CTR/detail/Ipc/hid_Ipc.h>
#include <nn/hidlow/CTR/hidlow_AccelerometerLifoRing.h>
#include <nn/hidlow/hidlow_Api.h>

namespace nn{
namespace hid{
namespace CTR{
namespace detail{
__asm short CalculateAccelerationTightly(short targetValue, short currentValue, short playRadius, short sensitivity){
    MOV             R12, R0
    MOV             R0, R1
    PUSH            {R4}
    RSB             R4, R2, #0
    SUB             R1, R12, R0
    CMP             R1, R4
    BGE             loc_11979C
    ADD             R1, R1, R2
    MUL             R1, R1, R3
    ADD             R0, R0, R1,ASR#7
    SXTH            R0, R0

loc_119794
    POP             {R4}
    BX              LR

loc_11979C
    CMP             R1, R2
    BLE             loc_119794
    SUB             R1, R1, R2
    POP             {R4}
    MUL             R1, R1, R3
    ADD             R0, R0, R1,ASR#7
    SXTH            R0, R0
    BX              LR
}
}

AccelerometerReader::AccelerometerReader(Accelerometer& accelerometer) : mAccelerometer(accelerometer){
    AccelerometerStatus tempStatus;
    s32 tempLen;

    this->mPlay = 0;
    this->mSensitivity = 0x80;
    this->mEnableOffset = false;
    this->mEnableRotate = false;
    this->mIndexOfRead = -1;
    this->mTickOfRead = -1LL;
    detail::Ipc::EnableAccelerometer();
    this->mLatestCalculatedStatus.x = 0;
    this->mLatestCalculatedStatus.y = 0;
    this->mLatestCalculatedStatus.z = 0;
    this->mOffsetAccStatus.x = 0;
    this->mOffsetAccStatus.y = 0;
    this->mOffsetAccStatus.z = 0;
    this->ResetAxisRotationMatrix();
    this->mEnableOffset = false;
    this->mEnableRotate = false;
    this->Read(&tempStatus, &tempLen, 1);
}

void AccelerometerReader::ConvertToAcceleration(AccelerationFloat* pAcceleration, s32 bufLen, AccelerometerStatus* pSamplingData, s32 samplingLen){
    // TODO
}

void AccelerometerReader::Read(AccelerometerStatus* pBuf, s32* pReadLen, s32 bufLen){
    // TODO
}

bool AccelerometerReader::ReadLatest(AccelerometerStatus* pBuf){
    s32 readLen;
    s64 tick = -1LL;
    s32 index = -1;
    Accelerometer* accelerometer = &(Accelerometer&)this->mAccelerometer;

    ((nn::hidlow::CTR::AccelerometerLifoRing*)accelerometer->mResourcePtr)->ReadData(pBuf,1,&readLen,&tick,&index);

    if (readLen <= 0) {
        return false;
    }
    short newCalcAcl;
    newCalcAcl = detail::CalculateAccelerationTightly(pBuf->x,this->mLatestCalculatedStatus.x,this->mPlay,this->mSensitivity);
    pBuf->x = newCalcAcl;
    this->mLatestCalculatedStatus.x = newCalcAcl;

    newCalcAcl = detail::CalculateAccelerationTightly(pBuf->y,this->mLatestCalculatedStatus.y,this->mPlay,this->mSensitivity);
    pBuf->y = newCalcAcl;
    this->mLatestCalculatedStatus.y = newCalcAcl;

    newCalcAcl = detail::CalculateAccelerationTightly(pBuf->z,this->mLatestCalculatedStatus.z,this->mPlay,this->mSensitivity);
    pBuf->z = newCalcAcl;
    this->mLatestCalculatedStatus.z = newCalcAcl;

    this->Transform(pBuf);
    return true;
}

void AccelerometerReader::ResetAxisRotationMatrix(){
    // TODO
}

void AccelerometerReader::Transform(AccelerometerStatus* status){
    // TODO
}

void AccelerometerReader::DisableAxisRotation(){
    this->mEnableRotate = 0;
}

AccelerometerReader::~AccelerometerReader(){
    detail::Ipc::DisableAccelerometer();
}


}
}
}