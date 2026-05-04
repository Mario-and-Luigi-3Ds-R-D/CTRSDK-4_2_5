#include <nn/hidlow/hidlow_All.h>

namespace nn{
namespace hidlow{

short ClampStickCircle(short *pOutX,short *pOutY,s32 x,s32 y,s32 min,s32 max){

}

short ClampStickCross(short *pOutX,short *pOutY,s32 x,s32 y,s32 min,s32 max){

}

f32 ClampStickCrossFloat(f32 *pOutX,f32 *pOutY,s32 x,s32 y,s32 min,s32 max){

}

void ClampStickMinimum(s16 *pOutX,s16 *pOutY,s32 x,s32 y,s32 min,s32 max){

}


void nn::hidlow::GatherStartAndSelect(hid::CTR::PadStatus* pButton){
    GatherStartAndSelect(&pButton->hold,&pButton->trigger,&pButton->release);
}

void GatherStartAndSelect(bit32 *hold,bit32 *trigger,bit32 *release){
    uint adjust;
    bit32 current;

    adjust = *trigger;
    if((((~adjust & 0xC) == 0) || (((adjust & 4) != 0 && ((*hold & 8) == 0)))) || (((adjust & 8) != 0 && ((*hold & 4) == 0)))){
        current = adjust | 8;
    } else{
        current = adjust & 0xfffffff7;
    }
    *trigger = current;
    adjust = *release;
    // This shit looks like a fuckin concastrophe bruh
    if((((~adjust & 0xC) == 0) || (((adjust & 4) != 0 && ((*hold & 8) == 0)))) || (((adjust & 8) != 0 && ((*hold & 4) == 0)))){
        current = adjust | 8;
    } else{
        current = adjust & 0xfffffff7;
    }
    *release = current;
    if((*hold & 4) != 0){
        *hold = *hold & 0xfffffffb | 8;
    }
    *trigger = *trigger & 0xfffffffb;
    *release = *release & 0xfffffffb;
    return;
}

}
}