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
    // TODO
}

CharacterCode ResFontBase::GetCharacterCode() const{
    // TODO
}

int ResFontBase::GetBaselinePos() const{
    // TODO
}

int ResFontBase::GetCellHeight() const{
    // TODO
}

int ResFontBase::GetCellWidth() const{
    // TODO
}

void ResFontBase::EnableLinearFilter(bool atSmall,bool atLarge){
    // TODO
}

bool ResFontBase::IsLinearFilterEnableAtSmall() const{
    // TODO
}

bool ResFontBase::IsLinearFilterEnableAtLarge() const{
    // TODO
}

u32 ResFontBase::GetTextureWrapFilterValue() const{
    // TODO
}

uint ResFontBase::FindGlyphIndex(uint code){
    // TODO
}
}
}