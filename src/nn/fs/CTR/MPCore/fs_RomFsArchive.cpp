#include <nn/fs/CTR/MPCore/fs_RomFsArchive.h>


namespace nn {
namespace fs {
namespace CTR {
namespace MPCore {
namespace detail {

Result RomFsArchive::OpenFile(IFile** pOut, const Path& path, bit32 unk3) {
    // TODO
}

Result RomFsArchive::OpenDirectory(IDirectory** pDir, const Path& path) {
    // TODO
}

Result RomFsArchive::DeleteFile(const Path& path) {
    return (Result)0xe0c046f8;
}

Result RomFsArchive::RenameFile(const Path& path, const Path& newPath) {
    return (Result)0xe0c046f8;
}

Result RomFsArchive::DeleteDirectory(const Path& path) {
    return (Result)0xe0c046f8;
}

Result RomFsArchive::TryDeleteDirectoryRecursively(const Path& path) {
    return (Result)0xe0c046f8;
}

Result RomFsArchive::CreateFile(const Path& path) {
    return (Result)0xe0c046f8;
}

Result RomFsArchive::CreateDirectory(const Path& path) {
    return (Result)0xe0c046f8;
}

Result RomFsArchive::RenameDirectory(const Path& path, const Path& newPath) {
    return (Result)0xe0c046f8;
}

RomFsArchive::~RomFsArchive() {
    this->mpBaseFile = 0; // other donconsts do the rest
    for(int i = 0; i < 5; i++){
        if(this->mpPriorFiles[i] != 0){
            this->mpPriorFiles[i]->Close();
        }
    }
}

Result RomFsArchive::DuplicateHandle(nn::Handle*, s64, s64) {
    // TODO
}

Result RomFsArchive::OpenLinkHandle(nn::Handle*) {
    this->mpBaseFile->Close();
}


//
// RomFsArchive::File
//


Result RomFsArchive::File::TryRead(s32* pOut, s64 offset, size_t size) {
    // TODO
}

Result RomFsArchive::File::TryWrite(s32* pOut, s64 offset, size_t size, bool flush) {
    return (Result)0xe0c046f8;
}

Result RomFsArchive::File::TryGetSize(s64* pOut) {
    s64 head = this->mHead;
    s64 tail = this->mTail;
    *pOut = mTail - mHead;
    return ResultSuccess();
}

Result RomFsArchive::File::TrySetSize(s64 size) {
    return (Result)0xe0c046f8;
}

Result RomFsArchive::File::TryFlush() {
    return (Result)0xe0c046f8;
}

Result RomFsArchive::File::TrySetPriority(s32 pOut){
    // TODO
}

Result RomFsArchive::File::TryGetPriority(s32* pOut) const{
    if(pOut != 0)
        *pOut = this->mPriority;
    return ResultSuccess();
}

Result RomFsArchive::File::DuplicateHandle(Handle* pOut, s64 head, s64 tail) {
    s64 newHead = mHead + head;
    s64 newTail = mHead + tail;

    return mParent->OpenLinkHandle(pOut);
}

void RomFsArchive::File::Close() {
    this->TrySetSize(NULL);
    this->mParent->mFileHeap.Free(this);
}


//
// ContentRomFsArchive
//


int* ContentRomFsArchive::AllocateBuffer() {
    /*os::CriticalSection::ScopedLock(gMountLock)
        static fnd::

    */
}

ContentRomFsArchive::ContentRomFsArchive() { }

void ContentRomFsArchive::DeleteObject() {
    //this->mFileHeap.
    //sArchiveHeap.Free();
}

ContentRomFsArchive::~ContentRomFsArchive() { }

void ContentRomFsArchive::OpenDirect() {

}

}
}
}
}
}