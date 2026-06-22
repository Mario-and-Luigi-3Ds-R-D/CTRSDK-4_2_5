#pragma once

extern "C"{
    __asm void nnnstdMemCpy (void* pOut, const void* pIn, size_t size);
    __asm void nnnstdMemMove(void* pOut, void* pIn, size_t size);
}
