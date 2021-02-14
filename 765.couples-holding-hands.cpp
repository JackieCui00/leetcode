#include "leetcode.h"

/*
 * https://leetcode-cn.com/problems/couples-holding-hands/
 *
 * N couples sit in 2N seats arranged in a row and want to hold hands. We want to know the minimum number of swaps so that every couple is sitting side by side. A swap consists of choosing any two people, then they stand up and switch seats.
 *
 *The people and seats are represented by an integer from 0 to 2N-1, the couples are numbered in order, the first couple being (0, 1), the second couple being (2, 3), and so on with the last couple being (2N-2, 2N-1).
 *
 *The couples' initial seating is given by row[i] being the value of the person who is initially sitting in the i-th seat.
 *
 *Example 1:
 *
 *Input: row = [0, 2, 1, 3]
 *Output: 1
 *Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
 *
 *Example 2:
 *
 *Input: row = [3, 2, 0, 1]
 *Output: 0
 *Explanation: All couples are already seated side by side.
 *
 *Note:
 *
 *    len(row) is even and in the range of [4, 60].
 *    row is guaranteed to be a permutation of 0...len(row)-1.
*/

class Solution {
public:
    int minSwapsCouples(std::vector<int>& row) {
        assert(row.size() % 2 == 0);
        std::vector<std::pair<std::size_t, std::size_t>> cluster;
        cluster.resize(row.size() / 2);
        for (std::size_t i = 0; i < row.size() / 2; ++i) {
            cluster.at(i).first = i;
            cluster.at(i).second = 1;
        }

        std::function<std::size_t(const std::size_t)> find_root = [&cluster, &find_root] (const std::size_t num) -> std::size_t {
            const std::size_t parent = cluster.at(num).first;
            if (parent == num) {
                return num;
            }
            const std::size_t root = find_root(parent);
            if (root != cluster.at(num).first) {
                cluster.at(num).first = root;
                cluster.at(root).second += 1;
            }

            return root;
        };

        for (std::size_t i = 0; i < row.size(); i += 2) {
            const int num1 = row.at(i) / 2;
            const std::size_t root1 = find_root(num1);

            const int num2 = row.at(i + 1) / 2;
            const std::size_t root2 = find_root(num2);

            if (root1 != root2) {
                if (cluster.at(root1).second < cluster.at(root2).second) {
                    cluster.at(root1).first = root2;
                    cluster.at(root2).second += 1;
                } else {
                    cluster.at(root2).first = root1;
                    cluster.at(root1).second += 1;
                }
            }
        }

        for (std::size_t i = 0; i < cluster.size(); ++i) {
            (void)find_root(i);
        }

        std::size_t result = 0;
        for (std::size_t i = 0; i < cluster.size(); ++i) {
            if (cluster.at(i).first == i) {
                result += cluster.at(i).second - 1;
            }
        }

        return result;
    }
};

TEST(CouplesHoldingHands, simple) {
    Solution solution;

    {
        std::vector<int> input = {0, 2, 1, 3};
        int output = solution.minSwapsCouples(input);
        constexpr int expect_output = 1;

        print(std::make_tuple(input), output, expect_output);
        ASSERT_EQ(expect_output, output) << "input:" << input;
    }

    {
        std::vector<int> input = {3, 2, 0, 1};
        int output = solution.minSwapsCouples(input);
        constexpr int expect_output = 0;

        print(std::make_tuple(input), output, expect_output);
        ASSERT_EQ(expect_output, output) << "input:" << input;
    }
}

DEFINE_MAIN
