#include <nn/fs/fs_IStream.h>

namespace nn{
namespace fs{

    IInputStream::~IInputStream(){
        (&this->flag1 + *(int*)((int)this + -0xc));
    }

    IOutputStream::~IOutputStream(){
        (&this->flag1 + *(int*)((int)this + -0xc));
    }

    IStream::~IStream(){
        (&this->mInputStream.flag1 + *(int*)((int)this + -0xc));
    }

} // fs
} // nn