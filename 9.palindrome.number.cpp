#include "leetcode.h"

/*
 *
 * 9. Palindrome Number
 *
 * Given an integer x, return true if x is palindrome integer.
 *
 * An integer is a palindrome when it reads the same backward as forward. For example, 121 is palindrome while 123 is not.
 *
 *
 * Example 1:
 *
 * Input: x = 121
 * Output: true
 *
 *
 * Example 2:
 *
 * Input: x = -121
 * Output: false
 * Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
 *
 *
 * Example 3:
 *
 * Input: x = 10
 * Output: false
 * Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
 *
 *
 * Example 4:
 *
 * Input: x = -101
 * Output: false
 *
 *
 * Constraints:
 *    -231 <= x <= 231 - 1
 *
 * Follow up: Could you solve it without converting the integer to a string?
 *
 **/

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }

        uint64_t n1 = x;
        uint64_t n2 = 0;
        while (x != 0) {
            n2 = n2 * 10 + x % 10;
            x /= 10;
        }

        return n1 == n2;
    }
};

TEST(IsPalindrome, simple) {
    Solution solution;

    {
        const int input = 121;
        const bool output = solution.isPalindrome(input);
        constexpr bool expect_output = true;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const int input = -121;
        const bool output = solution.isPalindrome(input);
        constexpr bool expect_output = false;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const int input = 10;
        const bool output = solution.isPalindrome(input);
        constexpr bool expect_output = false;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const int input = -101;
        const bool output = solution.isPalindrome(input);
        constexpr bool expect_output = false;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
