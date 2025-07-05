#include "leetcode.h"

/*
 * A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in
 * the sequence has an edge connecting them. A node can only appear in the sequence at most
 * once. Note that the path does not need to pass through the root.
 * 
 * The path sum of a path is the sum of the node's values in the path.
 * 
 * Given the root of a binary tree, return the maximum path sum of any non-empty path.
 *
 * Input: root = [1,2,3]
 * Output: 6
 * Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
 *
 * Input: root = [-10,9,20,null,null,15,7]
 * Output: 42
 * Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
 *
 */

using TreeNode = TreeNodeBase<int>;

class Solution
{
public:
    int maxPathSum(TreeNode* root)
    {
        auto result = this->tranverseTree(root);
        return result.second;
    }

    std::pair<int64_t, int64_t> tranverseTree(TreeNode* current)
    {
        if (current == NULL)
        {
            return {0, INT64_MIN};
        }

        std::pair<int64_t, int64_t> left = tranverseTree(current->left);
        std::pair<int64_t, int64_t> right = tranverseTree(current->right);

        int64_t maxEndCurrnet = std::max(left.first, right.first);
        if (maxEndCurrnet < 0)
        {
            maxEndCurrnet = 0;
        }
        maxEndCurrnet += current->val;

        int64_t maxSum = std::max(left.second, right.second);
        int64_t maxSumIncludeSelf = current->val;
        if (left.first > 0)
        {
            maxSumIncludeSelf += left.first;
        }
        if (right.first > 0)
        {
            maxSumIncludeSelf += right.first;
        }
        maxSum = std::max(maxSum, maxSumIncludeSelf);
        return {maxEndCurrnet, maxSum};
    }
};

TEST(BinaryTreeMaximumPathSum, simple)
{
    Solution solution;

    {
        std::vector<TreeNode> nodes = {1, 2, 3};
        TreeNode* root = &nodes[0];
        root->left = &nodes[1];
        root->right = &nodes[2];

        EXPECT_EQ(6, solution.maxPathSum(root));
    }

    {
        std::vector<TreeNode> nodes = {-10, 9, 20, 15, 7};
        TreeNode* root = &nodes[0];
        root->left = &nodes[1];
        root->right = &nodes[2];
        root->right->left = &nodes[3];
        root->right->right = &nodes[4];

        EXPECT_EQ(42, solution.maxPathSum(root));
    }
}

DEFINE_MAIN
