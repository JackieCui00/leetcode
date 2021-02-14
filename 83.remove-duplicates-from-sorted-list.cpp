#include "leetcode.h"

/*
 * [83] Remove Duplicates from Sorted List
 *
 * https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/
 *
 * Given a sorted linked list, delete all duplicates such that each element
 * appear only once.
 *
 *
 * Example 1:
 *
 * Input: 1->1->2
 * Output: 1->2
 *
 *
 * Example 2:
 *
 * Input: 1->1->2->3->3
 * Output: 1->2->3
 *
 *
 * Constraints:
 *
 *     The number of nodes in the list is in the range [0, 300].
 *     -100 <= Node.val <= 100
 *     The list is guaranteed to be sorted in ascending order.
 *
 */

using ListNode = ListNodeBase<int>;

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (nullptr == head) return nullptr;

        ListNode *prev = head;
        for (ListNode* node = prev->next; nullptr != node; node = prev->next) {
            if (prev->val == node->val) {
                prev->next = node->next;
#ifndef SELF_TEST
                delete node;
#endif
            } else {
                prev = node;
            }
        }

        return head;
    }
};

TEST(RemoveDuplicateFromSortedList, simple) {
    Solution solution;

    {
        std::array<ListNode, 3> nodes = {1, 1, 2};
        ListNode* input = &nodes.at(0);
        nodes.at(0).next = &nodes.at(1);
        nodes.at(1).next = &nodes.at(2);

        ListNode* output = solution.deleteDuplicates(input);

        std::array<ListNode, 2> expect_nodes = {1, 2};
        const ListNode* const expect_output = &expect_nodes.at(0);
        expect_nodes.at(0).next = &expect_nodes.at(1);

        print(std::make_tuple(print_list(input)), print_list(output), print_list(expect_output)); // TODO
        EXPECT_EQ(*output, *expect_output);
    }

    {
        std::array<ListNode, 5> nodes = {1, 1, 2, 3, 3};
        ListNode* input = &nodes.at(0);
        nodes.at(0).next = &nodes.at(1);
        nodes.at(1).next = &nodes.at(2);
        nodes.at(2).next = &nodes.at(3);
        nodes.at(3).next = &nodes.at(4);

        ListNode* output = solution.deleteDuplicates(input);

        std::array<ListNode, 3> expect_nodes = {1, 2, 3};
        const ListNode* const expect_output = &expect_nodes.at(0);
        expect_nodes.at(0).next = &expect_nodes.at(1);
        expect_nodes.at(1).next = &expect_nodes.at(2);

        print(std::make_tuple(print_list(input)), print_list(output), print_list(expect_output));
        EXPECT_EQ(*output, *expect_output);
    }
}

DEFINE_MAIN
