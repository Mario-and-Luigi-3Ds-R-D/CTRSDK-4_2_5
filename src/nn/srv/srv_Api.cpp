#include <nn/srv/srv_Api.h>
#include <nn/srv/detail/srv_Service.h>
#include <nn/os/os_Thread.h>

namespace nn{
namespace srv{
namespace{
void DispatcherThread(){

}

}
namespace detail{
Result Connect(const char*){

}

}

int sInitializeCount = 0;
static os::CriticalSection sInitializeLock;
const char PORT_NAME_SERVICE[] = "srv:";

Result Initialize(){
    os::CriticalSection& lock = srv::sInitializeLock;
    lock.Enter();
    if(srv::sInitializeCount > 0){
        #ifdef NN_DEBUG
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"srv_Api.cpp",0xa7,"%s(=%d) must be >= %s(=%d).","sInitializeCount",sInitializeCount);
        #endif
        srv::sInitializeCount++;
        Result res; res.mResult = 0x82067F9;
        lock.Leave();
        return res;
    }
    Result connect = detail::Connect(srv::PORT_NAME_SERVICE);
    lock.Leave();
    return connect;
}

Result StartNotification(){

}

static nn::fnd::IntrusiveLinkedList<HandlerManager>::Item* sHandlerManager = 0;

#ifdef NONMATCHING
#endif

Result RegisterNotificationHandler(NotificationHandler* pHandler, u32 message){
    #ifdef NN_DEBUG
    if(0x1fefffff < pHandler + -0x10000){
        nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"srv_Api.cpp",0x28,"%s(=0x%08X) is invalid pointer", "pHandler", pHandler);
    }
    if(message != 0){
        nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"srv_Api.cpp",0x29,"%s","message != 0");
    }
    if(pHandler->mAttachedMessage == 0){
        nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"srv_Api.cpp",0x2a,"%s","pHandler->mAttachedMessage == 0");
    }
    #endif
    pHandler->mAttachedMessage = message;

    nn::fnd::IntrusiveLinkedList<HandlerManager>::Item* handlerLink = pHandler ? (nn::fnd::IntrusiveLinkedList<HandlerManager>::Item*)((u8*)pHandler + 4) : 0;
    nn::fnd::IntrusiveLinkedList<HandlerManager>::Item* manager = sHandlerManager;

    if(!manager){
        nn::fnd::IntrusiveLinkedList<HandlerManager>::Item* handlerLink2 = pHandler ? (nn::fnd::IntrusiveLinkedList<HandlerManager>::Item*)((u8*)pHandler + 4) : 0;
        *((nn::fnd::IntrusiveLinkedList<HandlerManager>::Item**)((u8*)pHandler + 8)) = handlerLink;
        *((nn::fnd::IntrusiveLinkedList<HandlerManager>::Item**)((u8*)pHandler + 4)) = handlerLink2;
        sHandlerManager = pHandler ? (nn::fnd::IntrusiveLinkedList<HandlerManager>::Item*)((u8*)pHandler + 4) : 0;
    }
    else{
        handlerLink->mNextLink = manager;
        manager->mPrevLink->mNextLink = handlerLink;
        handlerLink->mPrevLink = manager->mPrevLink;
        manager->mPrevLink = handlerLink;
    }
//    Result res;
    return ResultSuccess();
}

Result GetServiceHandle(nn::Handle *pOut, const char *pName, s32 nameLen, bit32 flags) {
    if (srv::sInitializeCount <= 0) {
        Result res;
        res.mResult = 0xD8A067F8;
        return res;
    }
    if (nameLen > 8) {
        Result res;
        res.mResult = 0xD9006405;
        return res;
    }
    return nn::srv::detail::Service::GetServiceHandle(pOut, pName, nameLen, flags);
    #ifdef NN_DEBUG
        nndbgTPrintWarning_("srv_Api.cpp",0x170,"Failed to open service \"%s\"\n",pName);
    #endif
}


}
}