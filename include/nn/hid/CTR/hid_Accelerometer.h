#pragma once

#include "nn/hid/hid_Api.h"
#include "nn/util/util_NonCopyable.h"
#include "nn/math/math_Matrix34.h"

namespace nn{
namespace hid{
namespace CTR{
namespace detail{
    short CalculateAccelerationTightly(short targetValue, short currentValue, short playRadius, short sensitivity);
}

const s16  MAX_OF_ACCELEROMETER_VALUE = 930;
const s16  ACCELEROMETER_VALUE_PER_1G = 512;
const f32  ACCELERATION_SCALE_PER_1G = 1.f / ACCELEROMETER_VALUE_PER_1G;
const s16  MAX_OF_ACCELEROMETER_PLAY = MAX_OF_ACCELEROMETER_VALUE * 2;
const s16  ACCELEROMETER_SENSITIVITY_SCALE_SHIFT = 7;
const s16  MAX_OF_ACCELEROMETER_SENSITIVITY = 128; // 1 << ACCELEROMETER_SENSITIVITY_SCALE_SHIFT

struct AccelerometerStatus{
    short x;
    short y;
    short z;
};

struct AccelerationFloat{
    f32 x;
    f32 y;
    f32 z;
};

class AccelerometerReader : private nn::util::NonCopyable<AccelerometerReader>{
protected:
    Accelerometer& mAccelerometer;
    short mPlay;
    short mSensitivity;
    AccelerometerStatus mLatestCalculatedStatus;
    AccelerometerStatus mOffsetAccStatus;
    s32 rev;
    nn::math::MTX34 mRotateMtx;
    bool mEnableOffset;
    bool mEnableRotate;
    short rev2;
    s32 mIndexOfRead;
    s64 mTickOfRead;
public:

    AccelerometerReader(Accelerometer& accelerometer = CTR::GetAccelerometer());
    ~AccelerometerReader();
    void ConvertToAcceleration(AccelerationFloat* pAcceleration, s32 bufLen, AccelerometerStatus* pSamplingData, s32 samplingLen = -1);
    void Read(AccelerometerStatus* status, s32* pReadLen, s32 bufLen);
    bool ReadLatest(AccelerometerStatus* status);
    void ResetAxisRotationMatrix();
private:
    void Transform(AccelerometerStatus* status);

};

}
}
}