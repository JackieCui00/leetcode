#include "leetcode.h"
#include <deque>
#include <limits>

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
        int maxlen = 0;

        std::vector<int> maxlen_end;
        maxlen_end.resize(s.length(), 0);

        std::deque<int> stack;
        for (std::size_t i = 0; i < s.length(); ++i) {
            if (s.at(i) == '(') {
                stack.push_back(i);
                continue;
            }
            assert(s.at(i) == ')');

            if (stack.empty()) {
                continue;
            }

            const std::size_t closure_start = stack.back();
            stack.pop_back();
            assert(closure_start < i);
            int curlen = i - closure_start + 1;
            if (closure_start > 0) {
                curlen += maxlen_end.at(closure_start - 1);
            }
            maxlen_end.at(i) = curlen;

            maxlen = std::max(maxlen, curlen);
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
