#include "leetcode.h"

/*
 * 503. Next Greater Element II
 *
 *  Given a circular array (the next element of the last element is the first element of the array), print the Next Greater Number for every element. The Next Greater Number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, output -1 for this number.
 *
 * Example 1:
 *
 * Input: [1,2,1]
 * Output: [2,-1,2]
 * Explanation: The first 1's next greater number is 2;
 * The number 2 can't find next greater number;
 * The second 1's next greater number needs to search circularly, which is also 2.
 *
 * Note: The length of given array won't exceed 10000.
 *
 **/

class Solution {
public:
    std::vector<int> nextGreaterElements(std::vector<int>& nums) {
        if (nums.size() == 0) {
            return std::vector<int>();
        }

        std::vector<std::size_t> stack;
        std::vector<int> result(nums.size(), -1);

        for (std::size_t i = 0; i < nums.size(); ++i) {
            const int n = nums.at(i);

            while (!stack.empty() && nums.at(stack.back()) < n) {
                result.at(stack.back()) = n;
                stack.pop_back();
            }

            stack.push_back(i);
        }

        for (std::size_t i = 0; i < nums.size(); ++i) {
            const int n = nums.at(i);

            assert(!stack.empty());
            while (nums.at(stack.back()) < n) {
                result.at(stack.back()) = n;
                stack.pop_back();
            }
            assert(!stack.empty());
        }
        assert(stack.size() >= 1);

        return result;
    }
};

TEST(NextGreaterElements, simple) {
    Solution solution;

    {
        std::vector<int> input = {1, 2, 1};
        const std::vector<int> output = solution.nextGreaterElements(input);
        const std::vector<int> expect_output = {2, -1, 2};

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    };

    {
        std::vector<int> input = {1, 1, 1, 1, 1};
        const std::vector<int> output = solution.nextGreaterElements(input);
        const std::vector<int> expect_output = {-1, -1, -1, -1, -1};

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    };
}

DEFINE_MAIN
