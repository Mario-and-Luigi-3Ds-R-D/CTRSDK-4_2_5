#include <nn/fs/CTR/MPCore/fs_RomFsArchive.h>


namespace nn {
namespace fs {
namespace CTR {
namespace MPCore {
namespace detail {

Result RomFsArchive::OpenFile(IFile** pOut, const Path& path, bit32 unk3) {

}

Result RomFsArchive::OpenDirectory(IDirectory** pDir, const Path& path) {

}

Result RomFsArchive::DeleteFile(const Path& path) {
    return *(Result*)0xe0c046f8;
}

Result RomFsArchive::RenameFile(const Path& path, const Path& newPath) {
    return *(Result*)0xe0c046f8;
}

Result RomFsArchive::DeleteDirectory(const Path& path) {
    return *(Result*)0xe0c046f8;
}

Result RomFsArchive::TryDeleteDirectoryRecursively(const Path& path) {
    return *(Result*)0xe0c046f8;
}

Result RomFsArchive::CreateFile(const Path& path) {
    return *(Result*)0xe0c046f8;
}

Result RomFsArchive::CreateDirectory(const Path& path) {
    return *(Result*)0xe0c046f8;
}

Result RomFsArchive::RenameDirectory(const Path& path, const Path& newPath) {
    return *(Result*)0xe0c046f8;
}

RomFsArchive::~RomFsArchive() {
    this->mpBaseFile = 0; // other donconsts do the rest
}

void RomFsArchive::DuplicateHandle() {

}

void RomFsArchive::OpenLinkHandle() {
    this->mpBaseFile->Close();
}


//
// RomFsArchive::File
//


Result RomFsArchive::File::TryRead(s32* pOut, s64 offset, size_t size) {

}

Result RomFsArchive::File::TryWrite(s32* pOut, s64 offset, size_t size, bool flush) {

}

Result RomFsArchive::File::TryGetSize(s64* pOut) {

}

Result RomFsArchive::File::TrySetSize(s64 size) {

}

Result RomFsArchive::File::TryFlush() {

}

Result RomFsArchive::File::DuplicateHandle(Handle* pOut, s64 head, s64 tail) {

}

Handle RomFsArchive::File::GetFileHandle() const {

}

void RomFsArchive::File::DetachFileHandle() {

}

void RomFsArchive::File::Close() {

}


//
// ContentRomFsArchive
//


int* ContentRomFsArchive::AllocateBuffer() {

}

ContentRomFsArchive::ContentRomFsArchive() {

}

void ContentRomFsArchive::DeleteObject() {

}

ContentRomFsArchive::~ContentRomFsArchive() {

}

void ContentRomFsArchive::OpenDirect() {

}

}
}
}
}
}