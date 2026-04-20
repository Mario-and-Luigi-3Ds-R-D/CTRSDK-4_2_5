#pragma once

#include "nn/types.h"
#include "nn/ro/ro_RegistrationList.h"
#include "nn/ro/ro_Module.h"
#include "nn/ro/ro_Types.h"

namespace nn{
namespace ro{

    void Initialize(uint,uint);
    void Finalize();
    nn::ro::RegistrationList* RegisterList(void* pRr, size_t pSize);
    nn::ro::Module* FindModule(const char* pModule);
    uint GetAddress(const char* pAddress);
    void GetSizeInfo(nn::ro::SizeInfo* pSizeInfo,void* pBuffer);
    nn::ro::Module* LoadModule(nn::ro::Module* pOffset, int, void*, uint, bool, nn::ro::FixLevel pLevel, const nn::ro::RegistrationList*);

namespace detail{
    const char PORT_NAME_RELOCATEABLE_OBJECT[] = "ldr:ro";
    const s32 ENTRY_NOT_FOUND = -1;

    uptr GetOriginalAddress(const void* p);
    void UpdateRegistrationListNode(nn::ro::RegistrationList* p);
    s32 FindRegistrationListEntry(const nn::ro::RegistrationList** superP, const void* p);
    void* GetRoot();

    __weak bool IsCodeAddress(uptr addr);
}
}

namespace{
    void* sStatic;
}

}

extern "C" {
    void nnRoDetailInitializeLinkException(uint,uint);
    void nnRoInitializeImpl();
}