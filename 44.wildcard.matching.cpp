#include "leetcode.h"

/*
 * 44. Wildcard Matching
 *
 * https://leetcode-cn.com/problems/wildcard-matching/
 *
 * Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:
 *
 *     '?' Matches any single character.
 *     '*' Matches any sequence of characters (including the empty sequence).
 *
 * The matching should cover the entire input string (not partial).
 *
 *
 * Example 1:
 *
 * Input: s = "aa", p = "a"
 * Output: false
 * Explanation: "a" does not match the entire string "aa".
 *
 *
 * Example 2:
 *
 * Input: s = "aa", p = "*"
 * Output: true
 * Explanation: '*' matches any sequence.
 *
 *
 * Example 3:
 *
 * Input: s = "cb", p = "?a"
 * Output: false
 * Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
 *
 *
 * Example 4:
 *
 * Input: s = "adceb", p = "*a*b"
 * Output: true
 * Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
 *
 *
 * Example 5:
 *
 * Input: s = "acdcb", p = "a*c?b"
 * Output: false
 *
 *
 * Constraints:
 *
 *     0 <= s.length, p.length <= 2000
 *     s contains only lowercase English letters.
 *     p contains only lowercase English letters, '?' or '*'.
 *
 **/

class Solution {
public:
    bool isMatch(std::string s, std::string p) {
        std::vector<std::vector<bool>> results;
        results.resize(s.size() + 1);
        for (auto& v : results) {
            v.resize(p.size() + 1);
            v[0] = false;
        }
        results[0][0] = true;
        for (std::size_t i = 1; i < results[0].size(); ++i) {
            results[0][i] = results[0][i - 1] && (p[i - 1] == '*');
        }

        for (std::size_t i = 1; i <= s.size(); ++i) {
            const char s_c = s[i - 1];
            for (std::size_t j = 1; j <= p.size(); ++j) {
                const char p_c = p[j - 1];

                if (p_c == s_c || p_c == '?') {
                    results[i][j] = results[i - 1][j - 1];
                } else if (p_c == '*') {
                    results[i][j] = results[i][j - 1] || results[i - 1][j];
                } else {
                    results[i][j] = false;
                }

                // std::cout << "results:" << results << std::endl;
            }
        }

        return results[s.size()][p.size()];
    }
};

TEST(WildcardMatching, simple) {
    Solution solution;

    std::cout << std::boolalpha;
    {
        const std::string s = "aa";
        const std::string p = "a";
        const bool output = solution.isMatch(s, p);

        const bool expect_output = false;

        print(std::make_tuple(s, p), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const std::string s = "aa";
        const std::string p = "*";
        const bool output = solution.isMatch(s, p);

        const bool expect_output = true;

        print(std::make_tuple(s, p), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const std::string s = "cb";
        const std::string p = "?a";
        const bool output = solution.isMatch(s, p);

        const bool expect_output = false;

        print(std::make_tuple(s, p), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const std::string s = "adceb";
        const std::string p = "*a*b";
        const bool output = solution.isMatch(s, p);

        const bool expect_output = true;

        print(std::make_tuple(s, p), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const std::string s = "acdcb";
        const std::string p = "a*c?b";
        const bool output = solution.isMatch(s, p);

        const bool expect_output = false;

        print(std::make_tuple(s, p), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
