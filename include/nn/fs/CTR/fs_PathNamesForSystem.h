#pragma once

#include <nn/types.h>
#include <nn/util/util_Int64.h>
#include <nn/util/util_SizedEnum.h>

namespace nn{
namespace fs{
namespace CTR{

struct ProgramDataPath{
    enum Tag{
        TAG_ROMFS_DEFAULT,
        TAG_EXEFS,
        TAG_SYSTEM_MENU_DATA,
        TAG_SAVE_DATA,
        TAG_CONTENT,
        TAG_ROMFS_EXTRA
    };
    
    nn::util::SizedEnum4<Tag> tag;
    nn::util::Int64<bit64> id;

    static ProgramDataPath MakeRomFsDefaultPath(){
        ProgramDataPath ret;
        ret.tag = TAG_ROMFS_DEFAULT;
        ret.id = 0;
        return ret;
    }
};

}
}
}