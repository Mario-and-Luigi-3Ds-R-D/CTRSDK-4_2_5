#pragma once

namespace nn{
namespace util{
namespace ADLFireWall{

    template <typename T>
    struct NonCopyable{
    protected:
        NonCopyable();
        ~NonCopyable();
    
    private:
        NonCopyable(const NonCopyable*);
    }; // NonCopyable
    
}
}
}