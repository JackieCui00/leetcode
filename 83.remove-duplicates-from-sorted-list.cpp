#include "leetcode.h"
#include <tuple>

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
        ListNode *prev = head;
        ListNode *node = NULL;

        if (NULL == head) return NULL;

        for (node = prev->next; NULL != node; node = prev->next) {
            if (prev->val == node->val) {
                prev->next = node->next;
                delete node;
            }else {
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
        print(std::make_tuple(input), output, output); // TODO
    }

    {
        std::array<ListNode, 5> nodes = {1, 1, 2, 3, 3};
        ListNode* input = &nodes.at(0);
        nodes.at(0).next = &nodes.at(1);
        nodes.at(1).next = &nodes.at(2);
        nodes.at(2).next = &nodes.at(3);
        nodes.at(3).next = &nodes.at(4);

        ListNode* output = solution.deleteDuplicates(input);
        print(std::make_tuple(input), output, output); // TODO
    }
}

DEFINE_MAIN
