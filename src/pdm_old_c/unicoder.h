#ifndef INCLUDED_UNICODER_H
#define INCLUDED_UNICODER_H

#include <stdint.h>

typedef struct Utf8String Utf8String; 
typedef struct Utf32String Utf32String;

struct Utf8String {
    int8_t* buf;
    int64_t count;
};
struct Utf32String {
    int32_t* buf;
    int64_t count;
};

Utf8String NewUtf8String(uint8_t* mov_buf, int64_t count);
Utf32String NewUtf32String(int32_t* mov_buf, int64_t count);

Utf8String ConvertUtf32StringToUtf8String(Utf32String u32string);

#endif  // INCLUDED_UNICODER_H
