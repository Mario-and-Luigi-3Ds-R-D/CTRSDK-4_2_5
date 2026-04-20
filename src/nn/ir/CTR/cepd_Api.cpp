#include <nn/ir/CTR/cepd_Api.h>

namespace nn{
namespace ir{
namespace CTR{

CepdStatus CepdGetStatus(){
    return (CepdStatus)cepdStatus;
}

}
}
}