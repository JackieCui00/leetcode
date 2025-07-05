#include "leetcode.h"

/*
 * Given an array nums of distinct integers, return all the possible permutations.
 * You can return the answer in any order.
 *
 * Example 1:
 * Input: nums = [1,2,3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *
 * Example 2:
 * Input: nums = [0,1]
 * Output: [[0,1],[1,0]]
 *
 * Example 3:
 * Input: nums = [1]
 * Output: [[1]]
 *
 * Constraints:
 * - 1 <= nums.length <= 6
 * - -10 <= nums[i] <= 10
 * - All the integers of nums are unique.
 *
 */

class Solution {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        uint64_t resultSize = 1;
        for (uint64_t i = 1; i <= nums.size(); ++i)
        {
            resultSize *= i;
        }
        std::vector<std::vector<int>> result;
        result.reserve(resultSize);

        this->generate(result, nums, 0 /*start*/);
        assert(result.size() == resultSize);
        return result;
    }

    void generate(std::vector<std::vector<int>>& result, std::vector<int>& nums, uint64_t start)
    {
        if (start == nums.size())
        {
            result.emplace_back(nums);
            return;
        }

        this->generate(result, nums, start + 1);
        for (uint64_t i = start + 1; i < nums.size(); ++ i)
        {
            std::swap(nums[start], nums[i]);
            this->generate(result, nums, start + 1);
            std::swap(nums[start], nums[i]);
        }
    }
};

TEST(Permutations, simple)
{
    Solution solution;

    {
        std::vector<int> input = {1, 2, 3};
        auto result = solution.permute(input);
        decltype(result) expectResult = {
            {1, 2, 3},
            {1, 3, 2},
            {2, 1, 3},
            {2, 3, 1},
            {3, 1, 2},
            {3, 2, 1}
        };

        EXPECT_EQ(result, expectResult);
    }

    {
        std::vector<int> input = {0, 1};
        auto result = solution.permute(input);
        decltype(result) expectResult = {
            {0, 1},
            {1, 0}
        };

        EXPECT_EQ(result, expectResult);
    }

    {
        std::vector<int> input = {1};
        auto result = solution.permute(input);
        decltype(result) expectResult = {
            {1}
        };

        EXPECT_EQ(result, expectResult);
    }
}

DEFINE_MAIN
