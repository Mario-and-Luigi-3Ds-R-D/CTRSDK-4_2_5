#include <nn/snd/CTR/MPCore/snd_System.h>

namespace nn {
namespace snd {
namespace CTR {

bool AppendChannelNextBuffer(u8* ch_no, WaveBuffer* pWaveBuffer, s32 index){

}

bool AssignPCM(u8* ch_no, WaveBuffer* pWaveBuffer, DspsndAudioInfo i){

}

bool EnableAuxBus(AuxBusId busId, bool flag){
    nn::snd::CTR::DspsndMasterDirect *pMasterDirectAddr;
    bool newFlag;
    AuxBusId id;

    id = busId;
    newFlag = flag;
//    if(!dsp::CTR::IsComponentLoaded()){
//        return 0;
 //   }
}
}
}
}