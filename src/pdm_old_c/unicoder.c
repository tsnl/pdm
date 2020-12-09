#include "unicoder.h"

#include "utf8proc/utf8proc.h"

#include "useful.h"


static int64_t predictSpaceForUtf32String_asUtf8();
static int64_t predictSpaceForUtf32CodePoint(int32_t codepoint);


Utf8String NewUtf8String(uint8_t* mov_buf, int64_t count) {
    Utf8String out;
    out.buf = mov_buf;
    out.count = count;
    return out;
}
Utf32String NewUtf32String(int32_t* mov_buf, int64_t count) {
    Utf32String out;
    out.buf = mov_buf;
    out.count = count;
    return out;
}

int64_t predictSpaceForUtf32String_asUtf8(Utf32String u32string) {
    int64_t predictedLen = 0;
    for (int64_t index = 0; index < u32string.count; index++) {
        int codepoint = u32string.buf[index];
        predictedLen += predictSpaceForUtf32CodePoint(codepoint);
    }
    return predictedLen;
}
int64_t predictSpaceForUtf32CodePoint(int32_t codepoint) {
    // from https://en.wikipedia.org/wiki/UTF-8
    // 0000 (0) to 007f (127): 1 byte
    // 0080 (128) to 07ff (2047): 2 bytes
    // 0800 (2048) to ffff (65535): 3 bytes
    // 10000 (65536) to 10ffff (1114111): 4 bytes
    if (codepoint < 0) return 0;
    if (codepoint < 0x0080) return 1;
    if (codepoint < 0x0800) return 2;
    if (codepoint < 0x8000) return 3;
    return 4;
}

Utf8String ConvertUtf32StringToUtf8String(Utf32String u32string) {
    // constructing an output:
    Utf8String out;
    out.count = predictSpaceForUtf32String_asUtf8(u32string);
    out.buf = malloc(out.count);
    
    // encoding:
    utf8proc_ssize_t offset = 0;
    for (int64_t index = 0; index < u32string.count; index++) {
        int codepoint = u32string.buf[index];
        
        // ignoring negative (invalid) characters:
        if (codepoint >= 0) {
            offset += utf8proc_encode_char(codepoint, out.buf+offset);
        }
    }
    COMPILER_ASSERT(offset == out.count, "predicted Utf32 space does not match received.");

    // returning:
    return out;
}
