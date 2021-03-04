#include "leetcode.h"
#include <limits>

/*
 * 300. Longest Increasing Subsequence
 *
 * Given an integer array nums, return the length of the longest strictly increasing subsequence.
 *
 * A subsequence is a sequence that can be derived from an array by deleting some or no elements
 * without changing the order of the remaining elements.
 * For example, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7].
 *
 *
 * Example 1:
 *
 * Input: nums = [10,9,2,5,3,7,101,18]
 * Output: 4
 * Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
 *
 *
 * Example 2:
 *
 * Input: nums = [0,1,0,3,2,3]
 * Output: 4
 *
 *
 * Example 3:
 *
 * Input: nums = [7,7,7,7,7,7,7]
 * Output: 1
 *
 *
 * Constraints:
 *
 *     1 <= nums.length <= 2500
 *     -104 <= nums[i] <= 104
 *
 *
 * Follow up:
 *
 *     Could you come up with the O(n2) solution?
 *     Could you improve it to O(n log(n)) time complexity?
 *
 **/

class Solution {
public:
    int lengthOfLIS(const std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        std::map<int, std::size_t> end_max;
        {
            end_max.emplace(nums.at(0), 1);
        }
        std::size_t max = 1;

        for (std::size_t i = 1; i < nums.size(); ++i) {
            const int n = nums.at(i);

            auto iter = end_max.lower_bound(n);
            if (iter == end_max.begin()) {
                end_max.emplace(n, 1);
                assert(max >= 1);
                continue;
            }

            iter = std::prev(iter);
            assert(iter->first < n);

            const std::size_t end = iter->second + 1;
            iter = end_max.emplace_hint(iter, n, end);
            iter->second = std::max(end, iter->second);
            assert(iter != end_max.end());

            ++iter;
            while (iter != end_max.end() && iter->second < end) {
                iter = end_max.erase(iter);
            }

            max = std::max(max, end);
        }

        return max;
    }
};

TEST(LongestIncreaseingSubsequence, simple) {
    Solution solution;

    {
        const std::vector<int> input = {10, 9, 2, 5, 3, 7, 101, 18};
        const int output = solution.lengthOfLIS(input);
        const int expect_output = 4;

        EXPECT_EQ(output, expect_output);

        print(std::make_tuple(input), output, expect_output);
    }

    {
        const std::vector<int> input = {0, 1, 0, 3, 2, 3};
        const int output = solution.lengthOfLIS(input);
        const int expect_output = 4;

        EXPECT_EQ(output, expect_output);

        print(std::make_tuple(input), output, expect_output);
    }

    {
        const std::vector<int> input = {7, 7, 7, 7, 7, 7, 7};
        const int output = solution.lengthOfLIS(input);
        const int expect_output = 1;

        EXPECT_EQ(output, expect_output);

        print(std::make_tuple(input), output, expect_output);
    }
}

DEFINE_MAIN
