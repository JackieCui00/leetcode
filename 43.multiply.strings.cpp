#include "leetcode.h"

/*
 * 43. Multiply Strings
 *
 * https://leetcode-cn.com/problems/multiply-strings/
 *
 * Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.
 *
 * Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.
 *
 *
 *Example 1:
 *
 *Input: num1 = "2", num2 = "3"
 *Output: "6"
 *
 *
 *Example 2:
 *
 *Input: num1 = "123", num2 = "456"
 *Output: "56088"
 *
 *
 *Constraints:
 *
 *    1 <= num1.length, num2.length <= 200
 *    num1 and num2 consist of digits only.
 *    Both num1 and num2 do not contain any leading zero, except the number 0 itself.
 *
 **/

class Solution {
public:
    std::string multiply(std::string num1, std::string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }

        std::vector<int> result(num1.size() + num2.size(), 0);

        std::size_t add_idx = result.size() - 1;
        for (auto iter1 = num1.rbegin(); iter1 != num1.rend(); ++iter1) {
            const int n1 = *iter1 - '0';
            assert(n1 < 10);

            const std::size_t saved_add_idx = add_idx;
            for (auto iter2 = num2.rbegin(); iter2 != num2.rend(); ++iter2) {
                const int n2 = *iter2 - '0';
                result.at(add_idx) += n1 * n2;

                add_idx -= 1;
            }

            assert(saved_add_idx != 0);
            add_idx = saved_add_idx - 1;
        }

        int extra = 0;
        for (std::size_t i = result.size() - 1; i > 0; --i) {
            const int saved = result.at(i);
            result.at(i) = (saved + extra) % 10;
            extra = (saved + extra) / 10;
        }
        assert(extra < 10);
        result.at(0) = extra;

        std::string result_str;
        std::size_t idx = 0;
        while (result.at(idx) == 0) {
            ++idx;
        }
        result_str.resize(result.size() - idx);
        for (std::size_t i = 0; idx < result.size(); ++i, ++idx) {
            result_str.at(i) = result.at(idx) + '0';
        }

        return result_str;
    }
};

TEST(MultiplyStrings, simple) {
    Solution solution;

    {
        const std::string num1 = "2";
        const std::string num2 = "3";
        const std::string result = solution.multiply(num1, num2);
        const std::string expect_result = "6";

        print(std::make_tuple(num1, num2), result, expect_result);

        EXPECT_EQ(result, expect_result);
    }

    {
        const std::string num1 = "123";
        const std::string num2 = "456";
        const std::string result = solution.multiply(num1, num2);
        const std::string expect_result = "56088";

        print(std::make_tuple(num1, num2), result, expect_result);

        EXPECT_EQ(result, expect_result);
    }

    {
        const std::string num1 = "999";
        const std::string num2 = "999";
        const std::string result = solution.multiply(num1, num2);
        const std::string expect_result = "998001";

        print(std::make_tuple(num1, num2), result, expect_result);

        EXPECT_EQ(result, expect_result);
    }
}

DEFINE_MAIN


