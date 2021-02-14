#include "leetcode.h"

/*
 * [33] Search in Rotated Sorted Array
 *
 * https://leetcode-cn.com/problems/search-in-rotated-sorted-array/
 *
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand.
 *
 * (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
 *
 * You are given a target value to search. If found in the array return its
 * index, otherwise return -1.
 *
 * You may assume no duplicate exists in the array.
 *
 * Your algorithm's runtime complexity must be in the order of O(log n).
 *
 * Example 1:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 *
 *
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 *
 *
 * Constraints:
 *    1 <= nums.length <= 5000
 *    -10^4 <= nums[i] <= 10^4
 *    All values of nums are unique.
 *    nums is guaranteed to be rotated at some pivot.
 *    -10^4 <= target <= 10^4
 */

class Solution {
public:
    int search(std::vector<int>& nums, int target) {
    }
};

TEST(SearchInRotatedSortedArray, simple) {
    Solution solution;

    {
        std::vector<int> numbers = {4, 5, 6, 7, 0, 1, 2};
        const int target = 0;

        const int output = solution.search(numbers, target);
        constexpr int expect_output = 4;

        print(std::make_tuple(numbers, target), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<int> numbers = {4, 5, 6, 7, 0, 1, 2};
        const int target = 3;

        const int output = solution.search(numbers, target);
        constexpr int expect_output = -1;

        print(std::make_tuple(numbers, target), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<int> numbers = {1};
        const int target = 0;

        const int output = solution.search(numbers, target);
        constexpr int expect_output = -1;

        print(std::make_tuple(numbers, target), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
