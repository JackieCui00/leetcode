#include "leetcode.h"
#include <tuple>
/*
 *
 * https://leetcode.com/problems/3sum/description/
 *
 * Given an array nums of n integers, are there elements a, b, c in nums such
 * that a + b + c = 0? Find all unique triplets in the array which gives the
 * sum of zero.
 *
 * Note:
 *
 * The solution set must not contain duplicate triplets.
 *
 * Example:
 * Given array nums = [-1, 0, 1, 2, -1, -4],
 *
 * A solution set is:
 * [
 * ⁠ [-1, 0, 1],
 * ⁠ [-1, -1, 2]
 * ]
 *
 */

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {

    }
};

TEST(TreeSum, simple) {
    Solution solution;

    {
        std::vector<int> input = {-1, 0, 1, 2, -1, -4};
        auto output = solution.threeSum(input);
        decltype(output) expect_output = {{-1, -1, 2}, {-1, 0, 1}};

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<int> input = {};
        auto output = solution.threeSum(input);
        decltype(output) expect_output = {};

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<int> input = {0};
        auto output = solution.threeSum(input);
        decltype(output) expect_output = {};

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
