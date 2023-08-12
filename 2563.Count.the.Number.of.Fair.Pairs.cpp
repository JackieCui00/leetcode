#include "leetcode.h"

/*
 * https://leetcode.cn/problems/count-the-number-of-fair-pairs/
 *
 * Given a 0-indexed integer array nums of size n and two integers lower and upper, return the number of fair pairs.
 *
 * A pair (i, j) is fair if:
 *
 * 0 <= i < j < n, and
 * lower <= nums[i] + nums[j] <= upper
 *
 *
 * Example 1:
 * Input: nums = [0,1,7,4,4,5], lower = 3, upper = 6
 * Output: 6
 * Explanation: There are 6 fair pairs: (0,3), (0,4), (0,5), (1,3), (1,4), and (1,5).
 *
 * Example 2:
 * Input: nums = [1,7,9,2,5], lower = 11, upper = 11
 * Output: 1
 * Explanation: There is a single fair pair: (2,3).
 *
 * Constraints:
 * 1 <= nums.length <= 105
 * nums.length == n
 * -109 <= nums[i] <= 109
 * -109 <= lower <= upper <= 109
 *
 */

class Solution {
public:
    long long countFairPairs(std::vector<int>& nums, int lower, int upper) {
        return countFairPairs2(nums, lower, upper);
    }

    long long countFairPairs2(std::vector<int>& nums, int lower, int upper) {
        std::sort(nums.begin(), nums.end());

        uint64_t lessThanUpper = this->countLessThan(nums, upper);
        uint64_t lessThanLower = this->countLessThan(nums, lower - 1);
        return lessThanUpper - lessThanLower;
    }

    uint64_t countLessThan(std::vector<int>&nums, const int target)
    {
        uint64_t result = 0;

        int left = 0;
        int right = nums.size() - 1;

        while (left < right)
        {
            if (nums[left] + nums[right] <= target)
            {
                result += right - left;
                ++left;
            }
            else
            {
                --right;
            }
        }

        return result;
    }

    long long countFairPairs1(std::vector<int>& nums, int lower, int upper) {
        assert(lower <= upper);
        std::sort(nums.begin(), nums.end());

        uint64_t result = 0;
        if (nums.size() < 2)
        {
            return result;
        }

        if (nums[0] + nums[1] >= lower && nums[0] + nums[1] <= upper)
        {
            result++;
        }

        std::cout << "numbers:" << nums << ", lower:" << lower << ", upper:" << upper << std::endl;
        for (uint64_t i = 2; i < nums.size(); ++i)
        {
            const int extraLower =  lower - nums[i];
            const uint64_t smallNumber = this->small_number(nums, 0, i, extraLower);
            assert(smallNumber <= i);
            const int extraUpper =  upper - nums[i];
            const uint64_t bigNumber = this->big_number(nums, 0, i, extraUpper);
            assert(bigNumber <= i);

            assert((smallNumber + bigNumber) <= i);
            result += i - smallNumber - bigNumber;

            std::cout << "i: " << i
                << " extraLower:" << extraLower << " smallNumber: " << smallNumber
                << " extraUpper:" << extraUpper << " bigNumber: " << bigNumber
                << " result:" << result << std::endl;
        }

        return result;
    }

    // find number of count < target
    uint64_t small_number(std::vector<int>& nums, const int start, const int end, const int target)
    {
        if (start >= end)
        {
            return 0;
        }

        uint64_t result = 0;
        int mid = (start + end) / 2;

        if (nums[mid] < target)
        {
            result += mid - start + 1;
            result += small_number(nums, mid + 1, end, target);
        }
        else
        {
            result = small_number(nums, start, mid, target);
        }
        return result;
    }

    // find number of count > target
    uint64_t big_number(std::vector<int>& nums, const int start, const int end, const int target)
    {
        if (start >= end)
        {
            return 0;
        }

        uint64_t result = 0;
        int mid = (start + end) / 2;

        if (nums[mid] > target)
        {
            result += end - mid;
            result += big_number(nums, start, mid, target);
        }
        else
        {
            result = big_number(nums, mid + 1, end, target);
        }
        return result;
    }
};

TEST(FairPairCount, simple)
{
    Solution solution;
    {
        std::vector<int> data{0, 1, 7, 4, 4, 5};
        EXPECT_EQ(solution.countFairPairs(data, 3, 6), 6);
    }
    {
        std::vector<int> data{1, 7, 9, 2, 5};
        EXPECT_EQ(solution.countFairPairs(data, 11, 11), 1);
    }
}

DEFINE_MAIN
