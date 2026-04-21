#include <nn/err/CTR/err_FatalErr.h>

namespace nn{
namespace err{
namespace CTR{
namespace{

//FatalErrInfo sFatalErrInfo = { 0 };

void Throw(nn::err::CTR::FatalErrInfo* pInfo){

}

}

void ThrowFatalErr(Result pResult, uptr pc){

}
void ThrowFatalErrAll(Result result, uptr pc) {
//    sFatalErrInfo.mRevisionHi = 0;
//    sFatalErrInfo.mRevisionLo = 0xC449;
//    sFatalErrInfo.mType = 0;
//    sFatalErrInfo.mPc = pc;
//    sFatalErrInfo.mResult = result;
//    CTR::Throw(&sFatalErrInfo);
}

}
}
}