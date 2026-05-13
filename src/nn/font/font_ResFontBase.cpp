#include <nn/font/font_ResFontBase.h>

namespace nn{
namespace font{
ResFontBase::ResFontBase(){
    this->mResource = 0;
    this->mFontInfo = 0;
    this->mTexObjs = 0;
    this->mLastCharCode = 0;
    this->mLastGlyphIndex = 0;
    this->mWrapFilter = 0;
}

ResFontBase::~ResFontBase(){
}

int ResFontBase::GetWidth() const{
    return this->mFontInfo[0].width;
}

int ResFontBase::GetHeight() const{
    return this->mFontInfo[0].height;
}

int ResFontBase::GetAscent() const{
    return this->mFontInfo[0].ascent;
}

int ResFontBase::GetDescent() const{
    return this->mFontInfo[0].height - this->mFontInfo[0].width;
}

int ResFontBase::GetMaxCharWidth() const{
    return this->mFontInfo[0].defaultWidth.charWidth;
}

Type ResFontBase::GetType() const{
    return TYPE_RESOURCE;
}

TexFmt ResFontBase::GetTextureFormat() const{
    return this->mFontInfo[0].pGlyph->sheetFormat;
}

int ResFontBase::GetLineFeed() const{
    return this->mFontInfo[0].linefeed;
}

const CharWidths ResFontBase::GetDefaultCharWidths() const{
    return this->mFontInfo[0].defaultWidth;
}

void ResFontBase::SetLineFeed(int linefeed){
    this->mFontInfo[0].linefeed = linefeed;
}
// COULD BE NON MATCH
void ResFontBase::SetDefaultCharWidths(const CharWidths& widths){
    this->mFontInfo[0].defaultWidth = widths;
}

bool ResFontBase::SetAlternateChar(CharCode code) {
    u32 glyphIndex = this->ResFontBase::FindGlyphIndex((uint)code);
    if (glyphIndex != 0xffff) {
        this->mFontInfo[0].alterCharIndex = (u16)glyphIndex;
        return true;
    }
    return false;
}

int ResFontBase::GetCharWidth(CharCode code) const {
    return this->GetCharWidth(code);
}

const CharWidths ResFontBase::GetCharWidths(CharCode code) const{
    // TODO
}

void ResFontBase::GetGlyph(Glyph* pGlyph,CharCode code) const{
    // TODO
}

bool ResFontBase::HasGlyph(CharCode code) const {
    return FindGlyphIndex(code) != 0xffff;
}

CharacterCode ResFontBase::GetCharacterCode() const{
    this->mFontInfo[0].characterCode;
}

int ResFontBase::GetBaselinePos() const{
    return this->mFontInfo[0].linefeed;
}

int ResFontBase::GetCellHeight() const{
    return this->mFontInfo[0].pGlyph->cellHeight;
}

int ResFontBase::GetCellWidth() const{
    return this->mFontInfo[0].pGlyph->cellWidth;
}

void ResFontBase::EnableLinearFilter(bool atSmall,bool atLarge){

}

bool ResFontBase::IsLinearFilterEnableAtSmall() const{
    return (this->mWrapFilter & 4) >> 2;
}

bool ResFontBase::IsLinearFilterEnableAtLarge() const{
    return (this->mWrapFilter & 2) >> 1;
}

u32 ResFontBase::GetTextureWrapFilterValue() const{
    return this->mWrapFilter;
}

uint ResFontBase::FindGlyphIndex(CharCode code) const{
    return this->mFontInfo[0].pGlyph->sheetNum;
}
}
}