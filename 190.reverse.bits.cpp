#include "leetcode.h"

/*
 * 190. Reverse Bits
 *
 * Reverse bits of a given 32 bits unsigned integer.
 *
 * Note:
 *     Note that in some languages such as Java, there is no unsigned integer type. In this case, both input and output will be given as a signed integer type. They should not affect your implementation, as the integer's internal binary representation is the same, whether it is signed or unsigned.
 *     In Java, the compiler represents the signed integers using 2's complement notation. Therefore, in Example 2 above, the input represents the signed integer -3 and the output represents the signed integer -1073741825.
 *
 * Follow up:
 *
 * If this function is called many times, how would you optimize it?
 *
 *
 * Example 1:
 * Input: n = 00000010100101000001111010011100
 * Output:    964176192 (00111001011110000010100101000000)
 * Explanation: The input binary string 00000010100101000001111010011100 represents the unsigned integer 43261596, so return 964176192 which its binary representation is 00111001011110000010100101000000.
 *
 * Example 2:
 *
 * Input: n = 11111111111111111111111111111101
 * Output:   3221225471 (10111111111111111111111111111111)
 * Explanation: The input binary string 11111111111111111111111111111101 represents the unsigned integer 4294967293, so return 3221225471 which its binary representation is 10111111111111111111111111111111.
 *
 *
 * Constraints:
 *
 *     The input must be a binary string of length 32
 *
 **/

template<uint8_t N>
struct ReverseBitsTmpl {
    constexpr static uint8_t value = ((ReverseBitsTmpl< (N >> 1) >::value) >> 1) + ((N & 0x1) << 7);
};

template<>
struct ReverseBitsTmpl<0> {
    constexpr static uint8_t value = 0;
};

template<std::size_t... Indices>
constexpr auto make_array_helper(std::index_sequence<Indices...>) {
    return std::array<uint8_t, sizeof...(Indices)>({ReverseBitsTmpl<Indices>::value...});
}

static std::array<uint8_t, 256> s_reverse_bits_table = make_array_helper(std::make_index_sequence<256>{});

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        return reverseBitsV2(n);
    }

    uint32_t reverseBitsV1(uint32_t n) {
        uint8_t* pnum = reinterpret_cast<uint8_t*>(&n);
        return (s_reverse_bits_table.at(*pnum) << 24)
            + (s_reverse_bits_table.at(*(pnum + 1)) << 16)
            + (s_reverse_bits_table.at(*(pnum + 2)) << 8)
            + s_reverse_bits_table.at(*(pnum + 3));
    }

    uint32_t reverseBitsV2(uint32_t n) {
        /*
         * 若要翻转一个二进制串，可以将其均分成左右两部分，对每部分递归执行翻转操作，然后将左半部分拼在右半部分的后面，即完成了翻转。
         *
         * 由于左右两部分的计算方式是相似的，利用位掩码和位移运算，我们可以自底向上地完成这一分治流程。
         *
         * 对于递归的最底层，我们需要交换所有奇偶位：
         *      取出所有奇数位和偶数位；
         *      将奇数位移到偶数位上，偶数位移到奇数位上。
         * 类似地，对于倒数第二层，每两位分一组，按组号取出所有奇数组和偶数组，然后将奇数组移到偶数组上，偶数组移到奇数组上。以此类推。
         *
         **/

        constexpr uint32_t M1 = 0b01010101010101010101010101010101;
        constexpr uint32_t M2 = 0b00110011001100110011001100110011;
        constexpr uint32_t M4 = 0b00001111000011110000111100001111;
        constexpr uint32_t M8 = 0b00000000111111110000000011111111;

        n = ((n >> 1) & M1) | ((n & M1) << 1);
        n = ((n >> 2) & M2) | ((n & M2) << 2);
        n = ((n >> 4) & M4) | ((n & M4) << 4);
        n = ((n >> 8) & M8) | ((n & M8) << 8);

        return n >> 16 | n << 16;
    }
};

TEST(ReverseBits, simple) {
    Solution solution;

    {
        const uint32_t input = 0b00000010100101000001111010011100;
        const uint32_t output = solution.reverseBits(input);
        const uint32_t expect_output = 964176192;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const uint32_t input = 0b11111111111111111111111111111101;
        const uint32_t output = solution.reverseBits(input);
        const uint32_t expect_output = 3221225471;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
