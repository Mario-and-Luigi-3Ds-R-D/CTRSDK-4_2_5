#pragma once

#include "nn/types.h"
#include "nn/font/font_CharTypes.h"
#include "nn/font/font_Font.h"

namespace nn{
namespace font{
namespace internal{
class TextureObject{
    private:
    u32 mName;
    const Font* mpFont;
    uptr mpImage;
    TextureSize mSize;
    u8 mFormat;
    u8 rev[3];
};
}

struct FontWidth{
    ushort indexBegin;
    ushort indexEnd;
    FontWidth* pNext;
    CharWidths* GetWidthTable() const;
};

struct FontCodeMap{
    ushort ccodeBegin;
    ushort ccodeEnd;
    ushort mappingMethod;
    ushort reserved;
    FontCodeMap* pNext;
    ushort* GetMapInfo() const;
};

struct FontTextureGlyph{
    u8 cellWidth;
    u8 cellHeight;
    s8 baselinePos;
    u8 maxCharWidth;
    u32 sheetSize;
    ushort sheetNum;
    ushort sheetFormat;
    ushort sheetRow;
    ushort sheetLine;
    ushort sheetWidth;
    ushort sheetHeight;
    u8* sheetImage;
};

struct FontInformation{
    u8 fontType;
    s8 linefeed;
    ushort alterCharIndex;
    CharWidths defaultWidth;
    u8 characterCode;
    FontTextureGlyph* pGlyph;
    FontWidth* pWidth;
    FontCodeMap* pMap;
    u8 height;
    u8 width;
    u8 ascent;
    u8 padding_[1];
};
}
}