#include <nn/fs/CTR/MPCore/fs_UserFileSystem.h>

namespace nn{
namespace fs{
namespace{
    extern u8 buf[0x8];
    extern CTR::MPCore::detail::IArchive* gSaveDataArchive;
}
namespace CTR{
namespace MPCore{
namespace detail{
namespace{
    nn::Handle gFileServerArchive = 0;
    fnd::UnitHeapBase sArchiveHeap = *(fnd::UnitHeapBase*)0;
}

ArchiveTableEntry::ArchiveTableEntry(){
    this->id = 0;
    this->archive = 0;
}

//
// UserFileSystem
//

Result UserFileSystem::Initialize(nn::Handle handle){

}

void UserFileSystem::CloseFile(void* p){
    if(p != (void*)0x0){
        uintptr_t fn = *(uintptr_t*)(*(uintptr_t*)p + 0x2c);
        ((void(*)())fn)();
        return;
    }
    return;
}

__asm Result UserFileSystem::TryGetFileSize(s64* pOut, void* p){
    MOVS            R2, R0
    MOV             R0, R1
    CMPNE           R0, #0
    LDREQ           R0, =0xE0E046BC
    BEQ             locret_120980
    LDR             R1, [R0]
    LDR             R3, [R1,#8]
    MOV             R1, R2
    BX              R3

locret_120980
    BX              LR
}

Result UserFileSystem::TrySetFileSize(void* p, s64 size){
    if(p != (void*)0x0){
        uintptr_t fn = *(uintptr_t*)(*(uintptr_t*)p + 0xC);
        ((void(*)())fn)();
        return;
    }
    return;
}

Result UserFileSystem::TryWriteFile(s32* pOut, void* p, s64 offset, void* buffer, size_t size, bool flush){

}

Result UserFileSystem::TryReadFile(s32* pOut, void* p, s64 offset, void* buffer, size_t size){

}

Result UserFileSystem::TryOpenFile(void** pout,const wchar_t* pathName,bit32 mode){

}

void UserFileSystem::TryFlush(void* p){
    if(p != (void*)0x0){
        uintptr_t fn = *(uintptr_t*)(*(uintptr_t*)p + 0x10);
        ((void(*)())fn)();
        return;
    }
    return;
}

}
}
}
}
}