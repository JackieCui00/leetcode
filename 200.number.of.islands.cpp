#include "leetcode.h"

/*
 * Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water),
 * return the number of islands.
 *
 * An island is surrounded by water and is formed by connecting adjacent lands
 * horizontally or vertically.
 *
 * You may assume all four edges of the grid are all surrounded by water.
 *
 * Example 1:
 *  Input: grid = [
 *    ["1","1","1","1","0"],
 *    ["1","1","0","1","0"],
 *    ["1","1","0","0","0"],
 *    ["0","0","0","0","0"]
 *  ]
 *  Output: 1
 *
 * Example 2:
 * Input: grid = [
 *   ["1","1","0","0","0"],
 *   ["1","1","0","0","0"],
 *   ["0","0","1","0","0"],
 *   ["0","0","0","1","1"]
 * ]
 * Output: 3
 *
 * Constraints:
 * - m == grid.length
 * - n == grid[i].length
 * - 1 <= m, n <= 300
 * - grid[i][j] is '0' or '1'.
 *
 */

class Solution
{
public:
    int numIslands(std::vector<std::vector<char>>& grid)
    {
        int result = 0;
        for (uint64_t i = 0; i < grid.size(); ++i)
        {
            for (uint64_t j = 0; j < grid[0].size(); ++j)
            {
                if (grid[i][j] == '1')
                {
                    ++result;
                    this->traverse(grid, i, j);
                }
            }
        }
        return result;
    }

    void traverse(std::vector<std::vector<char>>& grid, uint64_t i, uint64_t j)
    {
        grid[i][j] = '0';
        if ((i + 1) < grid.size() && grid[i + 1][j] == '1')
        {
            traverse(grid, i + 1, j);
        }
        if (i > 0 && grid[i - 1][j] == '1')
        {
            traverse(grid, i - 1, j);
        }
        if ((j + 1) < grid[0].size() && grid[i][j + 1] == '1')
        {
            traverse(grid, i, j + 1);
        }
        if (j > 0 && grid[i][j - 1] == '1')
        {
            traverse(grid, i , j - 1);
        }
    }
};

TEST(NumberOfIslands, simple)
{
    Solution solution;

    {
        std::vector<std::vector<char>> input = {
            {'1','1','1','1','0'},
            {'1','1','0','1','0'},
            {'1','1','0','0','0'},
            {'0','0','0','0','0'}
        };
        EXPECT_EQ(1, solution.numIslands(input));
    }

    {
        std::vector<std::vector<char>> input = {
            {'1','1','0','0','0'},
            {'1','1','0','0','0'},
            {'0','0','1','0','0'},
            {'0','0','0','1','1'}
        };
        EXPECT_EQ(3, solution.numIslands(input));
    }

    {
        std::vector<std::vector<char>> input = {
            {'1','1','1'},
            {'0','1','0'},
            {'1','1','1'}
        };
        EXPECT_EQ(1, solution.numIslands(input));
    }
}

DEFINE_MAIN
