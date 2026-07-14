#pragma once

#include <nn/Handle.h>
#include <nn/fs/fs_Parameters.h>

namespace nn{
namespace fs{
namespace ipc{

class Directory{
public:
    nn::Handle mSession;

    Directory(){ }
    Directory(Handle session): 
        mSession(session) 
    {}
    Result Read(s32* pNumEntriesOut, fs::DirectoryEntry pEntries[], s32 numEntries); 
    Result Close();
    Result SetPriority(s32 priority);
    Result GetPriority(s32* pOut);
};
}
}
}