#include <nn/crypto/crypto_Sha512BitContext.h>
#include <nn/nstd/ARMv6/nstd_Mem.h>
extern "C" void nnnstdMemCpy(void* pOut, const void* scrp, size_t size);
namespace nn{
namespace crypto{
namespace{
    s8 sPadding[64];
}
inline CopyBytes(u8* pSrc, const u8* pDst, size_t length){
    nnnstdMemCpy();
}

void ShaBlock512BitContext::AddPadding(){
    u32 size;
    u32 pool;
    u32 footer[2];
    footer[1] = Convert32HToBE(this->mBlocksLow * 0x200 + this->mPool * 8);
    footer[0] = Convert32HToBE(this->mBlocksHigh * 0x200 + (this->mBlocksLow >> 0x17));
    pool = this->mPool;
    if(pool < 0x38)
        size = 0x38 - pool;
    else
        size = 0x78 - pool;
    this->Update(sPadding,size);
    this->Update(footer,8);
}
}
}