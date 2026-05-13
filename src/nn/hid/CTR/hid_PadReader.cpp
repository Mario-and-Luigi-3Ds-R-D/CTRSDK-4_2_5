#include <nn/hid/CTR/hid_Pad.h>

namespace nn{
namespace hid{
namespace CTR{
#ifdef NONMATCHING
#endif
PadReader::PadReader(Pad& pad) : mPad(pad) {
    this->mIndexOfRead = -1;
    // TODO
}

bool PadReader::ReadLatest(PadStatus* status){
  // TODO
}

f32 PadReader::NormalizeStick(short x, short y){
    return this->mStickClamper.NormalizeStick(x,y);
}

}
}
}