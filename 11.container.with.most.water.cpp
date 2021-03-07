#include "leetcode.h"

/*
 * 11. Container With Most Water
 *
 * https://leetcode-cn.com/problems/container-with-most-water/
 *
 * Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of the line i is at (i, ai) and (i, 0). Find two lines, which, together with the x-axis forms a container, such that the container contains the most water.
 *
 * Notice that you may not slant the container.
 *
 *
 * Example 1:
 * Input: height = [1,8,6,2,5,4,8,3,7]
 * Output: 49
 * Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
 *
 * Example 2:
 *
 * Input: height = [1,1]
 * Output: 1
 *
 *
 * Example 3:
 *
 * Input: height = [4,3,2,1,4]
 * Output: 16
 *
 *
 * Example 4:
 *
 * Input: height = [1,2,1]
 * Output: 2
 *
 *
 * Constraints:
 *
 *     n == height.length
 *     2 <= n <= 105
 *     0 <= height[i] <= 104
 **/

class Solution {
public:
    int maxArea(std::vector<int> height) {
        std::size_t start = 0;
        std::size_t end = height.size() - 1;
        int result = 0;

        while (start < end) {
            int area = 0;
            if (height.at(start) < height.at(end)) {
                area = height.at(start) * (end - start);
                ++start;
            } else {
                area = height.at(end) * (end - start);
                --end;
            }

            result = std::max(area, result);
        }

        return result;
    }
};

TEST(MaxArea, simple) {
    Solution solution;

    {
        std::vector<int> input = {1, 8, 6, 2, 5, 4, 8, 3, 7};
        const int output = solution.maxArea(input);
        const int expect_output = 49;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<int> input = {1, 1};
        const int output = solution.maxArea(input);
        const int expect_output = 1;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<int> input = {4, 3, 2, 1, 4};
        const int output = solution.maxArea(input);
        const int expect_output = 16;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<int> input = {1, 2, 1};
        const int output = solution.maxArea(input);
        const int expect_output = 2;

        print(std::make_tuple(input), output, expect_output);

        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
