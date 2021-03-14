#include "leetcode.h"
#include <bits/c++config.h>

/*
 * 132. Palindrome Partitioning II
 *
 * https://leetcode-cn.com/problems/palindrome-partitioning-ii/
 *
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 *
 * Return the minimum cuts needed for a palindrome partitioning of s.
 *
 *
 * Example 1:
 *
 * Input: s = "aab"
 * Output: 1
 * Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
 *
 *
 * Example 2:
 *
 * Input: s = "a"
 * Output: 0
 *
 *
 * Example 3:
 *
 * Input: s = "ab"
 * Output: 1
 *
 *
 * Constraints:
 *
 *     1 <= s.length <= 2000
 *     s consists of lower-case English letters only.
 *
 **/

class Solution {
public:
    int minCut(std::string s) {
        return this->minCut_v2(s);
    }

    int minCut_v2(const std::string& s) {
        assert(!s.empty());
        if (s.size() == 1) {
            return 0;
        }

        std::vector<int> min_cuts(s.size());
        for (std::size_t i = 0; i < s.size(); ++i) {
            min_cuts.at(i) = i;
        }

        for (std::size_t i = 1; i < s.size(); ++i) {
            std::size_t start = i - 1;
            std::size_t end = i;
            while (end < s.size() && s.at(start) == s.at(end)) {
                assert(start < end);

                if (start == 0) {
                    min_cuts.at(end) = 0;
                    break;
                }

                min_cuts.at(end) = std::min(min_cuts.at(end), min_cuts.at(start - 1) + 1);

                --start;
                ++end;
            }

            start = i;
            end = i;
            while (end < s.size() && s.at(start) == s.at(end)) {
                assert(start <= end);

                if (start == 0) {
                    min_cuts.at(end) = 0;
                    break;
                }

                min_cuts.at(end) = std::min(min_cuts.at(end), min_cuts.at(start - 1) + 1);

                --start;
                ++end;
            }
        }

        return min_cuts.back();
    }

    std::vector<std::vector<bool>> calculate_palindrome(const std::string& s) {
        std::vector<std::vector<bool>> result;
        result.resize(s.size());
        for (std::size_t i = 0; i < s.size(); ++i) {
            result[i].resize(i + 1, false);
        }

        for (std::size_t center = 0; center < s.size(); ++center) {
            result.at(center).at(center) = true;

            int start = center - 1;
            std::size_t end = center + 1;
            while (start >= 0 && end < s.size()) {
                if (s.at(start) != s.at(end)) {
                    break;
                }

                result.at(end).at(start) = true;
                --start;
                ++end;
            }

            start = center;
            end = center + 1;
            while (start >= 0 && end < s.size()) {
                if (s.at(start) != s.at(end)) {
                    break;
                }

                result.at(end).at(start) = true;
                --start;
                ++end;
            }
        }

        return result;
    }

    int minCut_v1(const std::string& s) {
        assert(!s.empty());

        const auto is_palindrome = this->calculate_palindrome(s);

        std::vector<int> min_cuts(s.size(), 0);
        min_cuts.at(0) = 0;

        for (std::size_t i = 1; i < s.size(); ++i) {
            if (is_palindrome.at(i).at(0)) {
                min_cuts.at(i) = 0;
                continue;
            }

            int cut = s.size();
            for (std::size_t j = 1; j <= i; ++j) {
                if (!is_palindrome.at(i).at(j)) {
                    continue;
                }
                cut = std::min(cut, min_cuts.at(j - 1) + 1);
            }

            min_cuts.at(i) = cut;
        }

        return min_cuts.back();
    }
};

TEST(MinCut, simple) {
    Solution solution;

    {
        const std::string input = "a";
        const int output = solution.minCut(input);
        const int expect_output = 0;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const std::string input = "ab";
        const int output = solution.minCut(input);
        const int expect_output = 1;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const std::string input = "aab";
        const int output = solution.minCut(input);
        const int expect_output = 1;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        const std::string input = "abcbaadcda";
        const int output = solution.minCut(input);
        const int expect_output = 1;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
