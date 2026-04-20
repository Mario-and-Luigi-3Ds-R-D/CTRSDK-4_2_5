#include <nn/hid/CTR/hid_Accelerometer.h>
#include <nn/hid/CTR/detail/Ipc/hid_Ipc.h>

namespace nn{
namespace hid{
namespace CTR{

AccelerometerReader::AccelerometerReader(Accelerometer *accelerometer){
    AccelerometerStatus tempStatus;
    s32 tempLen;

    this->mAccelerometer = accelerometer;
    this->mPlay = 0;
    this->mSensitivity = 0x80;
    this->mEnableOffset = false;
    this->mEnableRotate = false;
    this->mIndexOfRead = -1;
    this->mTickOfRead = -1;
    CTR::detail::Ipc::EnableAccelerometer();
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

#ifdef NONMATCHING
#endif
void AccelerometerReader::ConvertToAcceleration(AccelerationFloat* pAcceleration, s32 bufLen, AccelerometerStatus* pSamplingData, s32 samplingLen){
  s16 *p_y; // r12
  s16 *p_z; // r0
  f32 *v7; // r4
  f32 *v8; // r5
  int x; // t1
  int v10; // t1
  int v11; // t1

  if ( bufLen > 0 )
  {
    p_y = &pSamplingData->y;
    p_z = &pSamplingData->z;
    v7 = &pAcceleration->y;
    v8 = &pAcceleration->z;
    do
    {
      x = pSamplingData->x;
      ++pSamplingData;
      --bufLen;
      pAcceleration->x = (float)x * 0.0019531;
      v10 = *p_y;
      p_y += 3;
      ++pAcceleration;
      *v7 = (float)v10 * 0.0019531;
      v11 = *p_z;
      p_z += 3;
      v7 += 3;
      *v8 = (float)v11 * 0.0019531;
      v8 += 3;
    }
    while ( !bufLen );
  }
}

// Reads the current Accelerometer status, uses MTX44 to do so.
//
// AcceleroMeterReader::ct -> Here.
//
// Legit nightmare, so I ASM'd it, just use AcceleroMeter::ct as a method to get it.

/*__asm void Read(AccelerometerStatus* status, s32* pReadLen, s32 bufLen){
    PUSH            {R4-R8,LR}
    MOV             R4, R2
    MOV             R8, R1
    MOV             R2, R3
    VPUSH           {D8}
    SUB             SP, SP, #0x10
    MOV             R5, R0
    ADD             R3, R0, #0x4C
    ADD             R1, R0, #0x50
    LDR             R0, [R0]
    STMEA           SP, {R1,R3}
    MOV             R3, R4
    MOV             R1, R8
    LDR             R0, [R0,#4]
    BL              __cpp(nn::hidlow::CTR::AccelerometerLifoRing::ReadData)
    LDR             R0, [R4]
    LDR             R7, =__cpp(nn::hid::CTR::detail::CalculateAccelerationTightly)
    SUB             R6, R0, #1
    CMP             R6, #0
    VLDRGE          S16, =0.0
    BLT             loc_10E6A8

loc_10E4E8
    ADD             R0, R6, R6,LSL#1
    LDRSH           R3, [R5,#6]
    ADD             R4, R8, R0,LSL#1
    LDRSH           R2, [R5,#4]
    LDRSH           R0, [R4]
    LDRSH           R1, [R5,#8]
    BLX             R7
    STRH            R0, [R4]
    STRH            R0, [R5,#8]
    LDRSH           R3, [R5,#6]
    LDRSH           R2, [R5,#4]
    LDRSH           R1, [R5,#0xA]
    LDRSH           R0, [R4,#2]
    BLX             R7
    STRH            R0, [R4,#2]
    STRH            R0, [R5,#0xA]
    LDRSH           R3, [R5,#6]
    LDRSH           R2, [R5,#4]
    LDRSH           R1, [R5,#0xC]
    LDRSH           R0, [R4,#4]

loc_10E538
    BLX             R7
    STRH            R0, [R4,#4]
    STRH            R0, [R5,#0xC]
    LDRB            R0, [R5,#0x48]
    CMP             R0, #0
    BEQ             loc_10E580
    LDRH            R1, [R4]
    LDRH            R0, [R5,#0xE]
    SUB             R0, R1, R0
    STRH            R0, [R4]
    LDRH            R1, [R4,#2]
    LDRH            R0, [R5,#0x10]
    SUB             R0, R1, R0
    STRH            R0, [R4,#2]
    LDRH            R1, [R4,#4]
    LDRH            R0, [R5,#0x12]
    SUB             R0, R1, R0
    STRH            R0, [R4,#4]

loc_10E580
    LDRB            R0, [R5,#0x49]
    CMP             R0, #0
    BEQ             loc_10E6A0
    VLDR            S0, [R5,#0x18]
    VMOV            R0, S0
    CMP             R0, #0x3F800000
    VLDREQ          S0, [R5,#0x1C]
    VCMPEQ.F32      S0, S16
    VMRSEQ          APSR_nzcv, FPSCR
    BNE             loc_10E630
    VLDR            S0, [R5,#0x20]
    VCMP.F32        S0, S16
    VMRS            APSR_nzcv, FPSCR
    VLDREQ          S0, [R5,#0x24]
    VCMPEQ.F32      S0, S16
    VMRSEQ          APSR_nzcv, FPSCR
    VLDREQ          S0, [R5,#0x28]
    VCMPEQ.F32      S0, S16
    VMRSEQ          APSR_nzcv, FPSCR
    BNE             loc_10E630
    VLDR            S0, [R5,#0x2C]
    VMOV            R0, S0
    CMP             R0, #0x3F800000
    VLDREQ          S0, [R5,#0x30]
    VCMPEQ.F32      S0, S16
    VMRSEQ          APSR_nzcv, FPSCR
    BNE             loc_10E630
    VLDR            S0, [R5,#0x34]
    VCMP.F32        S0, S16
    VMRS            APSR_nzcv, FPSCR
    VLDREQ          S0, [R5,#0x38]
    VCMPEQ.F32      S0, S16
    VMRSEQ          APSR_nzcv, FPSCR
    VLDREQ          S0, [R5,#0x3C]
    VCMPEQ.F32      S0, S16
    VMRSEQ          APSR_nzcv, FPSCR
    BNE             loc_10E630
    VLDR            S0, [R5,#0x40]
    VMOV            R0, S0
    CMP             R0, #0x3F800000
    VLDREQ          S0, [R5,#0x44]
    VCMPEQ.F32      S0, S16
    VMRSEQ          APSR_nzcv, FPSCR
    BEQ             loc_10E6A0

loc_10E630
    LDRSH           R0, [R4]
    LDRSH           R2, [R4,#4]
    LDRSH           R1, [R4,#2]
    VMOV            S2, R0
    VMOV            S1, R2
    VMOV            S0, R1
    ADD             R3, SP, #0x4
    MOV             R2, SP
    ADD             R1, R5, #0x18
    VCVT.F32.S32    S2, S2
    VCVT.F32.S32    S1, S1
    VCVT.F32.S32    S0, S0
    MOV             R0, R2
    VSTR            S2, [SP,#0x0]
    VSTM            R3, {S0-S1}
    BL              __cpp(nn::math::ARMv6::VEC3TransformAsm)
    VLDR            S0, [SP,#0x0]
    VCVT.S32.F32    S0, S0
    VMOV            R0, S0
    STRH            R0, [R4]
    VLDR            S0, [SP,#0x4]
    VCVT.S32.F32    S0, S0
    VMOV            R0, S0
    STRH            R0, [R4,#2]
    VLDR            S0, [SP,#0x8]
    VCVT.S32.F32    S0, S0
    VMOV            R0, S0
    STRH            R0, [R4,#4]

loc_10E6A0
    SUBS            R6, R6, #1
    BPL             loc_10E4E8

loc_10E6A8
    ADD             SP, SP, #0x10
    VPOP            {D8}
    POP             {R4-R8,PC}
}*/

bool AccelerometerReader::ReadLatest(AccelerometerStatus* status){
    // TODO
}

void AccelerometerReader::ResetAxisRotationMatrix(){
    // TODO
}

void AccelerometerReader::Transform(AccelerometerStatus* status){
    // TODO
}

AccelerometerReader::~AccelerometerReader(){
    // CTR::detail::Ipc::DisableAcceleroMeter();
}


}
}
}