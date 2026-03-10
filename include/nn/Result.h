#pragma once

#include "types.h"

struct Result {
private:
    u32 mResult;
public:
    Result() : mResult(0){
    };
    bool Failed() const{
        return mResult & 0x80000000;
    }
    bool Succeeded() const {
        return !Failed();
    }
    // Add description,modtype, etc later since github deleted my shit.
};