#include "leetcode.h"

/*
 * A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.
 *
 * The path sum of a path is the sum of the node's values in the path.
 *
 * Given the root of a binary tree, return the maximum path sum of any path.
 *
 * Example 1:
 *
 * Input: root = [1,2,3]
 * Output: 6
 * Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
 *
 * Example 2:
 *
 * Input: root = [-10,9,20,null,null,15,7]
 * Output: 42
 * Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
 *
 * Constraints:
 *
 *     The number of nodes in the tree is in the range [1, 3 * 104].
 *     -1000 <= Node.val <= 1000
 *
 */

using TreeNode = TreeNodeBase<int>;

class Solution {
public:
    std::pair<int, int> find_max(TreeNode* root) {
        assert(nullptr != root);

        int left_max = std::numeric_limits<int>::min();
        int left_depth = std::numeric_limits<int>::min();
        if (root->left != nullptr) {
            std::tie(left_max, left_depth) = find_max(root->left);
        }

        int right_max = std::numeric_limits<int>::min();
        int right_depth = std::numeric_limits<int>::min();
        if (root->right != nullptr) {
            std::tie(right_max, right_depth) = find_max(root->right);
        }

        int max = std::max(left_max, right_max);
        {
            int tmp_max = root->val;
            if (left_depth > 0) {
                tmp_max += left_depth;
            }
            if (right_depth > 0) {
                tmp_max += right_depth;
            }
            max = std::max(max, tmp_max);
        }

        int depth = std::max(left_depth, right_depth);
        depth = depth < 0 ? root->val : depth + root->val;

        return std::make_pair(max, depth);
    }

    int maxPathSum(TreeNode* root) {
        auto result = find_max(root);
        return result.first;
    }
};

TEST(BinaryTreeMaximumPathSum, simple) {
    Solution solution;

    {
        std::array<TreeNode, 5> nodes = {-10, 9, 20, 15, 7};

        TreeNode* root = &nodes.at(0);
        root->left = &nodes.at(1);
        root->right = &nodes.at(2);
        root->right->left = &nodes.at(3);
        root->right->right = &nodes.at(4);

        auto output = solution.find_max(root);
        decltype(output) expect_output = {42, 25};

        print(std::make_tuple(root), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
