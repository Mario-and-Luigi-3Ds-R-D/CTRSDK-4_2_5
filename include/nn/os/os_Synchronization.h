#pragma once

// Rename 2 os_Types.h

#include "nn/os/os_Types.h"
#include "nn/svc/svc_Api.h"
#include "nn/Assert.h"

// forwards

/*namespace nn {
namespace svc {
    Result CloseHandle(nn::Handle);
    Result WaitSynchronizationN(int*, const nn::Handle*, int,bool,long long);
}
}*/


namespace nn{
namespace os{

    struct HandleManager{
    };

    class HandleObj : util::ADLFireWall::NonCopyable<HandleObj>{
    public:
        Handle mHandle;
    public:
        HandleObj() {}
        ~HandleObj(){ Close(); }
        Handle GetHandle() const{ return mHandle; }
        bool IsValid() const{ return mHandle.IsValid(); }
        void SetHandle(nn::Handle handle);
        void Close(){
            if (IsValid()) {
                nn::svc::CloseHandle(mHandle);
                mHandle = Handle();
            }
        }
        void Finalize(){ Close(); }
        void ClearHandle(){ mHandle = Handle(); }
    };
    
    inline void HandleObj::SetHandle(nn::Handle handle){
        NN_TASSERTMSG_(!IsValid(), "current handle(=%08X) is active\n", mHandle.GetPrintableBits());
        NN_TASSERT_(handle.IsValid());
        this->mHandle = handle;
    }

    class WaitObject : public HandleObj{
    public:
        nn::Result WaitOneImpl(s64);
        void WaitOne();
    protected:
        WaitObject() {}
        ~WaitObject() {}
    };

    inline nn::Result WaitObject::WaitOneImpl(s64 nanoSecondsTimeout){
        s32 dummy;
        Handle handle = GetHandle();
        return nn::svc::WaitSynchronizationN(&dummy, &handle, 1, false, nanoSecondsTimeout);
    }
    inline void WaitObject::WaitOne(){ NN_OS_ERROR_IF_FAILED(WaitOneImpl(WAIT_INFINITE)); }
}
}