// Filename: hidlow_Utils.cpp
//
// Project: Horizon CTRSDK

#include <math.h>
#include <nn/assert.h>
#include <nn/types.h>
#include <nn/Result.h>
#include <nn/hidlow/hidlow_Utils.h>

namespace nn{
namespace hidlow{

s32 sqrti(s32 x){
  if (0 >= x){
      return 0;
  }

  s32 tmp  = 1;
  s32 root = x;

  while (tmp < root){
    tmp  <<= 1;
    root >>= 1;
  }

  do{
    root = tmp;
    tmp = (x / tmp + tmp) >> 1;
  } while (tmp < root);

  return root;
}

short ClampStickCircle(short *pOutX,short *pOutY,s32 x,s32 y,s32 min,s32 max){
    s32 length2 = x * x + y * y;
    s32 seg;
    s32 scalar = 0;

    if (length2 <= min*min){
        *pOutX = *pOutY = 0;
        return scalar;
    }

    s32 length = sqrti(length2 << 7 *2);
    if (length2 >= max*max){
        scalar = max - min;
        seg = scalar << 7;
    }

    else{
        seg = length - (min << 7);
        scalar = (length >> 7) - min;
    }

    *pOutX = (s16)(x * seg / length);
    *pOutY = (s16)(y * seg / length);
    return scalar;
}

short ClampStickCross(short *pOutX,short *pOutY,s32 x,s32 y,s32 min,s32 max){
    if (x < 0){
        x =  -x <= min ? 0 : x + min;
    }
    else{
        x =  x <= min ? 0 : x - min;
    }

    if (y < 0){
        y =  -y <= min ? 0 : y + min;
    }
    else{
        y =  y <= min ? 0 : y - min;
    }

	s32 length2 = x * x + y * y;
	s32 scalar = max - min;

	if (length2 >= (max-min)*(max-min)){
	    s32 length = sqrti(length2 << 7 *2);

        s32 seg = scalar << 7;

	    x = (s16)(x * seg / length);
	    y = (s16)(y * seg / length);
    }

    *pOutX = (s16)x;
    *pOutY = (s16)y;
    return scalar;
}

f32 ClampAxisFloat(s32 x, s32 min, s32 max){
    if (x <= min){
       return 0.f;
    }
    else if (x >= max ){
        return 1.f;
    }
    else{
        return (f32)(x - min) / (f32)(max - min);
    }
}

f32 ClampStickCrossFloat(f32 *pOutX,f32 *pOutY,s32 x,s32 y,s32 min,s32 max){
    f32 length;

    if (x < 0){
        *pOutX = - ClampAxisFloat(-x, min, max);
    }
    else{
        *pOutX = ClampAxisFloat(x, min, max);
    }

    if (y < 0){
        *pOutY = - ClampAxisFloat(-y, min, max);
    }
    else{
        *pOutY = ClampAxisFloat(y, min, max);
    }

    length = (*pOutX) * (*pOutX) + (*pOutY) * (*pOutY);
    length = sqrtf(length);
    if (length > 1.f) {
        (*pOutX) /= length ;
        (*pOutY) /= length ;
        length = 1.f;
    }
    return length;
}

void ClampStickMinimum(s16 *pOutX,s16 *pOutY,s32 x,s32 y,s32 min,s32 max){
    
}


void GatherStartAndSelect(hid::CTR::PadStatus* pButton){
    GatherStartAndSelect(&pButton->hold,&pButton->trigger,&pButton->release);
}

void GatherStartAndSelect(hid::CTR::ExtraPadStatus* pButton){
    GatherStartAndSelect(&pButton->hold,&pButton->trigger,&pButton->release);
}

void GatherStartAndSelect(bit32 *hold,bit32 *trigger,bit32 *release){
    uint adjust;
    bit32 current;

    adjust = *trigger;
    if((((~adjust & 0xC) == 0) || (((adjust & 4) != 0 && ((*hold & 8) == 0)))) || (((adjust & 8) != 0 && ((*hold & 4) == 0)))){
        current = adjust | 8;
    } 
    else{
        current = adjust & 0xfffffff7;
    }
    *trigger = current;
    adjust = *release;
    if((((~adjust & 0xC) == 0) || (((adjust & 4) != 0 && ((*hold & 8) == 0)))) || (((adjust & 8) != 0 && ((*hold & 4) == 0)))){
        current = adjust | 8;
    } 
    else{
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