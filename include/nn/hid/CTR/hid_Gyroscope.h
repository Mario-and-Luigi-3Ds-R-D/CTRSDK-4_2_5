#pragma once

#include "nn/hid/CTR/hid_HidBase.h"
#include "nn/hid/CTR/hid_Accelerometer.h"
#include "nn/math/math_Vec3.h"
#include "nn/math/math_Matrix34.h"
#include "nn/util/util_NonCopyable.h"

namespace nn{
namespace hid{
namespace CTR{

enum ZeroDriftMode{
    GYROSCOPE_ZERODRIFT_LOOSE = 0,
    GYROSCOPE_ZERODRIFT_STANDARD = 1,
    GYROSCOPE_ZERODRIFT_TIGHT = 2,
    GYROSCOPE_ZERODRIFT_NUM = 3,
};

struct GyroscopeLowCalibrateAxisParam{
    short rpm0;
    short rpmPositive;
    short rpmNegative;
};

struct GyroscopeLowCalibrateParam{
    GyroscopeLowCalibrateAxisParam x;
    GyroscopeLowCalibrateAxisParam y;
    GyroscopeLowCalibrateAxisParam z;
};

struct GyroscopeStatus{
    nn::math::VEC3  speed;
    nn::math::VEC3  angle;
    Direction       direction;
    
    GyroscopeStatus(){}
};

class GyroscopeReader : private nn::util::NonCopyable<GyroscopeReader>{
protected:
    static const s32 GYROSCOPE_LOCAL_BUFFER_SIZE = 32;

    s32 mGyroscopeLocalBufferSize;
    GyroscopeStatus mGyroscopeStatusLocalBuffer[GYROSCOPE_LOCAL_BUFFER_SIZE];
    bool mIsFirstRead;
    s8 mZeroDriftMode;
    short rev;
    AccelerometerReader mDefaultAccelerometerReader;
    GyroscopeStatus mCurrentStatus;
    AccelerometerReader* mpAccelerometerReader;
    nn::math::VEC3 mSpeedOld;
    nn::math::VEC3 mSpeedVector;
    nn::math::VEC3 mSpeedScale;
    f32 mDirectionMagnification;
    f32 mPeriod;
    f32 mFreqDegree;
    f32 mFreqRadian;
    bool mEnableZeroPlay;
    bool mEnableZeroDrift;
    bool mEnableAccRevise;
    bool mEnableRotate;
    f32 mZeroPlayRadius;
    f32 mZeroDriftRadius;
    s32 mZeroDriftCount;
    f32 mZeroDriftPower;
    f32 mAccRevisePower;
    f32 mAccReviseRange;
    f32 mZeroPlayEffect;
    f32 mZeroDriftEffect;
    f32 mAccRevEffect;
    nn::math::VEC3 mCalibrationZero;
    f64 mCalibrationScale[3];
    nn::math::VEC3 mCountZero;
    s32 mCountIdx;
    s32 mCountT[3];
    f32 mDpsPitchMagnification;
    f32 mDpsYawMagnification;
    f32 mDpsRollMagnification;
    s32 rev2;
    Gyroscope& mGyroscope;
    s32 mIndexOfRead;
    s64 mTickOfRead;
    nn::math::MTX34 mRotateMtx;
public:
    GyroscopeReader(AccelerometerReader* pAccelerometerReader = NULL, Gyroscope& gyroscope = CTR::GetGyroscope());
    ~GyroscopeReader();
    void Read(GyroscopeStatus* pBufs, s32* pReadLen, s32 bufLen);
    bool ReadLatest(GyroscopeStatus* pBuf);

    // Enable / Disable
    void EnableZeroDrift(); 
    void EnableAccRevise();
    void EnableZeroPlay();
    //void EnableAccRevi(bool isEnable);
    void DisableAccRevise();
    void DisableZeroDrift();
    void DisableZeroPlay();

    // Calibration
    void CalculateDirection();
    void InitializeCalibrationData();

    // Reset
    void ResetZeroDriftMode();
    void ResetAxisRotationMatrix();
    f32 ReviseDirection_Acceleration(Direction& rev_dir, const nn::math::VEC3& acc);

    // Zero Modes
    void SetZeroPlayParam(f32& radius);
    void SetZeroDriftMode(const ZeroDriftMode& mode);
};

namespace{
    int sNumOfInstance;
    int rev;
    int sTickOfStart;
}

}
}
}