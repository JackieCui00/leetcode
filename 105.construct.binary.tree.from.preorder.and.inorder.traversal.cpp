#include "leetcode.h"

/*
 *
 * Given two integer arrays preorder and inorder where preorder is the preorder traversal
 * of a binary tree and inorder is the inorder traversal of the same tree,
 * construct and return the binary tree.
 *
 * Example 1:
 * Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
 * Output: [3,9,20,null,null,15,7]
 *
 * Example 2:
 * Input: preorder = [-1], inorder = [-1]
 * Output: [-1]
 *
 * Constraints:
 * - 1 <= preorder.length <= 3000
 * - inorder.length == preorder.length
 * - -3000 <= preorder[i], inorder[i] <= 3000
 * - preorder and inorder consist of unique values.
 * - Each value of inorder also appears in preorder.
 * - preorder is guaranteed to be the preorder traversal of the tree.
 * - inorder is guaranteed to be the inorder traversal of the tree.
 *
 */

using TreeNode = TreeNodeBase<int>;

class Solution
{
public:
    TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder)
    {
        mPreorder = &preorder;
        mInorder = &inorder;

        auto result = this->traversal(0, {0, inorder.size() - 1});
        return result.first;
    }

    std::pair<TreeNode*, int> traversal(int preorder, std::pair<int, int> inorder)
    {
        if (inorder.first == inorder.second)
        {
            return {new TreeNode((*mInorder)[inorder.first]), preorder + 1};
        }

        auto root = new TreeNode((*mPreorder)[preorder]);
        preorder += 1;

        int split = inorder.first;
        while (split <= inorder.second)
        {
            if ((*mInorder)[split] == root->val)
            {
                break;
            }
            ++split;
        }

        if (split == inorder.first)
        {
            root->left = nullptr;
        }
        else
        {
            auto result = this->traversal(preorder, {inorder.first, split - 1});
            root->left = result.first;
            preorder = result.second;
        }

        if (split == inorder.second)
        {
            root->right = nullptr;
        }
        else
        {
            auto result = this->traversal(preorder, {split + 1, inorder.second});
            root->right = result.first;
            preorder = result.second;
        }

        return {root, preorder};
    }

private:
    const std::vector<int>* mPreorder;
    const std::vector<int>* mInorder;
};

TEST(ConstructBinaryTreeFromPreorderAndInorderTraversal, simple)
{
    Solution solution;

    {
        auto result = solution.buildTree({3, 9, 20, 15, 7}, {9, 3, 15, 20, 7});
        EXPECT_EQ(result->val, 3);
        EXPECT_EQ(result->left->val, 9);
        EXPECT_EQ(result->right->val, 20);
        EXPECT_EQ(result->right->left->val, 15);
        EXPECT_EQ(result->right->right->val, 7);
    }
}

DEFINE_MAIN
