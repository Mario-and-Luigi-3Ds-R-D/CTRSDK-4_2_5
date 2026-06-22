#include <nn/snd/CTR/MPCore/snd_Voice.h>
#include <nn/snd/CTR/Common/snd_Const.h>

namespace nn{
namespace snd{
namespace CTR{
namespace internal{
    CTR::VoiceManager sVoiceManager;
}

// could be wrong idfk
void VoiceManager::AdjustVoicePlayState(s32 remain, s32 frame){
    if (this->mVoiceDropMode == VOICE_DROP_MODE_REAL_TIME){
        s32 bias = frame - 0x9FFC4;
        if (bias > 0){
            remain -= bias;
        }
    }

    os::CriticalSection::ScopedLock lock(this->mCriticalSection);

    Voice* v = this->mMostPriorVoice;
    if (!v)
        lock.~ScopedLock();
    NN_NULL_TASSERT_(this->mMostInferiorVoice);
    while (v){
        VoiceImpl* impl = v->mpImpl;
        if (impl->mState != Voice::STATE_PLAY || impl->mpWaveBuffer == nullptr){
            v = v->mInferiorVoice;
            continue;
        }

        s32 cycle = impl->mDspCycles;
        if (remain < cycle && v->mPriority != 0x7FFF){
            Voice* next = v->mInferiorVoice;
            this->FreeVoice(v);

            if (v->mCallback)
                v->mCallback(v, v->mUserArg);
            v = next;
            continue;
        }
        impl->SetSyncCount();

        if (!impl->mPlaying){
            impl->Start();
        }
        remain -= cycle;
        v = v->mInferiorVoice;
    }
}

Voice* VoiceManager::AllocVoice(s32 priority, VoiceDropCallbackFunc callback, uptr userArg){
    Voice* v;
    VoiceImpl* pVoiceImpl;
    NN_TASSERT_(0 <= priority && priority <= VOICE_PRIORITY_NODROP);
    if((priority < 0) || (VOICE_PRIORITY_NODROP < priority))
        return NULL;
    else{
        this->mCriticalSection.Enter();
        if(math::CntBit1(this->mUsedVoiceBits) == 0x18){
            NN_TASSERT_(mMostInferiorVoice != NULL);
            if((this->mMostInferiorVoice->mPriority == 0x7fff) || (priority < this->mMostInferiorVoice->mPriority)){
                this->mCriticalSection.Leave();
            }
            VoiceDropCallbackFunc func;
            v = this->mMostInferiorVoice;
            func = v->mCallback;
            this->FreeVoice(this->mMostInferiorVoice);
            if(func)
                (*func)(v,v->mUserArg);
        }
        NN_TASSERT_(v != NULL);
        v->mPriority = priority;
        this->InsertVoiceToPriorityList(v,priority);
        v->mpImpl->SetState(Voice::STATE_PAUSE);
        pVoiceImpl = v->mpImpl;
        pVoiceImpl->mSyncCount++;
        v->mCallback = callback;
        v->mUserArg = userArg;
    }
    return v;
}

void VoiceManager::Finalize(){
    this->mCriticalSection.Finalize();
}

void VoiceManager::ForceUpdateParams(){
    for(int i = 0; i < 0x18; i++){
        this->mpVoice[i]->mpImpl->ForceUpdateParams();
    }
}

void VoiceManager::FreeVoice(Voice* pVoice){
    NN_TASSERT_(mpVoice[0] <= pVoice && pVoice <= m_pVoice[NN_SND_VOICE_NUM-1]);
    NN_TASSERTMSG_(!this->IsAllocated(this->pVoice), "Cannot free voice which is not allocated\n");
}

Voice* VoiceManager::GetAvaliableVoice(){
}

/*inline VoiceManager* VoiceManager::GetInstance(){
    return &internal::sVoiceManager;
}*/

void VoiceManager::Initialize(){
    this->mMostPriorVoice = 0;
    this->mMostInferiorVoice = 0;
    this->mUsedVoiceBits = 0;
    this->mAllocatedVoiceCount = 0;
    this->SetVoiceDropMode(VOICE_DROP_MODE_DEFAULT);
    this->mCriticalSection.Initialize();
}

void VoiceManager::InsertVoiceToPriorityList(Voice* pVoice, s32 priority){
    NN_TASSERT_(0 <= priority && priority <= VOICE_PRIORITY_NODROP);
    Voice* v = this->mMostPriorVoice;
    if(!v){
        NN_TASSERT_(this->mMostPriorVoice == NULL && this->mMostInferiorVoice == NULL);
        this->SetMostPriorVoice(pVoice);
        this->SetMostInferiorVoice(pVoice);
    }
    else{
        while(priority < v->mPriority){
            if(!v){
                v->mInferiorVoice = pVoice;
                pVoice->mPriorVoice = v;
                this->SetMostInferiorVoice(pVoice);
                return;
            }
            v = v->mInferiorVoice;
        }
        Voice* newV = v->mPriorVoice;
        pVoice->mPriorVoice = newV;
        pVoice->mInferiorVoice = v;
        if(!newV)
            this->SetMostPriorVoice(pVoice);
        else
            newV->mInferiorVoice = pVoice;
        v->mPriorVoice = pVoice;
    }
    return;
}

void VoiceManager::RemoveVoiceFromPriorityList(Voice* pVoice){
    Voice *pPriorVoice = pVoice->mPriorVoice;
    Voice *pInfVoice = pVoice->mInferiorVoice;
    if((!pPriorVoice) && (!pInfVoice)){
        this->mMostPriorVoice = 0;
        this->mMostInferiorVoice = 0;
    }
    else{
        if((pInfVoice) && (pInfVoice->mPriorVoice = pVoice->mPriorVoice, !pInfVoice->mPriorVoice))
            this->mMostPriorVoice = pInfVoice;
        if((pPriorVoice) && (pPriorVoice->mInferiorVoice = pVoice->mInferiorVoice, !pPriorVoice->mInferiorVoice))
            this->mMostInferiorVoice = pPriorVoice;
    }
}

void VoiceManager::SetPriority(Voice* pVoice, s32 priority){
    NN_TASSERT_(mpVoice[0] <= pVoice && pVoice <= m_pVoice[NN_SND_VOICE_NUM-1]);
    os::CriticalSection::ScopedLock lock(this->mCriticalSection);
    this->RemoveVoiceFromPriorityList(pVoice);
    this->InsertVoiceToPriorityList(pVoice,priority);
}

inline void VoiceManager::SetVoiceDropMode(VoiceDropMode mode){
    NN_TASSERT_(mode == VOICE_DROP_MODE_DEFAULT || mode == VOICE_DROP_MODE_REAL_TIME);
    memcpy(&this->mVoiceDropMode,&mode,1);
}

void VoiceManager::UpdateParams(){
    for(int i = 0; i < 0x18; i++){
        this->mpVoice[i]->mpImpl->UpdateParams();
    }
}

void VoiceManager::UpdateStatus(s32 id, DspsndChannelPlayVars* pVars){
    this->mpVoice[id]->mpImpl->UpdateStatus();
}

void VoiceManager::UpdateWaveBufferList(){
    for(int i = 0; i < 0x18; i++){
        this->mpVoice[i]->mpImpl->UpdateWaveBufferList();
    }
}

VoiceManager::VoiceManager(){

}
}
}
}