#include <nn/hid/CTR/hid_Pad.h>
#include <nn/applet/applet_All.h>

namespace nn{
namespace hid{
namespace CTR{
#ifdef NONMATCHING
#endif
PadReader::PadReader(Pad* pad){
    this->mPad = pad;
    this->mIndexOfRead = -1;
    //AnalogStickClamper::AnalogStickClamper();
    this->mIsReadLatestFirst = true;
}

bool PadReader::ReadLatest(PadStatus* status){
  // TODO
}

f32 PadReader::NormalizeStick(short x, short y){
    this->mStickClamper.NormalizeStick(x,y);
}

}
}
}