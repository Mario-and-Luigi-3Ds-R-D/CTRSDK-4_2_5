#include <nn/hid/CTR/hid_ExtraPad.h>
#include <nn/ir/CTR/cepd_Api.h>

namespace nn{
namespace hid{
namespace CTR{

bool ExtraPad::IsSampling(){
    ir::CTR::CepdStatus cStatus = ir::CTR::CepdGetStatus();
    return cStatus == ir::CTR::CEPD_STATUS_SAMPLING;
}

}
}
}