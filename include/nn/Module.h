// Idea from Moddimations CTRSDK 2_4_1

#include "nn/util/detail/util_Symbol.h"

#define NN_MAKE_MODULE(Variable, Company, Module) \
    const char* Variable, __attribute__((section(".module_id"))) = "[SDK+" Company ":" Module "]"

#define NN_MAKE_MODULE_SDK(Variable, Module) \
    NN_MAKE_MODULE(Variable, "NINTENDO", Module)

#define NN_REFER_MODULE(Variable) \
    nnutilReferSymbol_(Variable)