#include "leetcode.h"

/*
 * 在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？
 *
 * Example 1:
 * 输入: 
 * [
 *   [1,3,1],
 *   [1,5,1],
 *   [4,2,1]
 * ]
 * 输出: 12
 * 解释: 路径 1→3→5→2→1 可以拿到最多价值的礼物
 */

class Solution {
public:
    int maxValue(std::vector<std::vector<int>>& grid)
    {
        for (std::size_t i = 1; i < grid.size(); ++i)
        {
            grid[i][0] += grid[i - 1][0];
        }
        for (std::size_t i = 1; i < grid[0].size(); ++i)
        {
            grid[0][i] += grid[0][i - 1];
        }

        for (std::size_t i = 1; i < grid.size(); ++i)
        {
            for (std::size_t j = 1; j < grid[0].size(); ++j)
            {
                grid[i][j] += std::max(grid[i-1][j], grid[i][j-1]);
            }
        }

        return grid[grid.size() - 1][grid[0].size() - 1];
    }
};

TEST(MaxGiftValue, simple)
{
    Solution solution;

    {
        auto data = std::vector<std::vector<int>>({{1, 3, 1}, {1, 5, 1}, {4, 2, 1}});
        EXPECT_EQ(12, solution.maxValue(data));
    }
}

DEFINE_MAIN
