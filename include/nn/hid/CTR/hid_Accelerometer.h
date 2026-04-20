#pragma once

#include "nn/hid/CTR/hid_HidBase.h"
#include "nn/math/math_Matrix34.h"

namespace nn{
namespace hid{
namespace CTR{

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

class AccelerometerReader{
protected:
    Accelerometer* mAccelerometer;
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

    AccelerometerReader(Accelerometer *accelerometer);
    void ConvertToAcceleration(AccelerationFloat* pAcceleration, s32 bufLen, AccelerometerStatus* pSamplingData, s32 samplingLen);
    void Read(AccelerometerStatus* status, s32* pReadLen, s32 bufLen);
    bool ReadLatest(AccelerometerStatus* status);
    void ResetAxisRotationMatrix();
    void Transform(AccelerometerStatus* status);
    ~AccelerometerReader();

};

}
}
}