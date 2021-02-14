#include "leetcode.h"

/*
 * https://leetcode-cn.com/problems/binary-tree-level-order-traversal/
 *
 * Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 *
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 *
 * return its level order traversal as:
 *
 * [
 *   [3],
 *   [9,20],
 *   [15,7]
 * ]
 *
 */

using TreeNode = TreeNodeBase<int>;

class Solution {
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if (root == nullptr) {
            return result;
        }

        std::deque<std::pair<std::size_t, TreeNode*>> container = {{0, root}};

        std::vector<int> adding;
        std::size_t adding_depth = 0;
        while (!container.empty()) {
            std::size_t depth = SIZE_MAX;
            TreeNode* node = nullptr;
            std::tie(depth, node) = container.front();
            container.pop_front();
            assert(depth != SIZE_MAX);
            assert(node != nullptr);

            if (depth != adding_depth) {
                assert(depth == (adding_depth + 1));
                result.emplace_back(std::move(adding));
                adding_depth = depth;
            }

            (void)adding.emplace_back(node->val);
            if (nullptr != node->left) {
                (void)container.emplace_back(depth + 1, node->left);
            }
            if (nullptr != node->right) {
                (void)container.emplace_back(depth + 1, node->right);
            }
        }
        assert(!adding.empty());
        result.emplace_back(std::move(adding));

        return result;
    }
};

TEST(BinaryTreeLevelOrderTraversal, simple) {
    Solution solution;

    {
        std::array<TreeNode, 5> nodes = {-10, 9, 20, 15, 7};

        TreeNode* root = &nodes.at(0);
        root->left = &nodes.at(1);
        root->right = &nodes.at(2);
        root->right->left = &nodes.at(3);
        root->right->right = &nodes.at(4);

        auto output = solution.levelOrder(root);
        decltype(output) expect_output = {{-10}, {9, 20}, {15, 7}};

        print(std::make_tuple(root), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

}

DEFINE_MAIN
