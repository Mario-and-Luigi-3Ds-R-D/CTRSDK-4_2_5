#pragma once

#include "nn/os/os_Synchronization.h"
#include "nn/svc/svc_Api.h"
#include "nn/util/util_Result.h"

namespace nn{
namespace os{
    class InterruptEvent : public WaitObject{
    };

    class EventBase : public InterruptEvent{
    public:
        void Initialize(ResetType resetType);
        void Finalize();
        void Signal();
        void ClearSignal();
        
    private:
        Result TryInitializeImpl(ResetType resetType);
    };

    inline Result EventBase::TryInitializeImpl(ResetType resetType){
        Handle handle;
        NN_UTIL_RETURN_IF_FAILED(svc::CreateEvent(&handle, resetType));
        this->SetHandle(handle);
        return ResultSuccess();
    }

    inline void EventBase::Initialize(ResetType resetType){
        NN_OS_ERROR_IF_FAILED(TryInitializeImpl(resetType));
    }

    inline void EventBase::Finalize(){
        this->HandleObj::Finalize();
    }
    
    inline void EventBase::Signal(){
        NN_OS_ERROR_IF_FAILED(svc::SignalEvent(GetHandle()));
    }

    inline void EventBase::ClearSignal(){
        NN_OS_ERROR_IF_FAILED(nn::svc::ClearEvent(GetHandle()));
    }

    class Event : public EventBase{ // most pointless heiharchy
    public:
    
        Event(){ this->ClearHandle();}
        ~Event(){ this->Close(); }
        
        void Initialize(bool manualReset) { EventBase::Initialize(manualReset ? RESET_TYPE_STICKY: RESET_TYPE_ONESHOT); }
        void Finalize() { EventBase::Finalize(); }
        void Signal() { EventBase::Signal(); }
        void Wait() { EventBase::WaitOne(); }
    };
}
}