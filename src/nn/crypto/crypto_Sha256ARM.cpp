#include <nn/crypto/crypto_Sha256Context.h>
#include <nn/Assert.h>

namespace nn{
namespace crypto{

void Sha256Context::Initialize(){
    this->mBlocksLow = 0;
    this->mBlocksHigh = 0;
    this->mPool = 0;
    mH[0] = 0x6a09e667;
    mH[1] = 0xbb67ae85;
    mH[2] = 0x3c6ef372;
    mH[3] = 0xa54ff53a;
    mH[4] = 0x510e527f;
    mH[5] = 0x9b05688c;
    mH[6] = 0x1f83d9ab;
    mH[7] = 0x5be0cd19;
}

void Sha256Context::Update(const void* pData, size_t size){
    NN_TASSERT_(pData != 0);
    NN_MIN_TASSERT_(size);
    this->ShaBlock512BitContext::Update(pData, size);
}

void Sha256Context::GetHash(void* pOut){
    this->AddPadding();
    u32* out = reinterpret_cast<u32*>(pOut);
    out[0] = Convert32HToBE(mH[0]);
    out[1] = Convert32HToBE(mH[1]);
    out[2] = Convert32HToBE(mH[2]);
    out[3] = Convert32HToBE(mH[3]);
    out[4] = Convert32HToBE(mH[4]);
    out[5] = Convert32HToBE(mH[5]);
    out[6] = Convert32HToBE(mH[6]);
    out[7] = Convert32HToBE(mH[7]);
}



}
}