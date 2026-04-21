#pragma once

#include <cwchar>

namespace nn {
namespace fslow {

template <class T, typename V>
class LowPath{
protected:
        bit32       mPathType; // todo: possible enum?
        const void* mData;
        size_t      mBinarySize;
public:
    LowPath (){
        this->mPathType   = 4;
        this->mData       = &mData;
        this->mBinarySize = 1;
    }
    LowPath (const wchar_t* path){
        this->mPathType   = 4;
        this->mData       = path;
        //this->mBinarySize = 2 * (wcslen (path) + 1);
    }

    const wchar_t* GetWStringRaw (){
        if (GetPathType () == 4) {
            return (wchar_t*)this->mData;
        }
        return NULL;
    }
    bit32       GetPathType () { return this->mPathType; }
    const void* GetDataBuffer () { return this->mData; }
    size_t      GetDataSize () { return this->mBinarySize; }

    static LowPath Make (const T* p){
        LowPath ret;
        ret.SetBinary (p);
        return ret;
    }

    void SetBinary (const T* p){
        this->mPathType   = 2;
        this->mData       = p;
        this->mBinarySize = sizeof (T);
    }
};

} // namespace fslow
} // namespace nn