#include "leetcode.h"

/*
 * [32] Longest Valid Parentheses
 *
 * https://leetcode-cn.com/problems/longest-valid-parentheses/
 *
 * Given a string containing just the characters '(' and ')', find the length
 * of the longest valid (well-formed) parentheses substring.
 *
 * Example 1:
 *
 * Input: "(()"
 * Output: 2
 * Explanation: The longest valid parentheses substring is "()"
 *
 *
 * Example 2:
 *
 * Input: ")()())"
 * Output: 4
 * Explanation: The longest valid parentheses substring is "()()"
 *
 */

class Solution {
public:
    int longestValidParentheses(std::string s) {
        std::vector<int> stack;
        stack.resize(s.length());

        int left=-1;
        int maxlen=0;
        int curlen=0;

        int head = 0;
        for (std::size_t i = 0; i < s.length(); ++i) {
            if (s.at(i) == '(') {
                stack[head++] = i;
            }

            if (0 == head) {
                left = i;
                continue;
            }

            head --;

            if (0 == head) {
                curlen = i - left;
            } else {
                curlen = i - stack[head-1];
            }

            maxlen = maxlen>curlen ? maxlen : curlen;
        }

        return maxlen;

    }
};

TEST(LongestValidParentheses, simple) {
    Solution solution;

    {
        const std::string input = "(()";
        const int output = solution.longestValidParentheses(input);
        constexpr int expect_output = 2;

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        const std::string input = ")()())";
        const int output = solution.longestValidParentheses(input);
        constexpr int expect_output = 4;

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
