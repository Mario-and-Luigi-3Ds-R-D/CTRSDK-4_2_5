#pragma once

#ifdef NN_DEBUG
#define NN_DBG_PRINT_RESULT(exp)    ::nn::dbg::detail::PrintResult(exp)
#else
    #define NN_DBG_PRINT_RESULT(exp)    ((void)(exp))
#endif