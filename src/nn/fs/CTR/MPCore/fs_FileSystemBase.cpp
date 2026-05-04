#include <nn/fs/CTR/MPCore/fs_FileSystemBase.h>
#include <nn/fs/CTR/MPCore/fs_ArchiveHandle.h>
#include <nn/err/CTR/err_Api.h>

namespace nn{
namespace fs{
namespace{
    extern u8 buf[0x8];
    extern CTR::MPCore::detail::IArchive* gSaveDataArchive;
}
/*Result MountSaveData(char* pArchiveName){
    // TODO
}

Result FormatSaveData(size_t pMaxFiles, size_t pMaxDirectories, bool pIsDuplicated){
    // TODO
}

Result CommitSaveData(const char* archiveName){
    // TODO
}*/

__asm Result MountRom(char *pArchiveName,size_t pMaxFile,size_t pMaxDirectory,void *pWorkingMemory, size_t pWorkingMemorySize,bool pUseCache){
    PUSH            {R4-R6,LR}
    SUB             SP, SP, #0x20
    MOV             R4, R0
    ADD             R0, SP, #0x30
    LDM             R0, {R6,R12}
    MOV             R0, #0
    STR             R0, [SP,#0xC]
    STR             R0, [SP,#0x10]
    STR             R0, [SP,#0x14]
    STR             R0, [SP,#0x18]
    ADD             R0, SP, #0x10
    STR             R0, [SP,#0x8]
    ADD             R0, SP, #0xC
    STMEA           SP, {R6,R12}
    BL              __cpp(nn::fs::CTR::MPCore::detail::OpenDataContent)
    MOVS            R1, R0,LSR#31
    LDREQ           R5, [SP,#0xC]
    MOVEQ           R0, #0
    MOV             R1, PC
    MOVS            R2, R0,LSR#31
    BLNE            __cpp(nn::err::CTR::ThrowFatalErrAll)
    MOV             R3, #0
    MOV             R2, R3
    MOV             R1, R5
    MOV             R0, R4
    BL              __cpp(nn::fs::CTR::MPCore::detail::RegisterArchive)
    MOV             R4, R0
    ANDS            R0, R0, #0x80000000
    BPL             loc_10DA10
    LDR             R1, [R5]
    MOV             R0, R5
    LDR             R1, [R1,#0x30]
    BLX             R1
    MOV             R0, R4
    MOV             R1, PC
    MOVS            R2, R4,LSR#31
    BLNE            __cpp(nn::err::CTR::ThrowFatalErrAll)

loc_10DA10
    ADD             SP, SP, #0x20 ; ' '
    MOV             R0, #0
    POP             {R4-R6,PC}
}

Result MountRom(size_t pMaxFile, size_t pMaxDirectory, void* pWorkingMemory, size_t pWorkingMemorySize, bool pUseCache){
    nn::fs::MountRom("rom", pMaxFile, pMaxDirectory, pWorkingMemory, pWorkingMemorySize, pUseCache);
}

/*Result Unmount(char* pArchiveName){
    // TODO
}

int GetRomRequiredMemorySize(size_t pMaxFile, size_t pMaxDirectory, bool pUseCache){
    // TODO
}

int GetRomRequiredMemorySizeImpl(size_t pMaxFile, size_t pMaxDirectory, bool pUseCache, ProgramDataPath* pContentPath){
    // TODO
}*/

}
}