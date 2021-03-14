#include "leetcode.h"
#include <cctype>
#include <tuple>
#include <utility>
#include <vector>

/*
 * 224. Basic Calculator
 *
 * https://leetcode-cn.com/problems/basic-calculator/
 *
 * Given a string s representing an expression, implement a basic calculator to evaluate it.
 *
 * Example 1:
 *
 * Input: s = "1 + 1"
 * Output: 2
 *
 *
 * Example 2:
 *
 * Input: s = " 2-1 + 2 "
 * Output: 3
 *
 *
 * Example 3:
 *
 * Input: s = "(1+(4+5+2)-3)+(6+8)"
 * Output: 23
 *
 *
 * Constraints:
 *
 *     1 <= s.length <= 3 * 105
 *     s consists of digits, '+', '-', '(', ')', and ' '.
 *     s represents a valid expression.
 *
 **/

class Solution {
public:
    int apply_op(const std::pair<int, char>& op, const int number) {
        assert(op.second == '+' || op.second == '-');
        if (op.second == '+') {
            return op.first + number;
        } else {
            return op.first - number;
        }
    }

    int calculate(std::string s) {
        assert(!s.empty());

        std::vector<std::pair<int, char>> ops = {{0, '+'}};

        int last_number = 0;
        for (std::size_t i = 0; i < s.size(); ++i) {
            if (s.at(i) == ' ') {
                continue;
            } else if (std::isdigit(s.at(i))) {
                last_number = last_number * 10 + (s.at(i) - '0');
            } else if (s.at(i) == '+' || s.at(i) == '-') {
                assert(!ops.empty());
                auto& last_op = ops.back();
                last_op.first = apply_op(last_op, last_number);
                last_op.second = s.at(i);
                last_number = 0;
            } else if (s.at(i) == '(') {
                assert(last_number == 0);
                ops.emplace_back(0, '+');
            } else if (s.at(i) == ')') {
                assert(!ops.empty());
                last_number = apply_op(ops.back(), last_number);
                ops.pop_back();
            } else {
                assert(false);
            }
        }

        assert(ops.size() == 1);
        return apply_op(ops.back(), last_number);
    }
};

TEST(Calculate, simple) {
    Solution solution;

    { // case1
        const std::string input = "0";
        const int output = solution.calculate(input);
        const int expect_output = 0;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    { // case1
        const std::string input = "1 + 1";
        const int output = solution.calculate(input);
        const int expect_output = 2;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    { // case1
        const std::string input = "21 + 1";
        const int output = solution.calculate(input);
        const int expect_output = 22;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    { // case1
        const std::string input = "1 + 1 - 3";
        const int output = solution.calculate(input);
        const int expect_output = -1;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    { // case1
        const std::string input = "(1 + (4 + 5 + 2) - 3) + (6 + 8)";
        const int output = solution.calculate(input);
        const int expect_output = 23;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
