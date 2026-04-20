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

#ifdef NONMATCHING_REASON_REGMISMATCH
#endif

int sInitializeCount = 0;
static os::CriticalSection sInitializeLock;
const char PORT_NAME_SERVICE[] = "srv:";

Result Initialize(){
    os::CriticalSection& lock = srv::sInitializeLock;
    lock.Enter();
    int count = srv::sInitializeCount;
    if(count > 0){
        srv::sInitializeCount = count + 1;
        Result rc;
        rc.mResult = 0x82067F9;
        lock.Leave();
        return rc;
    }
    Result connect = detail::Connect(srv::PORT_NAME_SERVICE);
    lock.Leave();
    return connect;
}

Result StartNotification(){

}

//static NotificationHandler* srv::sHandlerManager = nullptr;

Result RegisterNotificationHandler(NotificationHandler* pHandler, u32 message){

}

Result GetServiceHandle(nn::Handle *pOut, const char *pName, s32 nameLen, bit32 flags) {
    if (srv::sInitializeCount <= 0) {
        Result rc;
        rc.mResult = 0xD8A067F8;
        return rc;
    }
    if (nameLen > 8) {
        Result rc;
        rc.mResult = 0xD9006405;
        return rc;
    }
    return nn::srv::detail::Service::GetServiceHandle(pOut, pName, nameLen, flags);
}


}
}