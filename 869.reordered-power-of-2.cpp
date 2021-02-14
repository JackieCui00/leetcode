#include "leetcode.h"
#include <ios>

/*
 * https://leetcode-cn.com/problems/reordered-power-of-2/
 *
 * Starting with a positive integer N, we reorder the digits in any order (including the original order) such that the leading digit is not zero.
 * Return true if and only if we can do this in a way such that the resulting number is a power of 2.
 *
 *
 * Example 1:
 * Input: 1
 * Output: true
 *
 *
 * Example 2:
 * Input: 10
 * Output: false
 *
 *
 * Example 3:
 * Input: 16
 * Output: true
 *
 *
 * Example 4:
 * Input: 24
 * Output: false
 *
 *
 * Example 5:
 * Input: 46
 * Output: true
 *
 *
 * Note:
 *     1 <= N <= 10^9
 **/

class Solution {
public:
    bool reorderedPowerOf2(int N) {

    }
};

TEST(ReorderedPowerOf2, simple) {
    Solution solution;

    std::cout << std::boolalpha;

    {
        int input = 1;
        const bool output = solution.reorderedPowerOf2(input);
        constexpr bool expect_output = true;

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        int input = 10;
        const bool output = solution.reorderedPowerOf2(input);
        constexpr bool expect_output = false;

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        int input = 16;
        const bool output = solution.reorderedPowerOf2(input);
        constexpr bool expect_output = true;

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        int input = 24;
        const bool output = solution.reorderedPowerOf2(input);
        constexpr bool expect_output = false;

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        int input = 46;
        const bool output = solution.reorderedPowerOf2(input);
        constexpr bool expect_output = true;

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
