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

bool UserFileSystem::Initialize(){

}

void UserFileSystem::CloseFile(void* p){
    if(p != (void*)0x0){
        uintptr_t fn = *(uintptr_t*)(*(uintptr_t*)p + 0x2c);
        ((void(*)())fn)();
        return;
    }
    return;
}

Result UserFileSystem::TryGetFileSize(long long* pOut,void* p){
    if(p != (void*)0x0){
        uintptr_t fn = *(uintptr_t*)(*(uintptr_t*)p + 0x8);
        ((Result(*)(void*, long long*))fn)(p, pOut);
        return;
    }
    return;
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