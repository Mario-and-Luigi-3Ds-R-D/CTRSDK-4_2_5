// Filename: os_WaitableCounter.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include "nn/os/os_WaitableCounter.h"
#include "nn/svc/svc_Api.h"
#include "nn/Assert.h"

namespace nn{
namespace os{

nnHandle WaitableCounter::sHandle = {0};


void WaitableCounter::Initialize(){
    if(sHandle.value == INVALID_HANDLE_VALUE.value){
        Handle h;
        Result ret = nn::svc::CreateAddressArbiter(&h);
        NN_TASSERT_(ret.IsSuccess());
        if(ret.IsSuccess()){
            sHandle = h;
        }
    }
}

} // os
} // nn