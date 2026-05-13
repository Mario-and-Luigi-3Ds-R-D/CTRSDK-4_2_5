#include <nn/os/os_TransferMemoryBlock.h>
#include <nn/os/os_SharedMemory.h>
#include <nn/os/CTR/os_ErrorHandler.h>
#include <nn/os/os_Result.h>
#include <nn/svc/svc_Api.h>

namespace nn{
namespace os{

TransferMemoryBlock::~TransferMemoryBlock(){
    this->Finalize();
}

void TransferMemoryBlock::Finalize(){
    if (this->IsValid()){
        Unmap();
        this->Close();
    }
}

void TransferMemoryBlock::Initialize(void* p, size_t size, bit32 myPermission, bit32 otherPermission){
    NN_OS_ERROR_IF_FAILED(TryInitialize(p, size, myPermission, otherPermission));
}

/* Privates */

void TransferMemoryBlock::Unmap(){
    if (GetAddress() != NULL){
        if(this->mSpaceAllocated){
            nn::svc::UnmapMemoryBlock(GetHandle(), GetAddress());
            os::detail::FreeToSharedMemorySpace(this);
        }
        else{
            SetAddressAndSize(0, 0);
        }
    }
}

Result TransferMemoryBlock::TryInitialize(void* p,size_t size,bit32 myPermission,bit32   otherPermission ){
    if ((reinterpret_cast<uptr>(p) % NN_OS_MEMORY_PAGE_SIZE ) != 0 ){
        return ResultMisalignedAddress();
    }
    if ((size % NN_OS_MEMORY_PAGE_SIZE ) != 0){
        return ResultMisalignedSize();
    }

    Handle handle;
    Result result;
    result = nn::svc::CreateMemoryBlock(&handle, reinterpret_cast<uptr>(p), size, myPermission, otherPermission);
    this->SetHandle(handle);

    SetAddressAndSize(reinterpret_cast<uptr>(p), size);
    return result;
}

}
}