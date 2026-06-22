#include <nn/err/CTR/err_Api.h>
#include <nn/dbg/dbg_Break.h>
#include <nn/dbg/dbg_DebugString.h>

using namespace nn::dbg::detail;

namespace nn{
namespace err{
namespace CTR{
namespace{
static FatalErrInfo sFatalErrInfo;

Result InitializeFatalErrSession(){
    Result res;
    
}

void Throw(nn::err::CTR::FatalErrInfo* pInfo){
    
}

}

void ThrowFatalErr(Result result, nnerrFatalErrType type, uptr pc){
    nnResult res_local; result = res_local;
    #ifdef NN_DEBUG
        TPrintf("----\n");
        TPrintf("Fatal Error occured. (pc=0x%08x)\n", pc);
        PrintResult(res_local);
    #endif
    sFatalErrInfo.mRevisionHi = 0;
    sFatalErrInfo.mRevisionLo = 0xc449;
    sFatalErrInfo.mType = type;
    sFatalErrInfo.mResult.value = res_local.value;
    sFatalErrInfo.mPc = pc;
    CTR::Throw(&sFatalErrInfo);
}

void ThrowFatalErr(Result result, uptr pc){
    Result res; Result::Level lev = res.Result::GetLevel();
    if((lev != res.LEVEL_INFO) && (lev != res.LEVEL_STATUS)){
        ThrowFatalErr(result, NN_ERR_FATAL_TYPE_SYSTEM_COMMON, pc);
    }
}

void ThrowFatalErrAll(Result result, uptr pc){
    ThrowFatalErr(result, NN_ERR_FATAL_TYPE_SYSTEM_COMMON, pc);
}

}
}
}