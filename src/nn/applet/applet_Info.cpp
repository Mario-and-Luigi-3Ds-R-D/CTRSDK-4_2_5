#include <nn/applet/applet_All.h>

namespace nn{
namespace applet{
namespace CTR{

nn::applet::CTR::AppletAttr GetAttribute(){
    return sAttribute;
}

nn::applet::CTR::AppletAttr GetAppletType(){
    return sAttribute & 7;
}

void SetAttribute(nn::applet::CTR::AppletAttr attribute){
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

void SetHomeButtonState(nn::applet::CTR::HomeButtonState state){
    sHomeButtonState = state;
}

nn::applet::CTR::HomeButtonState GetHomeButtonState(){
    return (nn::applet::CTR::HomeButtonState)sHomeButtonState;
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

nn::applet::CTR::SleepNotificationState GetSleepNoticationState(){
    return (nn::applet::CTR::SleepNotificationState)sSleepNotificationState;
}

void SetSleepNotificationState(nn::applet::CTR::SleepNotificationState state){
    sSleepNotificationState = state;
}

nn::applet::CTR::TransitionType GetTransitionType(){
    return (nn::applet::CTR::TransitionType)sPrevTransitionType;
}

void SetTransitionType(nn::applet::CTR::TransitionType type){
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

nn::applet::CTR::HomeButtonState GetAbsoluteHomeButtonState(){
    nn::applet::CTR::sAbsoluteHomeButtonState;
}

void SetAbsoluteHomeButtonState(nn::applet::CTR::HomeButtonState state){
    nn::applet::CTR::sAbsoluteHomeButtonState = state;
}

void ClearAbsoluteHomeButtonState(){
    nn::applet::CTR::sAbsoluteHomeButtonState = 0;
}

nn::applet::CTR::OrderToCloseState GetOrderToCloseState(){
    return (nn::applet::CTR::OrderToCloseState)nn::applet::CTR::sOrderToCloseState;
}

void SetOrderToCloseState(nn::applet::CTR::OrderToCloseState state){
    nn::applet::CTR::sOrderToCloseState = state;
}

nn::applet::CTR::PowerButtonState GetPowerButtonState(){
    return (nn::applet::CTR::PowerButtonState)nn::applet::CTR::sPowerButtonState;
}

void SetPowerButtonState(nn::applet::CTR::PowerButtonState state){
    nn::applet::CTR::sPowerButtonState = state;
}

nn::applet::CTR::SleepSysState GetSleepSysState(){
    return (nn::applet::CTR::SleepSysState)nn::applet::CTR::sSleepSysState;
}

void SetSleepSysState(nn::applet::CTR::SleepSysState state){
    nn::applet::CTR::sSleepSysState = state;
}

void ClearSleepSysState(){
    nn::applet::CTR::sSleepSysState = 0;
}

void SetShutDownState(nn::applet::CTR::ShutdownState state){
    nn::applet::CTR::sShutdownState = state;
}

s8 IsActive(){
    return nn::applet::CTR::isActive;
}

s8 IsAppletMode(){
    return nn::applet::CTR::isAppletMode;
}

void SetActive(){
    nn::applet::CTR::isActive = 1;
}

void SetInactive(){
    nn::applet::CTR::isActive = 0;
}



}
}
}
}