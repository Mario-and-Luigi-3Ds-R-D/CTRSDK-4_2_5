#include <nn/applet/CTR/applet_Info.h>

namespace nn{
namespace applet{
namespace CTR{

CTR::AppletAttr GetAttribute(){
    return sAttribute;
}

CTR::AppletAttr GetAppletType(){
    return sAttribute & 7;
}

void SetAttribute(CTR::AppletAttr attribute){
    sAttribute = attribute;
}

s8 IsSystemApplet(){
    return sAttribute & 7 == 2;
}

s8 IsApplication(){
    return sAttribute & 7 == 0;
}

s8 IsInfoAccess(){
    return sAttribute & 7 == 6;
}

void SetHomeButtonState(CTR::HomeButtonState state){
    sHomeButtonState = state;
}

CTR::HomeButtonState GetHomeButtonState(){
    return (CTR::HomeButtonState)sHomeButtonState;
}

void SetExpectationToJumpToHome(bool flag){
    sIsExpectedToJumpToHomeMenu = flag;
}

s8 IsExpectedToJumpToHomeMenu(){
    return sIsExpectedToJumpToHomeMenu;
}

nn::applet::CTR::AppletId GetId(){
    return sId;
}

void SetId(nn::applet::CTR::AppletId id){
    sId = id;
}

u32 GetMessageCommand(){
    return sMessageCommand;
}

void SetMessageCommand(u32 message){
    sMessageCommand = message;
}

CTR::SleepNotificationState GetSleepNoticationState(){
    return (CTR::SleepNotificationState)sSleepNotificationState;
}

void SetSleepNotificationState(CTR::SleepNotificationState state){
    sSleepNotificationState = state;
}

CTR::TransitionType GetTransitionType(){
    return (CTR::TransitionType)sPrevTransitionType;
}

void SetTransitionType(CTR::TransitionType type){
    sPrevTransitionType = type;
}

void SetShutdownCallbackFlag(){
    sIsToCallShutdownCallback = 1;
}

s8 IsToShutdownCallbackFlag(){
    return sIsToCallShutdownCallback;
}

void ClearShutdownCallbackFlag(){
    sIsToCallShutdownCallback = 0;
}

void SetPowerButtonCallbackFlag(){
    sIsToCallPowerButtonCallback = 1;
}

s8 IsToCallPowerButtonCallback(){
    return sIsToCallPowerButtonCallback;
}

void ClearPowerButtonCallbackFlag(){
    sIsToCallPowerButtonCallback = 0;
}

void SetReceivedWakeupByCancelFlag(){
    sIsReceivedWakeupByCancelFlag = 1;
}

s8 IsReceivedWakeupByCancel(){
    return sIsReceivedWakeupByCancelFlag;
}

namespace detail{

CTR::HomeButtonState GetAbsoluteHomeButtonState(){
    CTR::sAbsoluteHomeButtonState;
}

void SetAbsoluteHomeButtonState(CTR::HomeButtonState state){
    CTR::sAbsoluteHomeButtonState = state;
}

void ClearAbsoluteHomeButtonState(){
    CTR::sAbsoluteHomeButtonState = 0;
}

CTR::SleepSysState GetSleepSysState(){
    return (CTR::SleepSysState)CTR::sSleepSysState;
}

void SetSleepSysState(CTR::SleepSysState state){
    CTR::sSleepSysState = state;
}

bool IsActive(){
    return CTR::isActive;
}

void SetActive(){
    CTR::isActive = 1;
}

void SetInactive(){
    nn::applet::CTR::isActive = 0;
}

CTR::PowerButtonState GetPowerButtonState(){
    return (CTR::PowerButtonState)CTR::sPowerButtonState;
}

void SetPowerButtonState(CTR::PowerButtonState state){
    CTR::sPowerButtonState = state;
}

CTR::OrderToCloseState GetOrderToCloseState(){
    return (CTR::OrderToCloseState)CTR::sOrderToCloseState;
}

void SetOrderToCloseState(CTR::OrderToCloseState state){
    CTR::sOrderToCloseState = state;
}

void ClearSleepSysState(){
    CTR::sSleepSysState = 0;
}

void SetShutDownState(CTR::ShutdownState state){
    CTR::sShutdownState = state;
}

s8 IsAppletMode(){
    return CTR::isAppletMode;
}

}
}
}
}