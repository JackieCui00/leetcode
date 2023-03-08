#include "leetcode.h"

/*
 * Given an unsorted integer array nums, return the smallest missing positive integer.
 *
 * You must implement an algorithm that runs in O(n) time and uses constant extra space.
 *
 *
 * Example 1:
 * Input: nums = [1,2,0]
 * Output: 3
 * Explanation: The numbers in the range [1,2] are all in the array.
 *
 * Example 2:
 * Input: nums = [3,4,-1,1]
 * Output: 2
 * Explanation: 1 is in the array but 2 is missing.
 *
 * Example 3:
 * Input: nums = [7,8,9,11,12]
 * Output: 1
 * Explanation: The smallest positive integer 1 is missing.
 *
 */

class Solution {
public:
    int firstMissingPositive(std::vector<int>& nums) {
        int max = static_cast<int>(nums.size());
        for (int i = 0; i < max; ++i)
        {
            int value = nums[i];
            nums[i] = -1;

            if (value <= 0 || value > max)
            {
                continue;
            }

            if (value - 1 <= i)
            {
                assert(nums[value - 1] == -1 || nums[value - 1] == value);
                nums[value - 1] = value;
            }
            else if (value == nums[value - 1])
            {
                // pass
                continue;
            }
            else
            {
                nums[i] = nums[value - 1];
                --i;
                nums[value - 1] = value;
            }
        }

        for (int i = 0; i < max; ++i)
        {
            if (nums[i] != (i + 1))
            {
                return i + 1;
            }
        }
        return nums.size() + 1;
    }
};

TEST(FirstMissingPositive, simple)
{
    Solution solution;

    {
        std::vector<int> data({1, 2, 0});
        EXPECT_EQ(3, solution.firstMissingPositive(data));
    }

    {
        std::vector<int> data({3, 4, -1 , 1});
        EXPECT_EQ(2, solution.firstMissingPositive(data));
    }

    {
        std::vector<int> data({7, 8, 9, 11, 12});
        EXPECT_EQ(1, solution.firstMissingPositive(data));
    }

    {
        std::vector<int> data({2, 2});
        EXPECT_EQ(1, solution.firstMissingPositive(data));
    }
}

DEFINE_MAIN
