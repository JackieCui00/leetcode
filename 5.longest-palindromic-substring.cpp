#include "leetcode.h"
#include <tuple>

/*
 * [5] Longest Palindromic Substring
 *
 * https://leetcode-cn.com/problems/longest-palindromic-substring/
 *
 * Given a string s, find the longest palindromic substring in s.
 *
 * Example 1:
 *
 * Input: s = "babad"
 * Output: "bab"
 * Note: "aba" is also a valid answer.
 *
 *
 * Example 2:
 *
 * Input: s = "cbbd"
 * Output: "bb"
 *
 *
 * Example 3:
 *
 * Input: s = "a"
 * Output: "a"
 *
 *
 * Example 4:
 *
 * Input: s = "ac"
 * Output: "a"
 *
 *
 * Constraints:
 *     1 <= s.length <= 1000
 *     s consist of only digits and English letters (lower-case and/or upper-case),
 *
 **/

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        std::size_t max_palindrome_length = s.size() + 1;
        std::size_t max_palindrome_start = 0;
        for (std::size_t center = 0; center < s.size(); ++center) {
            { // case 0: s.at(center) is center;
                std::size_t check_size = 0;
                while (center >= check_size
                        && center + check_size < s.size()
                        && s.at(center - check_size) == s.at(center + check_size)) {
                    ++check_size;
                }
                assert(check_size > 0);
                --check_size;
                const std::size_t palindrome_length = 2 * check_size + 1;
                if (max_palindrome_length > s.size() || palindrome_length > max_palindrome_length) {
                    max_palindrome_length = palindrome_length;
                    max_palindrome_start = center - check_size;
                }
            }
            if (center >= 1 && s.at(center) == s.at(center - 1)) { // case 1: s.at(center) and s.at(center - 1) is center
                std::size_t check_size = 0;
                while ((center - 1) >= check_size
                        && center + check_size < s.size()
                        && s.at(center - 1 - check_size) == s.at(center + check_size)) {
                    ++check_size;
                }
                assert(check_size > 0);
                --check_size;
                const std::size_t palindrome_length = 2 * check_size + 2;
                if (max_palindrome_length > s.size() || palindrome_length > max_palindrome_length) {
                    max_palindrome_length = palindrome_length;
                    max_palindrome_start = center - 1 - check_size;
                }
            }

            // optimize 1
            if (max_palindrome_start + max_palindrome_length == s.size()) {
                break;
            }
        }
        assert(max_palindrome_start < s.size());
        assert((max_palindrome_start + max_palindrome_length) <= s.size());

        return s.substr(max_palindrome_start, max_palindrome_length);
    }
};

TEST(LongestPalindromicSubstring, simple) {
    Solution solution;

    {
        std::string input = "babad";
        const std::string output = solution.longestPalindrome(input);
        const std::string expect_output = "bab";

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        std::string input = "cbbd";
        const std::string output = solution.longestPalindrome(input);
        const std::string expect_output = "bb";

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        std::string input = "a";
        const std::string output = solution.longestPalindrome(input);
        const std::string expect_output = "a";

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        std::string input = "ac";
        const std::string output = solution.longestPalindrome(input);
        const std::string expect_output = "a";

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
