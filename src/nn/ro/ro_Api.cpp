// Filename: ro_Api.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/ro/ro_Api.h>
#include <nn/drivers/drivers_Ro.h>

namespace nn{
namespace ro{
namespace{
    void* spStatic;
    void* spListNode;

    bool HasDebugInfo(nn::drivers::ro::RegistrationListHeader const& info){
        return info.IsDebugMode != 0;
    }
}

    // STUBS

void Finalize(){

}

/*void* RegisterList(void* pRr, size_t pSize){
    Result res = detail::DynamicLoader::RegisterList(PSEUDO_HANDLE_CURRENT_PROCESS,(uint)pRr,pSize);
    if(res.IsFailure() != 0){
        return 0;
    }
    spListNode = pRr;
    nn::drivers::ro::RegistrationListHeader const& hdr = *static_cast<nn::drivers::ro::RegistrationListHeader*>(pRr);
    bool result = HasDebugInfo(hdr);
    if(result){
        detail::EnableDebugNotification(true);
    }
    return pRr;
}*/

/*void Initialize(uint arg0, uint arg1) {
    nnRoDetailInitializeLinkException(0, (uint)nn::ro::detail::IsCodeAddress::CodeChecker::CodeChecker);
    nnRoDetailInitializeLinkException(arg0, arg1);
}*/



}
}