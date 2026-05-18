// Filename: hid_Accelerometer.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/hid/CTR/hid_Accelerometer.h>
#include <nn/hid/CTR/detail/Ipc/hid_Ipc.h>
#include <nn/hidlow/CTR/hidlow_AccelerometerLifoRing.h>
#include <nn/hidlow/hidlow_Api.h>
#include <nn/dbg/dbg_Break.h>

#include <nn/types.h>
#include <string.h>

namespace nn{
namespace hid{
namespace CTR{

#ifdef NONMATCHING
#endif

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
    #ifdef NN_DEBUG
        if(NULL != pAcceleration){
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"hid_Accelerometer.cpp",46,"%s","NULL != pAcceleration");
        }
        if(NULL != pSamplingData){
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"hid_Accelerometer.cpp",49,"%s","NULL != pSamplingData");
        }
        if((-1 < samplingLen) && (bufLen<=samplingLen)){
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"hid_Accelerometer.cpp",52,"%s","bufLen<=samplingLen");
        }
    #endif
    for(int i = 0; i < bufLen; i+= 1){
        pAcceleration[i].x = pSamplingData[i].x * 0.001953125;
        pAcceleration[i].y = pSamplingData[i].y * 0.001953125;
        pAcceleration[i].z = pSamplingData[i].z * 0.001953125;
    }
}

#ifdef NONMATCHING
#endif

void AccelerometerReader::Read(AccelerometerStatus* pBuf, s32* pReadLen, s32 bufLen){
    Accelerometer& accelerometer = this->mAccelerometer;
    ((nn::hidlow::CTR::AccelerometerLifoRing*)accelerometer.mResourcePtr)->ReadData(pBuf,1,pReadLen,&this->mTickOfRead,&this->mIndexOfRead);
    int readLen = *pReadLen;
    while(readLen += -1, -1 < readLen){
        short newCalcAcl;

        newCalcAcl = detail::CalculateAccelerationTightly(pBuf[readLen].x,this->mLatestCalculatedStatus.x,this->mPlay,this->mSensitivity);
        pBuf[readLen].x = newCalcAcl;
        this->mLatestCalculatedStatus.x = newCalcAcl;

        newCalcAcl = detail::CalculateAccelerationTightly(pBuf[readLen].y,this->mLatestCalculatedStatus.y,this->mPlay,this->mSensitivity);
        pBuf[readLen].y = newCalcAcl;
        this->mLatestCalculatedStatus.y = newCalcAcl;

        newCalcAcl = detail::CalculateAccelerationTightly(pBuf[readLen].z,this->mLatestCalculatedStatus.z,this->mPlay,this->mSensitivity);
        pBuf[readLen].z = newCalcAcl;
        this->mLatestCalculatedStatus.z = newCalcAcl;

        this->Transform(pBuf + readLen);
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

        math::ARMv6::VEC3Transform(&vec,&this->mRotateMtx,&vec);
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
__asm short CalculateAccelerationTightlyshort (short targetValue, short currentValue, short playRadius, short sensitivity){
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
}
}
}