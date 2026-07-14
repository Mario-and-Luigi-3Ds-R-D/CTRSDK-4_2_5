// Filename: ro_Api.cpp
//
// Project: Horizon Decompilation

#include <nn/ro/ro_Api.h>
#include <nn/srv.h>
#include <nn/svc.h>
#include <nn/Result.h>
#include <nn/Handle.h>
#include <nn/os.h>
#include <nn/err.h>
#include <nn/math.h>
#include <nn/util/detail/util_Symbol.h>
#include <nn/ro.h>
#include <nn/ro/ro_DynamicLoader.h>
#include <nn/ro/ro_DebugInfo.h>
#include <nn/dbg/dbg_PrintResult.h>
#include <nn/ro/ro_ObjectFile.h>
#include <nn/module.h>
#include <algorithm>

extern "C"{
    nnResult nnRoDetailInitializeLinkException(void* pRs, size_t rsSize);
}

namespace nn{
namespace ro{
namespace{
    NN_MAKE_MODULE_SDK(sModuleSign, "RO"); // found in plainrgn.bin

    ModuleHeader* spStatic;
    ModuleRegistrationListHeader* spListNode;

    Result Connect(){
        //return srv::GetServiceHandle(&detail::DynamicLoader::sSession, "ldr:ro");
    }

    void Disconnect(){
        //Result result = svc::CloseHandle(detail::DynamicLoader::sSession);
        //NN_ERR_THROW_FATAL_ALL(result);

        //detail::DynamicLoader::sSession = INVALID_HANDLE_VALUE;
    }

    bool IsConnected(){
        //return detail::DynamicLoader::sSession != INVALID_HANDLE_VALUE;
    }

    uptr GetLocateAddress(void* p){
        const uptr orgAddr = reinterpret_cast<uptr>(p);
        const uptr heapBase = os::detail::GetHeapAddressWithoutCheck();

        if(orgAddr >= heapBase){
            return orgAddr - (heapBase - 0x8000000);
        }
        else{
            return orgAddr;
        }
    }

    Result InitializeImpl(void* pRs, size_t rsSize){
        Result res;

        NN_REFER_MODULE(sModuleSign);

        if(IsConnected()){
            return ro::ResultAlreadyInitialized();
        }

        res = Connect();
        if(res.IsFailure()){
            return res;
        }

        const uptr locateAddr = GetLocateAddress(pRs);

        //res = detail::DynamicLoader::Startup(PSEUDO_HANDLE_CURRENT_PROCESS,reinterpret_cast<uptr>(pRs),rsSize,locateAddr);

        if(res.IsSuccess()){
            spStatic = reinterpret_cast<ModuleHeader*>(locateAddr);
            detail::EnableDebugNotification(false);
        }
        else{
            Disconnect();
        }

        return res;
    }

    s32 FindHash(const ModuleRegistrationListHeader& rrHeader, const Hash& hash){
        Hash* pHashList = rrHeader.hashOffset.GetPointer(&rrHeader);
        Hash* pHashListEnd = pHashList + rrHeader.numHash;
        Hash* pFound = std::lower_bound(pHashList, pHashListEnd, hash);

        return (pFound != pHashListEnd) ? pFound - pHashList: detail::ENTRY_NOT_FOUND;
    }

    bool HasDebugInfo(const ModuleRegistrationListHeader& rrHeader){
        return rrHeader.debugInfoSize != 0;
    }

    Result UnloadActiveModules(ModuleHeader* pHead){
        if(pHead != NULL){
            ModuleHeader* pTail;

            do{
                pTail = pHead->node.pPrev;
                Result res;
                //Result res = reinterpret_cast<Module*>(pTail)->Unload();

                if(res.IsFailure()){
                    return res;
                }

            } while( pTail != pHead );
        }

        return ResultSuccess();
    }

    Result UnloadModule(ModuleHeader* pRoot){
        Result res;

        res = UnloadActiveModules(pRoot->node.pNext);
        if(res.IsFailure()){
            return res;
        }

        res = UnloadActiveModules(pRoot->node.pPrev);
        if(res.IsFailure()){
            return res;
        }

        return res;
    }

    Result UnregisterAllRegistrationList(ModuleRegistrationListHeader* pAny){
        Result res;

        ModuleRegistrationListHeader* p = pAny;

        while(p->node.pPrev != NULL){
            p = p->node.pPrev;
        }

        while(p != NULL){
            ModuleRegistrationListHeader* pNext = p->node.pNext;

            res = reinterpret_cast<RegistrationList*>(p)->Unregister();

            if(res.IsFailure()){
                return res;
            }

            p = pNext;
        }

        return ResultSuccess();
    }
} // namespace

namespace detail{

uptr GetOriginalAddress(const void* p){
    const uptr locateAddr = reinterpret_cast<uptr>(p);
    if(locateAddr >= 0x8000000){
        const uptr heapBase = os::detail::GetHeapAddressWithoutCheck();
        return locateAddr + (heapBase - 0x8000000);
    }
    else{
        return locateAddr;
    }
}

void UpdateRegistrationListNode(RegistrationList* p){
    spListNode = reinterpret_cast<ModuleRegistrationListHeader*>(p);
}

s32 FindRegistrationListEntry(const RegistrationList** pp, const void* p){
    const Hash& hash = *reinterpret_cast<const Hash*>(p);

    for(ModuleRegistrationListHeader* prlh = spListNode; prlh != NULL; prlh = prlh->node.pNext){
        const s32 found = FindHash(*prlh, hash);

        if(found != -1){
            *pp = reinterpret_cast<RegistrationList*>(prlh);
            return found;
        }
    }

    return -1;
}


bool IsCodeAddress(uptr addr){
    class CodeChecker : public ro::Module::EnumerateCallback{
    private:
        uptr mAddress;
        bool mResult;
        bool mEnabled;
        short rev;
    public:
        CodeChecker(uptr addr): 
            mAddress(addr), 
            mResult(false), 
            mEnabled(false)
        {}
        virtual bool operator()(ro::Module* p){
            mEnabled = true;

            ro::RegionInfo ri;
            p->GetRegionInfo(&ri);
            uptr codeEnd = ri.mCodeBegin + ri.mCodeSize;

            if((ri.mCodeBegin <= mAddress)&& (mAddress < codeEnd) ){
                mResult = true;
                return false;
            }
            else{
                return true;
            }
        }
        bool GetResult() const { return mResult; }
        bool IsEnabled() const { return mEnabled; }
    } checker(addr);

    if(checker.IsEnabled()){
        return checker.GetResult();
    }
    else{
        const uptr begin = os::GetCodeRegionAddress();
        const uptr end = begin + os::GetCodeRegionSize();
        return (begin <= addr) && (addr < end);
    }
}

} // detail

Result Initialize(void* pRs, size_t rsSize){
    NN_UTIL_REFER_SYMBOL(ro::detail::IsCodeAddress);
    //return nnRoDetailInitializeLinkException(pRs, rsSize);
}

Result Finalize(){
    Result res = ResultSuccess();

    if(!IsConnected()){
        return ResultNotInitialized();
    }

    if(spStatic != NULL){
        res = UnloadModule(spStatic);
    }

    if(res.IsSuccess()){
        if(spListNode != NULL){
            res = UnregisterAllRegistrationList(spListNode);
        }
    }

    if(res.IsSuccess()){
        //res = detail::DynamicLoader::Cleanup(PSEUDO_HANDLE_CURRENT_PROCESS,detail::GetOriginalAddress(s_pStatic) );
    }
    if(res.IsSuccess()){
        spStatic = NULL;
        Disconnect();
    }

    return res;
}

}
}