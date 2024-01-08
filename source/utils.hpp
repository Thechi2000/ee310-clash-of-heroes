#pragma once
#include <nds.h>
#include <functional>
#include <set>

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

/**
 * Copies from one location to another.
 *
 * During the copy, if a bytes encountered is in the forbidden set,
 * it will be replaced by the last valid byte encountered.
 *
 * This is used when restricting the palette with Grit, since the generated bitmap
 * will still contain indexes outside of the palette range.
 *
 * @param dst where data will be copied to
 * @param src where data will be copied from
 * @param len number of bytes to copy
 * @param forbidden bytes to avoid
*/
static inline void cpy(void* dst, const void* src, size_t len, std::set<u8> forbidden) {
    struct Temp { u8 a, b; };
    u8 lastValidByte = 0;

    for (int i = 0; i < len / 2; ++i) {
        Temp tmp = ((Temp*)src)[i];
        if (forbidden.count(tmp.a) > 0) { tmp.a = lastValidByte; } else { lastValidByte = tmp.a; }
        if (forbidden.count(tmp.b) > 0) { tmp.b = lastValidByte; } else { lastValidByte = tmp.b; }
        ((u16*)dst)[i] = *((u16*)&tmp);
    }
}
