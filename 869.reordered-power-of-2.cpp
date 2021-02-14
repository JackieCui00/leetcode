#include "leetcode.h"
#include <utility>

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

template<std::size_t N, std::size_t ...Is>
constexpr std::array<int64_t, N> generate_power_of_2_impl(std::index_sequence<Is...>) {
    return {(1l << Is)...};
}

template<std::size_t N>
constexpr std::array<int64_t, N> generate_power_of_2() {
    return generate_power_of_2_impl<N>(std::make_index_sequence<N>());
}

class Solution {
public:
    bool reorderedPowerOf2(int N) {
        auto power_of_2 = generate_power_of_2<33>();

        std::array<int, 10> numbers = {};
        int64_t max = 1;
        while (N != 0) {
            const int last = N % 10;
            assert(last < 10);
            numbers.at(last) += 1;

            N /= 10;
            max *= 10;
        }
        assert(max >= 10);

        const auto saved = numbers;
        for (int64_t expect : power_of_2) {
            if (expect >= max) {
                break;
            }
            if (expect < (max / 10) ) {
                continue;
            }
            numbers = saved;

            bool failed = false;
            while (expect != 0) {
                const int last = expect % 10;
                assert(last < 10);
                if (numbers.at(last) == 0) {
                    failed = true;
                    break;
                }
                assert(numbers.at(last) > 0);
                numbers.at(last) -= 1;

                expect /= 10;
            }
            if (failed) {
                continue;
            }
            for (const auto n : numbers) {
                if (n != 0) {
                    failed = true;
                    break;
                }
            }
            if (failed) {
                continue;
            }

            return true;
        }

        return false;
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
