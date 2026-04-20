#include <nn/svc/svc_Api.h>
#include <nn/os/os_Memory.h>
#include <nn/util/util_Result.h>
#include <nn/srv/srv_EventNotication.h>

namespace{
    class ExitHandler : public nn::srv::NotificationHandler{
    public:
        virtual void HandleNotification(bit32 message){
            nn::svc::ExitProcess();
        }
    };
    bool sUsingStartUpDefault = false;
    ExitHandler sExitHandler;
}



extern "C" {
    
void nninitStartUpDefault(){

}

void nninitSetupDefault(){
    nn::srv::Initialize();
    nn::srv::StartNotification();
}


}