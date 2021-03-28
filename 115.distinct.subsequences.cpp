#include "leetcode.h"

/*
 * 115. Distinct Subsequences
 *
 * https://leetcode-cn.com/problems/distinct-subsequences/
 *
 * Given two strings s and t, return the number of distinct subsequences of s which equals t.
 *
 * A string's subsequence is a new string formed from the original string by deleting some (can be none) of the characters without disturbing the remaining characters' relative positions. (i.e., "ACE" is a subsequence of "ABCDE" while "AEC" is not).
 *
 * It is guaranteed the answer fits on a 32-bit signed integer.
 *
 *
 * Example 1:
 *
 * Input: s = "rabbbit", t = "rabbit"
 * Output: 3
 * Explanation:
 * As shown below, there are 3 ways you can generate "rabbit" from S.
 * rabbbit
 * rabbbit
 * rabbbit
 *
 *
 * Example 2:
 *
 * Input: s = "babgbag", t = "bag"
 * Output: 5
 * Explanation:
 * As shown below, there are 5 ways you can generate "bag" from S.
 * babgbag
 * babgbag
 * babgbag
 * babgbag
 * babgbag
 *
 *
 * Constraints:
 *
 *     0 <= s.length, t.length <= 1000
 *     s and t consist of English letters.
 *
 **/

class Solution {
public:
    int numDistinct(std::string s, std::string t) {
        if (s.size() < t.size()) {
            return 0;
        }

        std::vector<std::vector<uint64_t>> result;
        result.resize(s.size() + 1);
        for (std::size_t i = 0; i <= s.size(); ++i) {
            result.at(i).resize(t.size() + 1, 0);
            result.at(i).at(0) = 1;
        }

        for (std::size_t i = 1; i <= s.size(); ++i) {
            for (std::size_t j = 1; j <= t.size(); ++j) {
                result.at(i).at(j) = result.at(i - 1).at(j);
                if (s.at(i - 1) == t.at(j - 1)) {
                    result.at(i).at(j) += result.at(i - 1).at(j - 1);
                }
            }
        }

        return result.at(s.size()).at(t.size());
    }
};

TEST(NumDistinct, simple) {
    Solution solution;

    {
        const std::string s = "rabbbit";
        const std::string t = "rabbit";

        const int output = solution.numDistinct(s, t);
        const int expect_output = 3;

        print(std::make_tuple(s, t), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const std::string s = "babgbag";
        const std::string t = "bag";

        const int output = solution.numDistinct(s, t);
        const int expect_output = 5;

        print(std::make_tuple(s, t), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
