#include "leetcode.h"

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
        std::vector<std::vector<int>> result;
        if (nums.empty()) {
            return result;
        }

        std::vector<int> numbers = nums;
        std::sort(numbers.begin(), numbers.end());

        assert(numbers.size() > 0);
        int old_number = numbers.at(0) - 1; // smallest number
        for (std::size_t i = 0; i < numbers.size(); ++i) {
            if (old_number == numbers.at(i)) {
                continue;
            }
            old_number = numbers.at(i);

            const int target = - numbers.at(i);

            std::size_t head = i + 1;
            std::size_t tail = numbers.size() - 1;
            while (head < tail) {
                const int sum = numbers.at(head) + numbers.at(tail) ;
                if (sum == target) {
                    result.push_back({numbers.at(i), numbers.at(head), numbers.at(tail)});
                    const int old_head = numbers.at(head);
                    while (head < tail && numbers.at(head) == old_head) {
                        ++head;
                    }
                    const int old_tail = numbers.at(tail);
                    while (head < tail && numbers.at(tail) == old_tail) {
                        --tail;
                    }
                } else if (sum < target) {
                    const int old_head = numbers.at(head);
                    while (head < tail && numbers.at(head) == old_head) {
                        ++head;
                    }
                } else {
                    assert(sum > target);
                    const int old_tail = numbers.at(tail);
                    while (head < tail && numbers.at(tail) == old_tail) {
                        --tail;
                    }
                }
            }
        }

        return result;
    }

    // The following example using [] rather than .at to avoid branch-mispredict
    // and leetcode show 168ms for threeSum and 104ms for threeSum_NoAt
    // Also, the fastest solution use iterator rather than index, and it only use 40ms
    //
    // Interesting
    std::vector<std::vector<int>> threeSum_NoAt(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        if (nums.empty()) {
            return result;
        }

        std::vector<int> numbers = nums;
        std::sort(numbers.begin(), numbers.end());

        assert(numbers.size() > 0);
        int old_number = numbers[0] - 1; // smallest number
        for (std::size_t i = 0; i < numbers.size(); ++i) {
            if (old_number == numbers[i]) {
                continue;
            }
            old_number = numbers[i];

            const int target = - numbers[i];

            std::size_t head = i + 1;
            std::size_t tail = numbers.size() - 1;
            while (head < tail) {
                const int sum = numbers[head] + numbers[tail] ;
                if (sum == target) {
                    result.push_back({numbers[i], numbers[head], numbers[tail]});
                    const int old_head = numbers[head];
                    while (head < tail && numbers[head] == old_head) {
                        ++head;
                    }
                    const int old_tail = numbers[tail];
                    while (head < tail && numbers[tail] == old_tail) {
                        --tail;
                    }
                } else if (sum < target) {
                    const int old_head = numbers[head];
                    while (head < tail && numbers[head] == old_head) {
                        ++head;
                    }
                } else {
                    assert(sum > target);
                    const int old_tail = numbers[tail];
                    while (head < tail && numbers[tail] == old_tail) {
                        --tail;
                    }
                }
            }
        }

        return result;
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

    {
        std::vector<int> input = {0, 0, 0};
        auto output = solution.threeSum(input);
        decltype(output) expect_output = {{0, 0, 0}};

        print(std::make_tuple(input), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
