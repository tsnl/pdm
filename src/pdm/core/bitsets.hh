#ifndef INCLUDED__PDM__CORE__BITSETS_HH
#define INCLUDED__PDM__CORE__BITSETS_HH

namespace pdm {
    // exactly_1_bit_is_1_in_bitset returns true if bitset matches pattern
    // exactly1: "1" | "0" exactly1 | exaclty1 "0";
    template <typename T>
    bool exactly_1_bit_is_1_in_bitset(T bitset) {
        // e.g.: consider all 4 and last 3 bits as case (1) and case (2)
        // |1|1|0|0|
        // |1|0|1|1|
        //  ^-- does not become a 0 bc of carry
        //    ^-- becomes a 0 bc of carry, turning all right-0s into 1s
        return !(bitset & (bitset-1));
    }
}

#endif  // INCLUDED__PDM__CORE__BITSETS_HH