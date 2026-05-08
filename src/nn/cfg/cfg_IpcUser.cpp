#include <nn/cfg/CTR/cfg_IpcUser.h>

namespace nn {
namespace cfg {
namespace CTR {
namespace detail {
namespace IpcUser{
namespace{
    nn::Handle sSession = 0;
}
Result GetConfig (void* pData, size_t size, bit32 key){
    // TODO
}

Result GetRegion (CfgRegionCode* regionCode){
    //
}

Result GetTransferableId (bit32, bit64*){
    // TODO
}

}
}
}
}
}