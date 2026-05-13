#pragma once

#define NN_UTIL_REFER_SYMBOL(symbol)    nnutilReferSymbol_(NULL, &(symbol))

extern "C"{

void nnutilReferSymbol_(const char* pSym);
} // Extern "C   "
