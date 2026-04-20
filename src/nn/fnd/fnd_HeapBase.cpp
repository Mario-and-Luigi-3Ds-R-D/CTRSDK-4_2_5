#include <nn/fnd/fnd_HeapBase.h>

namespace nn{
namespace fnd{

void HeapBase::FillMemory32(uptr begin, uptr end, bit32 v){
    bit32** q;
    uptr var1;
    uptr begin_local;
    uptr end_local;

    begin_local = begin;
    if(begin != end){
        do{
            var1 = begin_local + 4;
            *(bit32*)begin_local = v;
            begin_local = var1;
        } while (var1 != end);
    }
}

}
}