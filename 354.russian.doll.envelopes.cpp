#include "leetcode.h"
#include <bits/c++config.h>
#include <tuple>
#include <utility>

/*
 * 354. Russian Doll Envelopes
 *
 * https://leetcode-cn.com/problems/russian-doll-envelopes/
 *
 * You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.
 *
 * One envelope can fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.
 *
 * Return the maximum number of envelopes can you Russian doll (i.e., put one inside the other).
 *
 * Note: You cannot rotate an envelope.
 *
 *
 * Example 1:
 *
 * Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
 * Output: 3
 * Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
 *
 *
 * Example 2:
 *
 * Input: envelopes = [[1,1],[1,1],[1,1]]
 * Output: 1
 *
 *
 * Constraints:
 *
 *     1 <= envelopes.length <= 5000
 *     envelopes[i].length == 2
 *     1 <= wi, hi <= 104
 *
 **/

class Solution {
public:
    int maxEnvelopes(std::vector<std::vector<int>>& envelopes) {
        return maxEnvelopes_v2(envelopes);
    }

    int maxEnvelopes_v2(std::vector<std::vector<int>>& envelopes) {
        if (envelopes.empty()) {
            return 0;
        }

        {
            struct VectorCompare {
                bool operator()(const std::vector<int>& left, const std::vector<int>& right) {
                    assert(left.size() == 2);
                    assert(right.size() == 2);

                    if (left.at(0) != right.at(0)) {
                        return left.at(0) < right.at(0);
                    }
                    return left.at(1) > right.at(1);
                }
            } comp;

            std::sort(envelopes.begin(), envelopes.end(), comp);
        }

        std::map<int, std::size_t> end_maxs = {{envelopes.begin()->at(1), 1}};
        std::size_t max = 1;

        for (std::size_t i = 1; i < envelopes.size(); ++i) {
            const int n = envelopes.at(i).at(1);

            auto iter = end_maxs.lower_bound(n);
            if (iter == end_maxs.begin()) {
                (void)end_maxs.emplace(n , 1);
                continue;
            }

            iter = std::prev(iter);
            assert(iter->first < n);

            const std::size_t end_max = iter->second + 1;
            iter = end_maxs.emplace_hint(iter, n, end_max);
            iter->second = std::max(iter->second, end_max);

            ++iter;
            while (iter != end_maxs.end() && iter->second < end_max) {
                iter = end_maxs.erase(iter);
            }

            max = std::max(end_max, max);
        }

        return max;
    }

    int maxEnvelopes_v1(std::vector<std::vector<int>>& envelopes) {
        if (envelopes.empty()) {
            return 0;
        }

        std::sort(envelopes.begin(), envelopes.end());

        std::map<int, std::pair<int, std::size_t>> end_maxs = {{envelopes.begin()->at(1), {envelopes.begin()->at(0),1}}};
        std::size_t max = 1;

        for (std::size_t i = 1; i < envelopes.size(); ++i) {
            const int first = envelopes.at(i).at(0);
            const int n = envelopes.at(i).at(1);

            auto iter = end_maxs.lower_bound(n);
            if (iter == end_maxs.begin()) {
                (void)end_maxs.emplace(std::piecewise_construct, std::make_tuple(n), std::make_tuple(first, 1));
                continue;
            }

            iter = std::prev(iter);
            auto orig_iter = iter;

            assert(iter->first < n);
            assert(iter->second.first <= first);
            while (iter != end_maxs.begin() && iter->second.first == first) {
                iter = std::prev(iter);
            }
            if (iter->second.first == first) {
                (void)end_maxs.emplace_hint(orig_iter, std::piecewise_construct, std::make_tuple(n), std::make_tuple(first, 1));
                continue;
            }

            const std::size_t end_max = iter->second.second + 1;
            iter = end_maxs.emplace_hint(orig_iter, std::piecewise_construct, std::make_tuple(n), std::make_tuple(first, end_max));
            if (iter->second.second < end_max) {
                iter->second = std::make_pair(first, end_max);
            }

            ++iter;
            while (iter != end_maxs.end() && iter->second.second < end_max) {
                iter = end_maxs.erase(iter);
            }

            max = std::max(end_max, max);
        }

        return max;
    }
};

TEST(MaxEnvelops, simple) {
    Solution solution;

    {
        std::vector<std::vector<int>> input = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
        const int output = solution.maxEnvelopes(input);
        const int expect_output = 3;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<std::vector<int>> input = {{1, 1}, {1, 1}, {1, 1}};
        const int output = solution.maxEnvelopes(input);
        const int expect_output = 1;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<std::vector<int>> input = {{46, 89}, {50, 53}, {52, 68}, {72, 45}, {77, 81}};
        const int output = solution.maxEnvelopes(input);
        const int expect_output = 3;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<std::vector<int>> input = {{4, 5}, {4, 6}, {6, 7}, {2, 3}, {1, 1}};
        const int output = solution.maxEnvelopes(input);
        const int expect_output = 4;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN

