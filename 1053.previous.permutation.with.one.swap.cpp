#include "leetcode.h"

/*
 * Given an array of positive integers arr (not necessarily distinct),
 * return the lexicographically largest permutation that is smaller than arr,
 * that can be made with exactly one swap.
 * If it cannot be done, then return the same array.
 *
 * Note that a swap exchanges the positions of two numbers arr[i] and arr[j]
 *
 * Example 1:
 * Input: arr = [3,2,1]
 * Output: [3,1,2]
 * Explanation: Swapping 2 and 1.
 *
 * Example 2:
 * Input: arr = [1,1,5]
 * Output: [1,1,5]
 * Explanation: This is already the smallest permutation.
 *
 * Example 3:
 * Input: arr = [1,9,4,6,7]
 * Output: [1,7,4,6,9]
 * Explanation: Swapping 9 and 7.
 *
 * Constraints:
 * - 1 <= arr.length <= 10^4
 * - 1 <= arr[i] <= 10^4
 */

class Solution
{
public:
    std::vector<int> prevPermOpt1(std::vector<int>& arr)
    {
        uint64_t ascendingStart = arr.size() - 1;
        while (ascendingStart > 0)
        {
            if (arr[ascendingStart - 1] > arr[ascendingStart])
            {
                break;
            }
            --ascendingStart;
        }
        if (ascendingStart == 0)
        {
            // always ascending, this is the smallest permutation
            return arr;
        }

        int key = arr[ascendingStart - 1];
        // find the largest element that is smaller than key, and swap them
        auto result = std::lower_bound(arr.begin() + ascendingStart, arr.end(), key);
        --result;
        while (*result == *(result - 1))
        {
            --result;
        }
        assert(*result < key);
        std::swap(*result, arr[ascendingStart - 1]);
        return arr;
    }
};

TEST(PreviousPermutationWithOneSwap, simple)
{
    Solution solution;

    {
        std::vector<int> input = {3, 2, 1};
        EXPECT_EQ(std::vector<int>({3, 1, 2}), solution.prevPermOpt1(input));
    }

    {
        std::vector<int> input = {1, 1, 5};
        EXPECT_EQ(std::vector<int>({1, 1, 5}), solution.prevPermOpt1(input));
    }

    {
        std::vector<int> input = {1, 9, 4, 6, 7};
        EXPECT_EQ(std::vector<int>({1, 7, 4, 6, 9}), solution.prevPermOpt1(input));
    }

    {
        std::vector<int> input = {3, 1, 1, 3};
        EXPECT_EQ(std::vector<int>({1, 3, 1, 3}), solution.prevPermOpt1(input));
    }
}

DEFINE_MAIN
