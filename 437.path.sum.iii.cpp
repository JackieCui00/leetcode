#include "leetcode.h"

/*
 * 437. Path Sum III
 * Given the root of a binary tree and an integer targetSum, return the number of paths
 * where the sum of the values along the path equals targetSum.
 * The path does not need to start or end at the root or a leaf, but it must go
 * downwards (i.e., traveling only from parent nodes to child nodes).
 *
 * Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
 * Output: 3
 * Explanation: The paths that sum to 8 are shown.
 *
 * Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
 * Output: 3
 *
 */

using TreeNode = TreeNodeBase<int>;

class Solution
{
public:
    int pathSum(TreeNode* root, int targetSum)
    {
        if (root == nullptr)
        {
            // TODO(cuijiacheng.cjc) whatif targetSum == 0
            return 0;
        }

        std::vector<int64_t> stack;
        stack.push_back(0);
        int result = 0;
        this->tranverseTree(root, targetSum, &stack, &result);
        return result;
    }

    void tranverseTree(TreeNode* current, const int target, std::vector<int64_t>* stack, int* result)
    {
        stack->push_back(stack->back() + current->val);
        *result += this->findTarget(stack, target);

        if (current->left != nullptr)
        {
            tranverseTree(current->left, target, stack, result);
        }
        if (current->right != nullptr)
        {
            tranverseTree(current->right, target, stack, result);
        }
        stack->pop_back();
    }

    int findTarget(std::vector<int64_t>* stack, const int target)
    {
        assert(stack->size() >= 2);
        const int64_t sum = stack->back();
        int result = 0;
        for (auto iter = stack->rbegin() + 1; iter != stack->rend(); ++iter)
        {
            if (sum - *iter == target)
            {
                ++result;
            }
        }
        return result;
    }
};

TEST(PathSumIII, simple)
{
    Solution solution;
    {
        std::array<TreeNode, 9> nodes = {10,5,-3,3,2,11,3,-2,1};
        TreeNode* root = &nodes[0];
        root->left = &nodes[1];
        root->right = &nodes[2];
        root->left->left = &nodes[3];
        root->left->right = &nodes[4];
        root->right->right = &nodes[5];
        root->left->left->left = &nodes[6];
        root->left->left->right = &nodes[7];
        root->left->right->right = &nodes[8];

        EXPECT_EQ(3, solution.pathSum(root, 8 /*targetSum*/));
    }
}

DEFINE_MAIN
