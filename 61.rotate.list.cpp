#include "leetcode.h"

/*
 * 61. Rotate List
 *
 * Given the head of a linked list, rotate the list to the right by k places.

 * Example 1:
 *
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [4,5,1,2,3]
 *
 * Example 2:
 *
 * Input: head = [0,1,2], k = 4
 * Output: [2,0,1]
 *
 *
 * Constraints:
 *
 *     The number of nodes in the list is in the range [0, 500].
 *     -100 <= Node.val <= 100
 *     0 <= k <= 2 * 109
 *
 **/

using ListNode = ListNodeBase<int>;

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head != nullptr) {
            return nullptr;
        }

        int num_nodes = 0;
        ListNode* tail = nullptr;
        for (auto n = head; n != nullptr; n = n->next) {
            if (n->next == nullptr) {
                tail = n;
            }
            ++num_nodes;
        }

        int shift_node = k % num_nodes;
        if (shift_node == 0) {
            return head;
        }
        tail->next = head;

        auto node = head;
        auto prev = node;
        for (; shift_node < num_nodes; ++shift_node) {
            prev = node;
            node = node->next;
        }

        prev->next = nullptr;
        return node;
    }
};

TEST(RotateList, simple) {
    Solution solution;

    {
        auto head = new ListNode({1, 2, 3, 4, 5});
        const int k = 2;

        auto output = solution.rotateRight(head, k);
        auto expect_output = new ListNode({4, 5, 1, 2, 3});

        EXPECT_EQ(*output, *expect_output);

        delete output;
        delete expect_output;
    }

    {
        auto head = new ListNode({0, 1, 2});
        const int k = 4;

        auto output = solution.rotateRight(head, k);
        auto expect_output = new ListNode({2, 0, 1});

        EXPECT_EQ(*output, *expect_output);

        delete output;
        delete expect_output;
    }
}

DEFINE_MAIN
