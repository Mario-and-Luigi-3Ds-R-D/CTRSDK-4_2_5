#pragma once

#include "nn/os/os_Types.h"
#include "nn/svc/svc_Api.h"
#include "nn/util/util_Result.h"

namespace nn{
namespace os{
    class InterruptEvent : public nn::os::WaitObject{
    };

    class EventBase : public nn::os::InterruptEvent{
    public:
        void Initialize(ResetType resetType);
        void Finalize();
        
    private:
        Result TryInitializeImpl(ResetType resetType);
    };

    inline Result EventBase::TryInitializeImpl(ResetType resetType){
        Handle handle;
        NN_UTIL_RETURN_IF_FAILED(nn::svc::CreateEvent(&handle, resetType));
        this->SetHandle(handle);
        return ResultSuccess();
    }

    inline void EventBase::Initialize(ResetType resetType){
        NN_OS_ERROR_IF_FAILED(TryInitializeImpl(resetType));
    }

    class Event : public nn::os::EventBase{ // most pointless heiharchy
    public:
    
        Event(){
            this->ClearHandle();
        }

        ~Event(){
            this->Close();
        }
        void Initialize(bool manualReset) { EventBase::Initialize(manualReset ? RESET_TYPE_STICKY: RESET_TYPE_ONESHOT); }
        void Finalize() { EventBase::Finalize(); }
    };
}
}