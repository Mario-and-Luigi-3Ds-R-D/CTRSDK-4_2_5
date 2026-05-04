#include <nn/err/CTR/err_Api.h>

namespace nn{
namespace err{
namespace CTR{
namespace{
void Throw(nn::err::CTR::FatalErrInfo* pInfo){

}

}

//void ThrowFatalErr(Result result, nnerrFatalErrType type, uptr pc){
/*    sFatalErrInfo.mRevisionHi = 0;
    sFatalErrInfo.mRevisionLo = 0xC449;
    sFatalErrInfo.mType = type;
    sFatalErrInfo.mResult = result;
    sFatalErrInfo.mPc = pc;*/
//}

void ThrowFatalErr(Result result, uptr pc){

}

void ThrowFatalErrAll(Result result, uptr pc) {
/*    sFatalErrInfo.mRevisionHi = 0;
    sFatalErrInfo.mRevisionLo = 0xC449;
    sFatalErrInfo.mType = 0;
    sFatalErrInfo.mResult = result;
    sFatalErrInfo.mPc = pc;
    CTR::Throw(&sFatalErrInfo);*/
}

}
}
}