#pragma once

#include "nn/types.h"

namespace nn{
namespace ro{
namespace detail{
namespace IsCodeAddress{

    class CodeChecker{
    public:
        CodeChecker();
        virtual bool oper(uint pOperator); // guessed name
    };
}
}
}
}