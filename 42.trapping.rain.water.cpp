#include "leetcode.h"

/*
 * Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

 * Example 1:
 * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 * Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.

 * Example 2:
 * Input: height = [4,2,0,3,2,5]
 * Output: 9
 */

class Solution {
public:
    int trap(const std::vector<int>& height)
    {
        if (height.empty())
        {
            return 0;
        }

        return trapByDoublePtr(height);
    }

    int trapByDoublePtr(const std::vector<int>& height)
    {
        int64_t maxLeft = 0;
        int64_t maxRight = height.size() - 1;

        int64_t left = 0;
        int64_t right = height.size() - 1;

        int64_t result = 0;
        while (left <= right)
        {
            int64_t leftMaxHeight = height[maxLeft];
            if (leftMaxHeight <= height[left])
            {
                leftMaxHeight = height[left];
                maxLeft = left;
            }

            int64_t rightMaxHeight = height[maxRight];
            if (rightMaxHeight <= height[right])
            {
                rightMaxHeight = height[right];
                maxRight = right;
            }

            if (leftMaxHeight < rightMaxHeight)
            {
                result += leftMaxHeight - height[left];
                ++left;
            }
            else
            {
                result += rightMaxHeight - height[right];
                --right;
            }
        }

        return result;
    }

    int trapByCal(const std::vector<int>& height)
    {
        std::vector<int64_t> maxLeft;
        maxLeft.resize(height.size());

        int64_t max = -1;
        for (int64_t i = 0; i < static_cast<int64_t>(height.size()); ++i)
        {
            if (height[i] >= max)
            {
                max = height[i];
                maxLeft[i] = height[i];
            }
            else
            {
                maxLeft[i] = max;
            }
        }

        std::vector<int64_t> maxRight;
        maxRight.resize(height.size());

        max = -1;
        for (int64_t i = height.size() - 1; i >= 0; --i)
        {
            if (height[i] > max)
            {
                max = height[i];
                maxRight[i] = height[i];
            }
            else
            {
                maxRight[i] = max;
            }
        }

        int64_t result = 0;
        for (int64_t i = 0; i < static_cast<int64_t>(height.size()); ++i)
        {
            int64_t h = std::min(maxLeft[i], maxRight[i]);
            assert(h >= height[i]);

            result += h - height[i];
        }

        return result;
    }

    int trapByStack(const std::vector<int>& height)
    {
        int64_t result = 0;

        std::vector<int64_t> stack;
        stack.reserve(height.size());
        for (int64_t i = 0; i < static_cast<int64_t>(height.size()); ++i)
        {
            int64_t h = height[i];

            int64_t baseHeight = 0;
            while (!stack.empty() && h >= height[stack.back()])
            {
                assert(height[stack.back()] >= baseHeight);
                int64_t diff = height[stack.back()] - baseHeight;
                assert(i > stack.back());
                int64_t width = i - stack.back() - 1;
                result += diff * width;

                baseHeight = height[stack.back()];
                stack.pop_back();
            }
            if (!stack.empty())
            {
                int64_t diff = h - baseHeight;
                int64_t width = i - stack.back() - 1;
                result += diff * width;
            }

            stack.push_back(i);
        }

        return result;
    }
};

TEST(TrapingRainWater, simple)
{
    Solution solution;

    EXPECT_EQ(6, solution.trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}));
    EXPECT_EQ(9, solution.trap({4, 2, 0, 3, 2, 5}));
}

DEFINE_MAIN
