#include <nn/dev/CTR/dev_Api.h>
#include <nn/dev/CTR/dev_Ipc.h>
#include <nn/srv/srv_Api.h>
#include <string.h>

#ifdef NN_DEBUG

namespace nn{
namespace dev{
namespace CTR{
namespace{
    bool sInitialized;
}
namespace{
    Dev sDevHandle;

    size_t CalcSize(s32 numSectors, SectorSize sectorSize){
        size_t SIZE_TABLE[9];
        memcpy(SIZE_TABLE, SECTOR_SIZE_TABLE, sizeof(SECTOR_SIZE_TABLE));
        return SIZE_TABLE[sectorSize] * numSectors;
    }
}
void Initialize(){
    size_t nameLen;
    Result res;
    if(sInitialized == false){
        srv::Initialize();
        nameLen = strlen(pxi::CTR::PORT_NAME_DEV);
        res.mResult = srv::GetServiceHandle(&sDevHandle.mSession, pxi::CTR::PORT_NAME_DEV,nameLen, 0).IsFailure();
        NN_RESULT_TASSERT_(res);
        sInitialized = true;
    }
}

void Finalize(){
    if(sInitialized != false){
        nnResult res;
        res.value = svc::CloseHandle(sDevHandle.mSession).IsFailure();
        NN_RESULT_TASSERT_(res);
        sInitialized = false;
    }
}

Result ReadHostIO(void* pData, s32 numSectors, SectorSize sectorSize, const u8* pCommand){
    NN_TASSERTMSG_(sInitialized, "Not initialized");
    u32 size = CalcSize(numSectors,sectorSize);
    Dev dev(sDevHandle);
    return dev.ReadHostIO((u8*)pData, size, numSectors, sectorSize, (u8*)pCommand);
}


}
}
}

#endif