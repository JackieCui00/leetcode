#include "leetcode.h"

/*
 * https://leetcode.cn/problems/maximum-gap/
 *
 * Given an integer array nums, return the maximum difference between two successive
 * elements in its sorted form. If the array contains less than two elements, return 0.
 *
 * You must write an algorithm that runs in linear time and uses linear extra space.
 *
 * Example 1:
 * Input: nums = [3,6,9,1]
 * Output: 3
 * Explanation: The sorted form of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum difference 3.
 *
 * Example 2:
 * Input: nums = [10]
 * Output: 0
 * Explanation: The array contains less than 2 elements, therefore return 0.
 *
 * Constraints:
 *  1 <= nums.length <= 10^5
 *  0 <= nums[i] <= 10^9
 *
 */

class Solution {
public:
    int maximumGap(const std::vector<int>& nums)
    {
        if (nums.size() < 2)
        {
            return 0;
        }

        int64_t min = INT64_MAX;
        int64_t max = -1;
        for (const auto i : nums)
        {
            min = std::min(static_cast<int64_t>(i), min);
            max = std::max(static_cast<int64_t>(i), max);
        }
        if (min == max)
        {
            return 0;
        }

        const int64_t BUCKET_NUMBER = nums.size();
        const int64_t bucketGap = (max - min) * BUCKET_NUMBER / (BUCKET_NUMBER - 1);
        std::cout << "bucketGap: " << bucketGap << std::endl;
        std::vector<std::pair<int64_t, int64_t>> buckets; // min, max
        buckets.resize(BUCKET_NUMBER + 1, std::make_pair(INT64_MAX, -1));

        for (const auto i : nums)
        {
            const int bucket = static_cast<int>((static_cast<int64_t>(i) - min) * BUCKET_NUMBER / bucketGap);
        std::cout << "bucke: " << bucket << std::endl;
            assert(bucket < BUCKET_NUMBER + 1);
            auto& b = buckets[bucket];
            b.first = std::min(static_cast<int64_t>(i), b.first);
            b.second = std::max(static_cast<int64_t>(i), b.second);
        }

        int64_t result = -1;
        int64_t m = -1;
        for (auto& b : buckets)
        {
            // std::cout << b.first << ", " << b.second << std::endl;
            if (m == -1)
            {
                // first
                m = b.second;
                continue;
            }
            else if (b.first == INT64_MAX)
            {
                continue;
            }

            assert(b.first > m);
            result = std::max(b.first - m, result);
            m = b.second;
        }

        return result;
    }
};

TEST(MaximumGap, simple)
{
    Solution solution;
    EXPECT_EQ(solution.maximumGap({3, 6, 9, 1}), 3);
    EXPECT_EQ(solution.maximumGap({10}), 0);
    EXPECT_EQ(solution.maximumGap({1, 1, 1, 1, 1, 5, 5, 5, 5, 5}), 4);
}

DEFINE_MAIN
