#include <nn/os/os_LightEvent.h>
#include <nn/svc/svc_Api.h>
// Should be 100%
namespace nn{
namespace os{

void LightEvent::Initialize(bool pIsManualReset){
    this->mLock.Initialize();
    *this->mCounter = pIsManualReset ? NOT_RESETED_MANUAL: NOT_RESETED_AUTO;
}

void LightEvent::ClearSignal(){
    if(*this->mCounter == RESETED_MANUAL){
        SimpleLock::ScopedLock lock(this->mLock);
        *this->mCounter = NOT_RESETED_MANUAL;
    }
    else if(*this->mCounter == RESETED_AUTO){
        *this->mCounter = NOT_RESETED_AUTO;
    }
}

void LightEvent::Wait(){
    for(;;){
            switch (*this->mCounter){
            case NOT_RESETED_MANUAL:
                    this->mCounter.WaitIfLessThan(0);
                    return;
            case RESETED_MANUAL:
                    return;
            case NOT_RESETED_AUTO:
                    break;
            case RESETED_AUTO:
                if (this->mCounter->CompareAndSwap (RESETED_AUTO, NOT_RESETED_AUTO) == RESETED_AUTO) {
                    return;
                }
                break;
            }
        mCounter.WaitIfLessThan (0);
    }
}

void LightEvent::Signal() {
    if(*this->mCounter == NOT_RESETED_AUTO){
        *this->mCounter = RESETED_AUTO;
        this->mCounter.Signal(1);
    }
    else if(*this->mCounter == NOT_RESETED_MANUAL){
        SimpleLock::ScopedLock lock(this->mLock);
        *this->mCounter = RESETED_MANUAL;
        this->mCounter.SignalAll();
    }
}

bool LightEvent::TryWait(fnd::TimeSpan timeout){
    for(;;){
        switch(*this->mCounter){

        case NOT_RESETED_MANUAL:
            return this->mCounter.WaitIfLessThan(0, timeout) == ResultSuccess();
        case RESETED_MANUAL:       
            return true;
        case NOT_RESETED_AUTO:     
            break;
        case RESETED_AUTO:{
            if(this->mCounter->CompareAndSwap(RESETED_AUTO, NOT_RESETED_AUTO) == RESETED_AUTO ){
                return true;
            }
        } 
        break;
        //os::Tick begin = os::Tick::GetSystemCurrent();
        //os::Tick end = begin + timeout;

        }
    }
    for(;;){
/*        os::Tick remainTick = end - os::Tick::GetSystemCurrent();

        if(remainTick <= 0){
            return false;
        }
        Result result = this->mCounter.WaitIfLessThan(0, remainTick);

        if(result != ResultSuccess()){
            return false;
        }
*/         
        if(*this->mCounter == RESETED_AUTO){
            if(this->mCounter->CompareAndSwap(RESETED_AUTO, NOT_RESETED_AUTO) == RESETED_AUTO ){
                return true;
            }
        }
    }
}
    
// end non match
} // os
} // nn