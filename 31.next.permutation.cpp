#include "leetcode.h"

/*
 * 31. Next Permutation
 *
 * Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
 *
 * If such an arrangement is not possible, it must rearrange it as the lowest possible order (i.e., sorted in ascending order).
 *
 * The replacement must be in place and use only constant extra memory.
 *
 *
 * Example 1:
 *
 * Input: nums = [1,2,3]
 * Output: [1,3,2]
 *
 *
 * Example 2:
 *
 * Input: nums = [3,2,1]
 * Output: [1,2,3]
 *
 *
 * Example 3:
 *
 * Input: nums = [1,1,5]
 * Output: [1,5,1]
 *
 *
 * Example 4:
 *
 * Input: nums = [1]
 * Output: [1]
 *
 *
 * Constraints:
 *     1 <= nums.length <= 100
 *     0 <= nums[i] <= 100
 *
 **/

class Solution {
public:
    void nextPermutation(std::vector<int>& numbers) {
        assert(!numbers.empty());
        if (numbers.size() == 1) {
            return;
        }

        int change_index = numbers.size() - 1;
        while (change_index > 0) {
            if (numbers.at(change_index) > numbers.at(change_index - 1)) {
                break;
            }
            --change_index;
        }

        if (change_index == 0) { // max permutation
            std::sort(numbers.begin(), numbers.end());
            return;
        }

        for (std::size_t i = 0; i < (numbers.size() - change_index) / 2; ++i) {
            std::size_t index1 = change_index + i;
            std::size_t index2 = numbers.size() - 1 - i;
            std::swap(numbers.at(index1), numbers.at(index2));
        }

        auto iter = std::upper_bound(numbers.begin() + change_index, numbers.end(), numbers.at(change_index - 1));
        std::swap(numbers.at(change_index - 1), *iter);
    }
};

TEST(NextPermutation, simple) {
    Solution solution;

    {
        const std::vector<int> input = {1, 2, 3};
        std::vector<int> output = input;
        solution.nextPermutation(output);
        const std::vector<int> expect_ouptut = {1, 3, 2};

        print(std::make_tuple(input), output, expect_ouptut);

        EXPECT_EQ(output, expect_ouptut);
    }

    {
        const std::vector<int> input = {3, 2, 1};
        std::vector<int> output = input;
        solution.nextPermutation(output);
        const std::vector<int> expect_ouptut = {1, 2, 3};

        print(std::make_tuple(input), output, expect_ouptut);

        EXPECT_EQ(output, expect_ouptut);
    }

    {
        const std::vector<int> input = {1, 1, 5};
        std::vector<int> output = input;
        solution.nextPermutation(output);
        const std::vector<int> expect_ouptut = {1, 5, 1};

        print(std::make_tuple(input), output, expect_ouptut);

        EXPECT_EQ(output, expect_ouptut);
    }

    {
        const std::vector<int> input = {1};
        std::vector<int> output = input;
        solution.nextPermutation(output);
        const std::vector<int> expect_ouptut = {1};

        print(std::make_tuple(input), output, expect_ouptut);

        EXPECT_EQ(output, expect_ouptut);
    }
}

DEFINE_MAIN
