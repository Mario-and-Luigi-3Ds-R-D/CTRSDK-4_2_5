#pragma once

#include "nn/types.h"
#include "nn/font/font_ResFontBase.h"

namespace nn{
namespace font{
class ResFont : public ResFontBase{
public:
    ResFont();
    virtual ~ResFont();

    void RemoveResource();
    void* SetDrawBuffer(void*); // void-> TextureObject*
    void* SetResource();
};

}
}