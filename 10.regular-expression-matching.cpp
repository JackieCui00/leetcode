#include "leetcode.h"

/*
 * https://leetcode-cn.com/problems/regular-expression-matching/
 *
 * Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*' where:
 *
 *     '.' Matches any single character.​​​​
 *     '*' Matches zero or more of the preceding element.
 *
 * The matching should cover the entire input string (not partial).
 *
 *
 *
 * Example 1:
 *
 * Input: s = "aa", p = "a"
 * Output: false
 * Explanation: "a" does not match the entire string "aa".
 *
 * Example 2:
 *
 * Input: s = "aa", p = "a*"
 * Output: true
 * Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
 *
 * Example 3:
 *
 * Input: s = "ab", p = ".*"
 * Output: true
 * Explanation: ".*" means "zero or more (*) of any character (.)".
 *
 * Example 4:
 *
 * Input: s = "aab", p = "c*a*b"
 * Output: true
 * Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
 *
 * Example 5:
 *
 * Input: s = "mississippi", p = "mis*is*p*."
 * Output: false
 *
 *
 *
 * Constraints:
 *
 *     0 <= s.length <= 20
 *     0 <= p.length <= 30
 *     s contains only lowercase English letters.
 *     p contains only lowercase English letters, '.', and '*'.
 *     It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.
 *
 */

class Solution {
public:
    bool isMatch(std::string s, std::string p) {
        return isMatch_v3(s, p);
    }

    bool isMatch_v1(std::string s, std::string p) {
        if (p.empty()) return s.empty();

        if (p.size() >= 2 && p.at(1) == '*') {
            std::size_t i = 0;
            while (i <= s.size()) {
                if (isMatch(s.substr(i), p.substr(2))) {
                    return true;
                }
                if (i == s.size()) break;
                if (p.at(0) == '.' || s.at(i) == p.at(0)) {
                    ++i;
                } else {
                    break;
                }
            }
        }

        if (s.empty()) return p.empty();

        if (p.at(0) == '.' || s.at(0) == p.at(0)) {
            if (isMatch(s.substr(1), p.substr(1))) {
                return true;
            }
        }

        return false;
    }

    bool isMatch_v2(const char* s, const char* p) {
        if (p[0] == '\0') return s[0] == '\0';
        if (s[0] == '\0') {
            while (p[0] != '\0' && p[1] == '*') {
                p += 2;
            }
            return p[0] == '\0';
        }
        // from now: s and p is not empty

        if (p[0] != '\0' && p[1] == '*') {
            std::size_t i = 0;
            while (true) {
                if (isMatch_v2(s + i, p + 2)) {
                    return true;
                }
                if (s[i] == '\0') {
                    break;
                }
                if (p[0] == '.' || s[i] == p[0]) {
                    ++i;
                    continue;
                }
                break;
            }
        }

        if (p[0] == '.' || s[0] == p[0]) {
            if (isMatch_v2(s + 1, p + 1)) {
                return true;
            }
        }

        return false;
    }

    bool CharMatch(const char s, const char p) {
        return (s == p) || (p == '.');
    }

    bool isMatch_v3(const std::string& str, const std::string& to_match) {
        const std::size_t str_length = str.size();
        const std::size_t match_length = to_match.size();

        std::vector<std::vector<bool>> matrix;
        matrix.resize(str_length + 1);
        matrix.at(0).resize(match_length + 1);
        matrix.at(0).at(0) = true;
        for (std::size_t i = 0; i < str_length; ++i) {
            matrix.at(i + 1).resize(match_length + 1);
            matrix.at(i + 1).at(0) = false;
        }
        for (std::size_t j = 0; j < match_length; ++j) {
            if (j % 2 == 0) {
                matrix.at(0).at(j + 1) = false;
            } else {
                matrix.at(0).at(j + 1) = (to_match.at(j) == '*') && matrix.at(0).at(j - 1);
            }
        }

        for (std::size_t i = 0; i < str_length; ++i) {
            for (std::size_t j = 0; j < match_length; ++j) {
                if (to_match.at(j) != '*') {
                    matrix.at(i + 1).at(j + 1) = matrix.at(i).at(j) && CharMatch(str.at(i), to_match.at(j));
                } else {
                    assert(j > 0);
                    if (CharMatch(str.at(i), to_match.at(j - 1))) {
                        matrix.at(i + 1).at(j + 1) = matrix.at(i).at(j + 1) || matrix.at(i + 1).at(j - 1);
                    } else {
                        matrix.at(i + 1).at(j + 1) = matrix.at(i + 1).at(j - 1);
                    }
                }
            }
        }

        return matrix.at(str_length).at(match_length);
    }

};

TEST(RegularExpressionMatching, simple) {
    Solution solution;

    std::cout << std::boolalpha;
    {
        std::string s = "aa";
        std::string p = "a";
        const bool output = solution.isMatch(s, p);
        constexpr bool expect_output = false;
        print(std::make_tuple(s, p), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
    {
        std::string s = "aa";
        std::string p = "a*";
        const bool output = solution.isMatch(s, p);
        constexpr bool expect_output = true;
        print(std::make_tuple(s, p), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
    {
        std::string s = "ab";
        std::string p = "a.";
        const bool output = solution.isMatch(s, p);
        constexpr bool expect_output = true;
        print(std::make_tuple(s, p), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
    {
        std::string s = "ab";
        std::string p = ".*";
        const bool output = solution.isMatch(s, p);
        constexpr bool expect_output = true;
        print(std::make_tuple(s, p), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
    {
        std::string s = "aab";
        std::string p = "c*a*b";
        const bool output = solution.isMatch(s, p);
        constexpr bool expect_output = true;
        print(std::make_tuple(s, p), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
    {
        std::string s = "mississippi";
        std::string p = "mis*is*p*.";
        const bool output = solution.isMatch(s, p);
        constexpr bool expect_output = false;
        print(std::make_tuple(s, p), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
    {
        std::string s = "aaa";
        std::string p = "ab*a*c*a";
        const bool output = solution.isMatch(s, p);
        constexpr bool expect_output = true;
        print(std::make_tuple(s, p), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
