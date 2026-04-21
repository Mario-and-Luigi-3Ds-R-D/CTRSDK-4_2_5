#pragma once

#include "nn/types.h"
#include "nn/font/font_Font.h"
#include "nn/font/font_Types.h"

namespace nn{
namespace font{
class ResFontBase : public Font{
protected:

typedef ushort GlyphIndex;

    void* mResource;
    FontInformation* mFontInfo;
    internal::TextureObject* mTexObjs;
    u32 mWrapFilter;
    mutable CharCode mLastCharCode;
    mutable GlyphIndex mLastGlyphIndex;
public:
    ResFontBase();
    virtual ~ResFontBase();
    virtual int GetWidth() const;
    virtual int GetHeight() const;
    virtual int GetAscent() const;
    virtual int GetDescent() const;
    virtual int GetMaxCharWidth() const;
    virtual Type GetType() const;
    virtual TexFmt GetTextureFormat() const;
    virtual int GetLineFeed() const;
    virtual const CharWidths GetDefaultCharWidths() const;
    virtual void SetLineFeed(int linefeed);
    virtual void SetDefaultCharWidths(const CharWidths& widths);
    virtual bool SetAlternateChar(CharCode code);
    virtual int GetCharWidth(CharCode code) const;
    virtual const CharWidths GetCharWidths(CharCode code) const;
    virtual void GetGlyph(Glyph* pGlyph,CharCode code) const;
    virtual bool HasGlyph(CharCode c) const;
    virtual CharacterCode GetCharacterCode() const;
    virtual int GetBaselinePos() const;
    virtual int GetCellHeight() const;
    virtual int GetCellWidth() const;
    virtual void EnableLinearFilter(bool atSmall,bool atLarge);
    virtual bool IsLinearFilterEnableAtSmall() const;
    virtual bool IsLinearFilterEnableAtLarge() const;
    virtual u32 GetTextureWrapFilterValue() const;
    uint FindGlyphIndex(uint code);
};

}
}