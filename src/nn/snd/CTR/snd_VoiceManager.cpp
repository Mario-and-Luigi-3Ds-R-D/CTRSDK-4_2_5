#include <nn/snd/CTR/MPCore/snd_Voice.h>
#include <nn/snd/CTR/Common/snd_Const.h>

namespace nn{
namespace snd{
namespace CTR{
namespace internal{
    CTR::VoiceManager sVoiceManager;
}

VoiceManager::VoiceManager(){
    u8* pBuffer = this->mVoiceBuffer;
    u8* pImplBuffer = this->mVoiceImplBuffer;
    for (s32 i = 0; i < NN_SND_VOICE_NUM; i++){

        this->mpVoice[i] = new (pBuffer) Voice(i);
        NN_TASSERT_(reinterpret_cast<uptr>(m_pVoice[i]) == reinterpret_cast<uptr>(pBuffer));
        pBuffer += sizeof(Voice);

        this->mpVoice[i]->mpImpl = new (pImplBuffer) VoiceImpl(i);
        NN_TASSERT_(reinterpret_cast<uptr>(this->mpVoice[i]->mpImpl) == reinterpret_cast<uptr>(pImplBuffer));
        pImplBuffer += sizeof(VoiceImpl);
    }
}

void VoiceManager::Initialize(){
    this->mMostPriorVoice = 0;
    this->mMostInferiorVoice = 0;
    this->mUsedVoiceBits = 0;
    this->mAllocatedVoiceCount = 0;
    this->SetVoiceDropMode(VOICE_DROP_MODE_DEFAULT);
    this->mCriticalSection.Initialize();
}

void VoiceManager::Finalize(){
    this->mCriticalSection.Finalize();
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
    if (!v) return;
    
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
    Voice* v = NULL;
    NN_TASSERT_(0 <= priority && priority <= VOICE_PRIORITY_NODROP);
    if(!(0 <= priority && priority <= VOICE_PRIORITY_NODROP))
        return NULL;
    this->mCriticalSection.Enter();
    if(math::CntBit1(this->mUsedVoiceBits) == NN_SND_VOICE_NUM){
        NN_TASSERT_(mMostInferiorVoice != NULL);
        if((this->mMostInferiorVoice->mPriority == VOICE_PRIORITY_NODROP || this->mMostInferiorVoice->mPriority > priority)){
            this->mCriticalSection.Leave();
            return NULL;
        }
        else{
            Voice* voice = this->mMostInferiorVoice;
            VoiceDropCallbackFunc _callback = voice->mCallback;
            uptr _userArg = voice->mUserArg;
            FreeVoice(this->mMostInferiorVoice);
            if (_callback){
                (_callback)(voice, _userArg);
            }
        }
    }
    v = GetAvaliableVoice();
    NN_TASSERT_(v != NULL);

    v->mPriority = priority;

    this->InsertVoiceToPriorityList(v,priority);
    this->mCriticalSection.Leave();

    v->mpImpl->SetState(Voice::STATE_PAUSE);
    v->mpImpl->mSyncCount;

    v->mCallback = callback;
    v->mUserArg = userArg;

    return v;
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
    s32 varVoice = this->mUsedVoiceBits;
    Voice * pVoice = reinterpret_cast<Voice*>(NULL);
}

/*inline VoiceManager* VoiceManager::GetInstance(){
    return &internal::sVoiceManager;
}*/

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
}
}
}