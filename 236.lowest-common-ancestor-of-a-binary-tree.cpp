#include "leetcode.h"

/*
 * [236] Lowest Common Ancestor of a Binary Tree
 *
 * https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/
 *
 * algorithms
 * Medium (30.02%)
 * Total Accepted:    179.3K
 * Total Submissions: 585.6K
 * Testcase Example:  '[3,5,1,6,2,0,8,null,null,7,4]\n5\n4'
 *
 * Given a binary tree, find the lowest common ancestor (LCA) of two given
 * nodes in the tree.
 *
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor
 * is defined between two nodes p and q as the lowest node in T that has both p
 * and q as descendants (where we allow a node to be a descendant of itself).”
 *
 * Given the following binary tree:  root = [3,5,1,6,2,0,8,null,null,7,4]
 *
 *
 * ⁠       _______3______
 * ⁠      /              \
 * ⁠   ___5__          ___1__
 * ⁠  /      \        /      \
 * ⁠  6      _2       0       8
 * ⁠        /  \
 * ⁠        7   4
 *
 *
 * Example 1:
 *
 *
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
 * Output: 3
 * Explanation: The LCA of of nodes 5 and 1 is 3.
 *
 *
 * Example 2:
 *
 *
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
 * Output: 5
 * Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant
 * of itself
 * ⁠            according to the LCA definition.
 *
 * Note:
 *
 *
 * All of the nodes' values will be unique.
 * p and q are different and both values will exist in the binary tree.
 *
 *
 */

using TreeNode = TreeNodeBase<int>;

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (p == q) {
            return p;
        }
        if (p == root || q == root) {
            return root;
        }

        auto result = find(root, p, q);
        assert(result.first == 2);
        return result.second;
    }

    std::pair<int, TreeNode*> find(TreeNode* root, TreeNode* p, TreeNode* q) {
        int result = 0; // 0 for not found, 1 for found 1, 2 for found 2
        TreeNode* node = nullptr;

        if (root == p || root == q) {
            result += 1;
        }

        if (root->left != nullptr) {
            auto left = find(root->left, p, q);
            assert(result + left.first <= 2);
            if (left.first == 2) {
                node = left.second;
            }
            result += left.first;
        }
        if (root->right != nullptr) {
            auto right = find(root->right, p, q);
            assert(result + right.first <= 2);
            if (right.first == 2) {
                node = right.second;
            }
            result += right.first;
        }

        if (result == 2 && node == nullptr) {
            node = root;
        }

        return std::make_pair(result, node);
    }

    TreeNode* lowestCommonAncestor_brilliant(TreeNode* root, TreeNode* p, TreeNode* q) {
        // this is very tricky
        // actually return root here only sees one of p/q is in Tree

        if (p == root || q == root || nullptr == root) {
            return root;
        }

        TreeNode* left = lowestCommonAncestor_brilliant(root, p, q);
        TreeNode* right = lowestCommonAncestor_brilliant(root, p, q);

        // ATTENTION: left != nullptr && right != nullptr -> root
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr) {
            return left;
        }

        return root;
    }
};

TEST(LowestCommonAncestorOfABinaryTree, simple) {
    Solution solution;

    std::array<TreeNode, 9> nodes = {3, 5, 1, 6, 2, 0, 8, 7, 4};
    TreeNode* root = &nodes.at(0);
    root->left = &nodes.at(1);
    root->right = &nodes.at(2);
    root->left->left = &nodes.at(3);
    root->left->right = &nodes.at(4);
    root->right->left = &nodes.at(5);
    root->right->right = &nodes.at(6);
    root->left->right->left = &nodes.at(7);
    root->left->right->right = &nodes.at(8);

    {
        TreeNode* p = root->left;
        TreeNode* q = root->right;

        TreeNode* output = solution.lowestCommonAncestor(root, p, q);
        TreeNode* expect_output = root;

        print(std::make_tuple(print_tree(root), p, q), output, expect_output);
    }

    {
        TreeNode* p = root->left;
        TreeNode* q = root->left->right->right;

        TreeNode* output = solution.lowestCommonAncestor(root, p, q);
        TreeNode* expect_output = root->left;

        print(std::make_tuple(print_tree(root), p, q), output, expect_output);
    }

    {
        TreeNode* p = root->left->left;
        TreeNode* q = root->left->right->right;

        TreeNode* output = solution.lowestCommonAncestor(root, p, q);
        TreeNode* expect_output = root->left;

        print(std::make_tuple(print_tree(root), p, q), output, expect_output);
    }
}

DEFINE_MAIN
