#include <nn/os/os_LightEvent.h>
#include <nn/svc/svc_Api.h>
// Should be 100%
namespace nn{
namespace os{

void LightEvent::Initialize(bool pIsManualReset){
    this->mLock.Initialize();
    *this->mCounter = pIsManualReset ? RESET_MANUAL: RESET_AUTO;
}

void LightEvent::ClearSignal(){
    if(*this->mCounter == RESET_UNK1){
        this->mLock.Lock();
        *this->mCounter = RESET_MANUAL;
    }
    else if(*this->mCounter == RESET_UNK0){
        *this->mCounter = RESET_AUTO;
    }
    this->mLock.Unlock();
}

void LightEvent::Wait(){
    while (true){
            switch (*this->mCounter){
            case RESET_MANUAL:
                    this->mCounter.WaitIfLessThan (0);
                    return;
            case RESET_UNK1:
                    return;
            case RESET_AUTO:
                    break;
            case RESET_UNK0:
                if (this->mCounter->CompareAndSwap (RESET_UNK0, RESET_AUTO) == RESET_UNK0) {
                    return;
                }
                break;
            }
        mCounter.WaitIfLessThan (0);
    }
}

void LightEvent::Signal() {
    if(*this->mCounter == RESET_AUTO){
        *this->mCounter = RESET_UNK0;
        this->mCounter.Signal(1);
    }
    else if(*this->mCounter == RESET_MANUAL){
        this->mLock.SimpleLock::Lock(); // Locks the LightEvent
        *this->mCounter = RESET_UNK1;
        this->mCounter.SignalAll();
        this->mLock.Unlock();
    }
}

bool LightEvent::TryWait(){
    if(*this->mCounter == RESET_UNK1){
        return true;
    }
    else{
        return this->mCounter->CompareAndSwap(RESET_UNK0, RESET_AUTO) == RESET_UNK0;
    }
}
    
// end non match
} // os
} // nn