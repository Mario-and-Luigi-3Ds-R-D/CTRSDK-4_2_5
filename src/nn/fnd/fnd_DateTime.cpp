#include <nn/fnd/fnd_DateTime.h>
#include <nn/fnd/fnd_TimeSpan.h>
#include <nn/ptm/CTR/ptm_Rtc.h>
#include <nn/Assert.h>

namespace nn{
namespace fnd{

const DateTime DateTime::MIN_DATETIME = *(nn::fnd::DateTime*)0;

DateTime& DateTime::operator+=(const TimeSpan& rhs){
    this->mMilliSeconds += rhs.GetMilliSeconds(); 
    return *this; 
}

// Converts Dates -> Days using math, and things yeah.
//
// Very cool, ikr.

__asm s32 DateTime::DateToDays(s32 year, s32 month, s32 day){

    CMP             R1, #2
    SUB             R12, R2, #1
    LDR             R2, =0x51EB851F
    SUB             R0, R0, #0x7D0
    ADDLE           R3, R1, #9
    SUBGT           R3, R1, #3
    SUBLE           R0, R0, #1
    PUSH            {R4-R7}
    CMP             R0, #0
    MOV             R1, #1
    BGE             loc_128A28
    SMULL           R5, R1, R2, R0
    MOV             R4, #0xFFFFFFE7
    MOV             R5, R1,ASR#7
    SUB             R5, R5, R1,ASR#31
    MUL             R4, R5, R4
    ADDS            R4, R0, R4,LSL#4
    BEQ             loc_128A9C
    MOV             R6, R1,ASR#5
    MOV             R5, #0xFFFFFFE7
    SUB             R1, R6, R1,ASR#31
    MOV             R4, R0
    MUL             R1, R1, R5
    ADDS            R1, R0, R1,LSL#2
    BEQ             loc_128A28
    TST             R4, #3
    MOVNE           R1, #0
    BEQ             loc_128A9C

loc_128A28
    SMULL           R4, R2, R2, R0
    ADD             R3, R3, R3,LSL#4
    LDR             R4, =0x66666667
    ADD             R3, R3, R3,LSL#3
    ADD             R7, R3, #2
    MOV             R3, R2,ASR#5
    LDR             R6, =0x23AB1
    SUB             R3, R3, R2,ASR#31
    SMULL           R2, R4, R4, R7
    MOV             R5, #0xFFFFFFE7
    MUL             R2, R3, R6
    MUL             R3, R3, R5
    LDR             R5, =0x5B5
    ADD             R0, R0, R3,LSL#2
    MOV             R3, R2,ASR#31
    MUL             R0, R0, R5
    ADD             R5, R2, R3,LSR#30
    MOV             R2, R4,ASR#1
    MOV             R5, R5,ASR#2
    MOV             R3, R0,ASR#31
    SUB             R2, R2, R4,ASR#31
    ADD             R0, R0, R3,LSR#30
    ADD             R0, R5, R0,ASR#2
    ADD             R0, R0, R2
    ADD             R0, R0, R12
    ADD             R0, R0, R1
    POP             {R4-R7}
    ADD             R0, R0, #0x3B
    BX              LR

loc_128A9C
    MOV             R1, #1
    B               loc_128A28

}

// Gets The Paramaters for DateTime::DateTime
//
// Then does the DateTime math.

__asm DateTime DateTime::FromParamaters(s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second, s32 millisecond){

    PUSH            {R4-R9,LR}
    MOV             R7, R0
    MOV             R0, R1
    MOV             R1, R2
    MOV             R2, R3
    ADD             R3, SP, #0x1C
    LDR             R4, [SP,#0x28]

loc_12173C
    LDM             R3, {R5,R8}
    LDR             R6, [SP,#0x24]
    BL              __cpp(nn::fnd::DateTime::DateToDays)
    MOV             R9, R0
    LDR             R0, =0xEA60
    LDR             R1, =0x0036EE80
    MOV             R2, #0x3E8
    MOV             R12, R4,ASR#31
    SMULL           R3, R0, R8, R0
    SMLAL           R4, R12, R5, R1
    SMLAL           R3, R0, R6, R2
    LDR             R8, =0x5265C00
    ADDS            R1, R3, R4
    ADC             R0, R0, R12
    SMLAL           R1, R0, R9, R8
    STR             R0, [R7,#4]
    STR             R1, [R7]
    POP             {R4-R9,PC}

}

s32 DateTime::GetSecond(){
    return nn::fnd::DateTime::MilliSecondsOnDay(this->mMilliSeconds) % 1000 % 60;
}

s32 DateTime::GetMilliSecond(){
    return nn::fnd::DateTime::MilliSecondsOnDay(this->mMilliSeconds) % 1000;
}

DateTime DateTime::GetNow(){
    nn::fnd::DateTime now = nn::fnd::DateTime::MIN_DATETIME;
    now += nn::fnd::TimeSpan::FromMilliSeconds(nn::ptm::CTR::detail::GetSwcMilliSeconds());
    return now;
    return nn::fnd::DateTime::MIN_DATETIME;
}

}
}