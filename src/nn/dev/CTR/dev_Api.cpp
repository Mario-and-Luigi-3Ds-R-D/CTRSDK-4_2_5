#include <nn/dev/CTR/dev_Api.h>
#include <nn/dev/CTR/dev_Dev.h>
#include <nn/util/util_Result.h>
#include <nn/srv/srv_API.h>
#include <string.h>
/*
namespace nn{
namespace dev{
namespace CTR{
namespace{
    bool sInitialized;
}
namespace{
    Handle sDev9Handle;

    size_t CalcSize(s32 numSectors, SectorSize sectorSize){
        size_t SIZE_TABLE[9];
        //memcpy(SIZE_TABLE, SECTOR_SIZE_TABLE, sizeof(SECTOR_SIZE_TABLE));
        return SIZE_TABLE[sectorSize] * numSectors;
    }
}
void Initialize(){
    Result res;
    if(!sInitialized){
        srv::Initialize();
        NN_UTIL_PANIC_IF_FAILED(nn::srv::GetServiceHandle(&sDev9Handle, nn::pxi::CTR::PORT_NAME_DEV9));
        sInitialized = true;
    }
}

void Finalize(){
    if(sInitialized){
        NN_UTIL_PANIC_IF_FAILED(nn::svc::CloseHandle(sDev9Handle));
        sInitialized = false;
    }
}

Result ReadHostIO(void* pData, s32 numSectors, SectorSize sectorSize, const u8* pCommand){
    NN_TASSERTMSG_(sInitialized, "Not initialized");
    u32 size = CalcSize(numSectors,sectorSize);
    Dev dev(sDev9Handle);
    return dev.ReadHostIO((u8*)pData, size, numSectors, sectorSize, (u8*)pCommand);
}


}
}
}*/