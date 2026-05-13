#include "nn/types.h"

namespace nn {
namespace snd {
namespace CTR {
class DspSnd{
public:
    void Finalize(bool);
};

namespace internal{
    extern DspSnd sDspSnd;
}
} // namespace CTR
} // namespace snd
} // namespace nn