#pragma once

namespace nn {
namespace math {
    
    struct VEC2{
    public:
        float x;
        float y;
    };

    static const VEC2& Zero(){

    static const VEC2 zero(0.0f, 0.0f);
    return zero;
}

    //
    static const VEC2& One(){

    static const VEC2 one(1.0f, 1.0f);
    return one;
}

}
}