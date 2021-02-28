#include "leetcode.h"

/*
 * https://leetcode-cn.com/problems/longest-substring-with-at-least-k-repeating-characters/
 *
 * 395. Longest Substring with At Least K Repeating Characters
 *
 * Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.
 *
 *
 * Example 1:
 *
 * Input: s = "aaabb", k = 3
 * Output: 3
 * Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
 *
 *
 * Example 2:
 *
 * Input: s = "ababbc", k = 2
 * Output: 5
 * Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
 *
 *
 * Constraints:
 *
 *     1 <= s.length <= 104
 *     s consists of only lowercase English letters.
 *     1 <= k <= 105
 *
 **/

class Solution {
public:
    int longestSubstring(std::string s, int k) {
        if (k == 1) {
            return s.size();
        }
        return this->longestSubstring_impl(s, 0, s.size(), k);
    }

    int longestSubstring_impl(const std::string& s, const std::size_t start,
                            const std::size_t end, const int k) {
        if (start == end) {
            return 0;
        }

        std::array<std::size_t, 26> count = {0};
        for (std::size_t i = start; i < end; ++i) {
            count.at(s.at(i) - 'a') += 1;
        }

        std::size_t sub_start = start;
        for (; sub_start < end; ++sub_start) {
            const char c = s.at(sub_start);
            if (count.at(c - 'a') < k) {
                break;
            }
        }
        if (sub_start == end) {
            return end - start;
        }

        int max_length = sub_start - start;

        while (sub_start < end) {
            // find a start
            for (; sub_start < end; ++sub_start) {
                const char c = s.at(sub_start);
                if (count.at(c - 'a') >= k) {
                    break;
                }
            }

            // find a end;
            std::size_t sub_end = sub_start;
            for (; sub_end < end; ++sub_end) {
                const char c = s.at(sub_end);
                if (count.at(c - 'a') < k) {
                    break;
                }
            }

            // now [sub_start, sub_end) is a possible string
            const int sub_max = this->longestSubstring_impl(s, sub_start, sub_end, k);
            max_length = std::max(max_length, sub_max);

            // finally, update sub_start
            sub_start = sub_end;
        }

        return max_length;
    }
};

TEST(LongestSubstringWithAtLeastKRepeatingCharacters, simple) {
    Solution solution;

    {
        const std::string s = "aaabb";
        const int k = 3;
        EXPECT_EQ(solution.longestSubstring(s, k), 3);
    }

    {
        const std::string s = "ababbc";
        const int k = 2;
        EXPECT_EQ(solution.longestSubstring(s, k), 5);
    }
}

DEFINE_MAIN
