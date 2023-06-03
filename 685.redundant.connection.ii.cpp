#include "leetcode.h"

/*
 * https://leetcode.cn/problems/redundant-connection-ii/
 * 
 * In this problem, a rooted tree is a directed graph such that, there is exactly one node
 * (the root) for which all other nodes are descendants of this node, plus every node has
 * exactly one parent, except for the root node which has no parents.
 *
 * The given input is a directed graph that started as a rooted tree with n nodes
 * (with distinct values from 1 to n), with one additional directed edge added. The added
 * edge has two different vertices chosen from 1 to n, and was not an edge that already
 * existed.
 *
 * The resulting graph is given as a 2D-array of edges. Each element of edges is a pair
 * [ui, vi] that represents a directed edge connecting nodes ui and vi, where ui is a
 * parent of child vi.
 *
 * Return an edge that can be removed so that the resulting graph is a rooted tree of n
 * nodes. If there are multiple answers, return the answer that occurs last in the given
 * 2D-array.
 *
 * Example 1:
 * Input: edges = [[1,2],[1,3],[2,3]]
 * Output: [2,3]
 *
 * Example 2:
 * Input: edges = [[1,2],[2,3],[3,4],[4,1],[1,5]]
 * Output: [4,1]
 *
 * Constraints:
 *   n == edges.length
 *   3 <= n <= 1000
 *   edges[i].length == 2
 *   1 <= ui, vi <= n
 *   ui != vi
 *
 */

class Solution {
public:
    std::vector<int> findRedundantDirectedConnection(
            const std::vector<std::vector<int>>& edges)
    {
        const uint64_t count = edges.size();

        std::vector<uint64_t> parents(count, 0);
        for (uint64_t i = 0; i < count; ++i)
        {
            parents[i] = i;
        }

        std::vector<uint64_t> roots(count, 0);
        for (uint64_t i = 0; i < count; ++i)
        {
            roots[i] = i;
        }

        std::pair<uint64_t, uint64_t> moreParent(UINT64_MAX, UINT64_MAX);
        std::pair<uint64_t, uint64_t> loop(UINT64_MAX, UINT64_MAX);
        for (const auto& e : edges)
        {
            assert(e.size() == 2);
            assert(e[0] > 0);
            const uint64_t p = e[0] - 1;
            assert(p < count);
            assert(e[1] > 0);
            const uint64_t c = e[1] - 1;
            assert(c < count);

            if (parents[c] != c)
            {
                // already has a parent
                assert(moreParent.first == UINT64_MAX);
                assert(moreParent.first == UINT64_MAX);
                moreParent.first = p;
                moreParent.second = c;
                continue;
            }
            else
            {
                parents[c] = p;
            }

            const uint64_t rootP = findRoot(roots, p);
            const uint64_t rootC = findRoot(roots, c);
            if (rootP == rootC)
            {
                assert(loop.first == UINT64_MAX);
                loop.first = p;
                assert(loop.second == UINT64_MAX);
                loop.second = c;
            }
            else
            {
                roots[rootC] = rootP;
            }
        }

        if (moreParent.first == UINT64_MAX)
        {
            return {static_cast<int>(loop.first + 1), static_cast<int>(loop.second + 1)};
        }
        // there is a loop and a node has more than one parent

        if (loop.first == UINT64_MAX) 
        {
            // no loop
            return {static_cast<int>(moreParent.first + 1), static_cast<int>(moreParent.second + 1)};
        }
        else
        {
            // must be {parents[c], c} cause the loop;
            const uint64_t c = moreParent.second;
            return {static_cast<int>(parents[c] + 1), static_cast<int>(c + 1)};
        }
    }

    uint64_t findRoot(std::vector<uint64_t>& roots, const uint64_t i)
    {
        if (roots[i] == i)
        {
            return i;
        }
        else
        {
            const uint64_t result = findRoot(roots, roots[i]);
            roots[i] = result;
            return result;
        }
    }
};

TEST(RedundantDirectedConnectionII, simple)
{
    Solution solution;
    {
        auto result = solution.findRedundantDirectedConnection({{1, 2}, {1, 3}, {2, 3}});
        EXPECT_EQ(result, std::vector<int>({2, 3}));
    }
    {
        auto result = solution.findRedundantDirectedConnection({{1, 2}, {2, 3}, {3, 4},
                {4, 1}, {1, 5}});
        EXPECT_EQ(result, std::vector<int>({4, 1}));
    }
}

DEFINE_MAIN
