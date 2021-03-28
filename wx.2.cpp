/*
 2、给一棵二叉树，每个结点上有一个不同的整数值val，一个子树上所有节点数值的总和称为子树和，求最大子树和。
 例如树节点数值如下图，最大子树和为1+4+7=12。
      3
    /  \
   1   -5
   / \
 4    7

 数据结构：
 Strutc Tree {
     Tree* lch;
     Tree* rch;
     int val;
 };
 实现函数：int MaxSubTreeSum(Tree* root);
*/

#include <iostream>

#include <gtest/gtest.h>
#include <utility>
#include <vector>

struct Tree {
    Tree* lch;
    Tree* rch;
    int val;

    explicit Tree(const int val_) : lch(nullptr), rch(nullptr), val(val_) {}
};

std::pair<int, int> MaxSubTreeSumImpl(const Tree* const root) {
    if (nullptr == root) {
        return std::make_pair(0, 0);
    }

    auto left = MaxSubTreeSumImpl(root->lch);
    auto right = MaxSubTreeSumImpl(root->rch);

    int result = root->val + left.second + right.second;
    return std::make_pair(std::max({left.first, right.first, result}), result);
}

int MaxSubTreeSum(Tree* root) {
    auto result = MaxSubTreeSumImpl(root);
    return result.first;
}

TEST(MaxSubTreeSum, simple) {
    {
        std::vector<Tree> nodes = {Tree(3), Tree(1), Tree(-5), Tree(4), Tree(7)};
        nodes[0].lch = &nodes[1];
        nodes[0].rch = &nodes[2];
        nodes[1].lch = &nodes[3];
        nodes[1].rch = &nodes[4];

        ASSERT_EQ(MaxSubTreeSum(&nodes[0]), 12);
    }
}

int main(int argc, char* argv[]) {
    ::testing::FLAGS_gtest_color="true";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
