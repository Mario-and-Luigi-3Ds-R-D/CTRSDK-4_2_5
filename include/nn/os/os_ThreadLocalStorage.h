#pragma once

#include <nn/types.h>
#include <nn/Result.h>

namespace nn{
namespace os{
    class ThreadLocalStorage{
    public:
        int mIndex;

        ~ThreadLocalStorage();
        void Finalize();
        static void ClearAllSlots();
    };

namespace{
    short sTLSMap;
}
}
}