#include "leetcode.h"

/*
 * Given an array filled with letters and numbers, find the longest subarray with an equal number of letters and numbers.
 * Return the subarray. If there are more than one answer, return the one which has the smallest index of its left endpoint. If there is no answer, return an empty arrary.
 *
 *
 * Example 1:
 * Input: ["A","1","B","C","D","2","3","4","E","5","F","G","6","7","H","I","J","K","L","M"]
 * Output: ["A","1","B","C","D","2","3","4","E","5","F","G","6","7"]
 *
 *
 * Example 2:
 * Input: ["A","A"]
 * Output: []
 *
 */

class Solution {
public:
    std::vector<std::string> findLongestSubarray(const std::vector<std::string>& array)
    {
        std::vector<std::string> result;
        if (array.size() == 0)
        {
            return result;
        }

        std::unordered_map<int64_t, std::size_t> prefixSums;
        prefixSums[0] = 0;

        int64_t sum = 0;
        std::size_t maxLength = 0;
        std::size_t maxLengthStart = 0;
        for (std::size_t i = 0; i < array.size(); ++i)
        {
            sum += IsNumber(array[i]) ? 1 : -1;

            auto iter = prefixSums.find(sum);
            if (iter == prefixSums.end())
            {
                prefixSums[sum] = i + 1;
            }
            else
            {
                assert(i >= (iter->second + 1));
                const uint64_t length = i - iter->second + 1;
                if (length > maxLength)
                {
                    maxLength = length;
                    maxLengthStart = iter->second;
                    assert(maxLengthStart + maxLength - 1 == i);
                }
            }
        }

        if (maxLength == 0)
        {
            return result;
        }
        for (std::size_t i = 0; i < maxLength; ++i)
        {
            result.push_back(array[maxLengthStart + i]);
        }
        return result;
    }

    bool IsNumber(const std::string& s) const
    {
        assert(s.length() == 1);
        return s[0] >= '0' && s[0] <= '9';
    }
};

TEST(FindLongestSubarray, simple)
{
    Solution solution;

    {
        auto result = solution.findLongestSubarray(
                {"A","1","B","C","D","2","3","4","E","5","F","G","6","7","H","I","J","K","L","M"});
        EXPECT_EQ(result,
                std::vector<std::string>({"A","1","B","C","D","2","3","4","E","5","F","G","6","7"}));
    }

    {
        auto result = solution.findLongestSubarray({"A","A"});
        EXPECT_EQ(result, std::vector<std::string>());
    }
}

DEFINE_MAIN
