#pragma once
#include <nds.h>
#include <functional>

#include "time.hpp"

struct Vector {
    int x, y;
};

struct Sprite {
    void* data;
    uint32_t length;
};

#define TO_BE_IMPLEMENTED() assert(0)

#define IN_RANGE(x, min, max) ((min) <= (x) && (x) <= (max))

static inline void mdCopy(void* dst, const void* src, size_t len, std::function<u8(u8, size_t, u8*)> modifier = [](u8 a, size_t i, u8* array) {return a;}) {
    struct Temp { u8 a, b; };

    for (int i = 0; i < len / 2; ++i) {
        Temp tmp = ((Temp*)src)[i];

        tmp.a = modifier(tmp.a, (size_t)(2 * i), (u8*)src);
        tmp.b = modifier(tmp.b, (size_t)(2 * i + 1), (u8*)src);

        ((u16*)dst)[i] = *((u16*)&tmp);
    }
}
