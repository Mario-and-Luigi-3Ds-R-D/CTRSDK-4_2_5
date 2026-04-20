#pragma once

#include "nn/types.h"

namespace nn{
namespace font{
enum CharacterCode{
    CHARACTER_CODE_UNICODE = 1,
    CHARACTER_CODE_SJIS,
    CHARACTER_CODE_CP1252,
    CHARACTER_CODE_MAX
};

struct CharWidths{
    s8  left;
    u8  glyphWidth;
    s8  charWidth;
};


class CharStrmReader{
    friend class Font;
public:
    CharStrmReader(const CharStrmReader& rhs) : mCharStrm(rhs.mCharStrm), mReadFunc(rhs.mReadFunc){}
    ~CharStrmReader() {}

    void Set(const char* stream)
    { }
    void Set(const wchar_t* stream)
    { }

    const void* GetCurrentPos() const { return mCharStrm; }
    ushort Next() { return (this->*mReadFunc)(); }

private:
    typedef ushort (CharStrmReader::*ReadNextCharFunc)();

    const void*          mCharStrm;  // Current position in the character stream
    const ReadNextCharFunc mReadFunc; // Encoding-specific read function
    explicit CharStrmReader(ReadNextCharFunc func) : mCharStrm(NULL), mReadFunc(func)
    {}

    template <typename CharType>
    CharType GetChar(int offset = 0) const{
        return reinterpret_cast<const CharType*>(mCharStrm)[offset];
    }

    template <typename CharType>
    void StepStrm(int step = 1){
        reinterpret_cast<const CharType*&>(mCharStrm) += step;
    }

    ushort ReadNextCharUTF8();
    ushort ReadNextCharUTF16();
    ushort ReadNextCharCP1252();
    ushort ReadNextCharSJIS();
};

}
}