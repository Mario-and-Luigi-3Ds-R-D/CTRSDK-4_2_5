// Filename: snd_Api.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/snd/CTR/MPCore/snd_Api.h>
#include <nn/snd/CTR/MPCore/snd_System.h>
#include <nn/srv/srv_Api.h>

namespace nn{
namespace snd{
namespace CTR{

Result Initialize(){
    Result res;
    if(sInitialized == false){
        res.mResult = srv::Initialize().IsFailure();
//        if(res.mResult )
    }
}



void Sleep(){
    if((sInitialized & ~ sIsSleep) != 0){
        sSleepEvent.Initialize(true);
        sIsSleepPrepare = true;
        internal::sDspsnd.Finalize(true);
        sIsSleep = true;
    }
}



}
}
}