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
        ListNode node{1, 1, 2};
        ListNode* input = &node;

        ListNode* output = solution.deleteDuplicates(input);

        ListNode expect_node{1, 2};
        const ListNode* const expect_output = &expect_node;

        print(std::make_tuple(print_list(input)), print_list(output), print_list(expect_output)); // TODO
        EXPECT_EQ(*output, *expect_output);
    }

    {
        ListNode node{1, 1, 2, 3, 3};
        ListNode* input = &node;

        ListNode* output = solution.deleteDuplicates(input);


        ListNode expect_node{1, 2, 3};
        const ListNode* const expect_output = &expect_node;

        print(std::make_tuple(print_list(input)), print_list(output), print_list(expect_output));
        EXPECT_EQ(*output, *expect_output);
    }
}

DEFINE_MAIN
