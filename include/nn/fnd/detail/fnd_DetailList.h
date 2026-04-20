#pragma once

#include "nn/fnd/detail/fnd_DetailHeapHead.h"

namespace nn{
namespace fnd{
namespace detail{

    void RemoveListObject(NNSFndList* list, void* object); // 100%
    void AppendListObject(NNSFndList* list, void* object); // 100%
    void* GetNextListObject(NNSFndList* list, void* object); // 100%
    void InitList(NNSFndList* link, ushort offset); // 100%

}
}
}