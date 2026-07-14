#pragma once

#define NN_UTIL_REFER_SYMBOL(symbol)    nnutilReferSymbol_(NULL, &(symbol))

#ifdef __cplusplus
extern "C" {
#endif

void nnutilReferSymbol_(const void*, ...);

#ifdef __cplusplus
}
#endif

