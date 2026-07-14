// Filename: hid_AccelerometerReader.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/hid/CTR/hid_AccelerometerReader.h>
#include <nn/hid/CTR/hid_IpcClient.h>
#include <nn/hidlow/CTR/hidlow_AccelerometerLifoRing.h>
#include <nn/hidlow/hidlow_Utils.h>
#include <nn/Assert.h>

#include <nn/types.h>
#include <string.h>

namespace nn{
namespace hid{
namespace CTR{
namespace detail{
    short CalculateAccelerationTightlyshort (short targetValue, short currentValue, short playRadius, short sensitivity);
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
    this->ResetOffset();
    this->ResetAxisRotationMatrix();
    this->DisableOffset();
    this->DisableAxisRotation();
    this->AccelerometerReader::Read(&tempStatus, &tempLen, 1);
}

void AccelerometerReader::ConvertToAcceleration(AccelerationFloat* pAcceleration, s32 bufLen, AccelerometerStatus* pSamplingData, s32 samplingLen){
    NN_TASSERT_(NULL != pAcceleration);
    NN_TASSERT_(NULL != pSamplingData);
    NN_TASSERT_(bufLen<=samplingLen);
    for(int i = 0; i < bufLen; i++){
        pAcceleration[i].x = pSamplingData[i].x * 0.001953125;
        pAcceleration[i].y = pSamplingData[i].y * 0.001953125;
        pAcceleration[i].z = pSamplingData[i].z * 0.001953125;
    }
}


void AccelerometerReader::Read(AccelerometerStatus* pBuf, s32* pReadLen, s32 bufLen){
    Accelerometer& accelerometer = this->mAccelerometer;
    ((nn::hidlow::CTR::AccelerometerLifoRing*)accelerometer.mResourcePtr)->ReadData(pBuf,bufLen,pReadLen,&this->mTickOfRead,&this->mIndexOfRead);
    typedef short (*CalcFn)(short, short, short, short);
    CalcFn calc = detail::CalculateAccelerationTightly;
        
    for(int i =*pReadLen - 1; i >= 0; --i){
        short newCalcAcl;
        
        newCalcAcl = calc(pBuf[i].x,this->mLatestCalculatedStatus.x,this->mPlay,this->mSensitivity);
        pBuf[i].x = newCalcAcl;
        this->mLatestCalculatedStatus.x = newCalcAcl;

        newCalcAcl = calc(pBuf[i].y,this->mLatestCalculatedStatus.y,this->mPlay,this->mSensitivity);
        pBuf[i].y = newCalcAcl;
        this->mLatestCalculatedStatus.y = newCalcAcl;

        newCalcAcl = calc(pBuf[i].z,this->mLatestCalculatedStatus.z,this->mPlay,this->mSensitivity);
        pBuf[i].z = newCalcAcl;
        this->mLatestCalculatedStatus.z = newCalcAcl;
        this->Transform(&pBuf[i]);
    }
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

NN_NOINLINE void AccelerometerReader::ResetAxisRotationMatrix(){
    this->SetAxisRotationMatrix(math::MTX34::Identity());
}

void AccelerometerReader::Transform(AccelerometerStatus* pAcclStatus){
    if(this->mEnableOffset != false){
        pAcclStatus->x = pAcclStatus->x - this->mOffsetAccStatus.x;
        pAcclStatus->y = pAcclStatus->y - this->mOffsetAccStatus.y;
        pAcclStatus->z = pAcclStatus->z - this->mOffsetAccStatus.z;
    }
    
    if ((this->mEnableRotate != false && !this->mRotateMtx.nn::math::MTX34::IsIdentity())) {
        nn::math::VEC3 vec(pAcclStatus->x,pAcclStatus->y,pAcclStatus->z);

        math::VEC3Transform(&vec,&this->mRotateMtx,&vec);
        pAcclStatus->x = vec.x;
        pAcclStatus->y = vec.y;
        pAcclStatus->z = vec.z;
    }
}

void AccelerometerReader::DisableAxisRotation(){
    this->mEnableRotate = 0;
}

void AccelerometerReader::DisableOffset(){
    this->mEnableOffset = 0;
}

void AccelerometerReader::SetAxisRotationMatrix(const nn::math::MTX34& mtx){
    memcpy(&this->mRotateMtx,&mtx,0x30);
}

AccelerometerReader::~AccelerometerReader(){
    detail::Ipc::DisableAccelerometer();
}

namespace detail{

short CalculateAccelerationTightly(short targetValue, short currentValue, short playRadius, short sensitivity){
    s32 diff = targetValue - currentValue;

    if (diff < -playRadius) {
        s32 delta = diff + playRadius;
        return (short)(currentValue + ((delta * sensitivity) >> 7));
    }

    if (diff <= playRadius) {
        return currentValue;
    }

    s32 delta = diff - playRadius;
    return (short)(currentValue + ((delta * sensitivity) >> 7));
}

}
}
}
}