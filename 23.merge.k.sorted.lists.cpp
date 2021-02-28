#include "leetcode.h"
#include <algorithm>
#include <queue>

/*
 * 23. Merge k Sorted Lists
 *
 * https://leetcode-cn.com/problems/merge-k-sorted-lists/
 *
 * You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
 *
 * Merge all the linked-lists into one sorted linked-list and return it.
 *
 * Example 1:
 *
 * Input: lists = [[1,4,5],[1,3,4],[2,6]]
 * Output: [1,1,2,3,4,4,5,6]
 * Explanation: The linked-lists are:
 * [
 *   1->4->5,
 *   1->3->4,
 *   2->6
 * ]
 * merging them into one sorted list:
 * 1->1->2->3->4->4->5->6
 *
 *
 * Example 2:
 *
 * Input: lists = []
 * Output: []
 *
 *
 * Example 3:
 *
 * Input: lists = [[]]
 * Output: []
 *
 *
 * Constraints:
 *
 *     k == lists.length
 *     0 <= k <= 10^4
 *     0 <= lists[i].length <= 500
 *     -10^4 <= lists[i][j] <= 10^4
 *     lists[i] is sorted in ascending order.
 *     The sum of lists[i].length won't exceed 10^4.
 *
 **/

using ListNode = ListNodeBase<int>;

class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }

        struct ListNodeCompare {
            bool operator()(const ListNode* const a, const ListNode* const b) {
                if (a == nullptr) {
                    return true;
                }
                if (b == nullptr) {
                    return false;
                }

                return a->val > b->val;
            }
        } comp;
        std::make_heap(lists.begin(), lists.end(), comp);

        ListNode* head = nullptr;
        ListNode* prev = nullptr;
        {
            auto min = *(lists.begin());
            if (min == nullptr) {
                return nullptr;
            }
            head = min;
            prev = min;

            std::pop_heap(lists.begin(), lists.end(), comp);
            *std::prev(lists.end()) = min->next;
            std::push_heap(lists.begin(), lists.end(), comp);
        }
        assert(head != nullptr);
        assert(prev != nullptr);

        for (auto min = *(lists.begin()); min != nullptr; min = *(lists.begin())) {
            prev->next = min;
            prev = min;
            std::pop_heap(lists.begin(), lists.end(), comp);
            *std::prev(lists.end()) = min->next;
            std::push_heap(lists.begin(), lists.end(), comp);
        }

        return head;
    }
};

TEST(MergeKSortedLists, simple) {
    Solution solution;

    {
        auto list1 = new ListNode({1, 4, 5});
        auto list2 = new ListNode({1, 3, 4});
        auto list3 = new ListNode({2, 6});
        std::vector<ListNode*> input = {list1, list2, list3};

        std::cout << "Input: List1:" << print_list(list1)
                << ", List2:" << print_list(list2)
                << ", List3:" << print_list(list3) << std::endl;
        auto output = solution.mergeKLists(input);
        std::cout << "Output:" << print_list(output) << std::endl;

        auto expect_output = new ListNode({1, 1, 2, 3, 4, 4, 5, 6});
        std::cout << "Expect:" << print_list(expect_output) << std::endl;

        EXPECT_EQ(*output, *expect_output);

        delete output;
        delete expect_output;
    }

    {
        std::vector<ListNode*> input;
        auto output = solution.mergeKLists(input);
        ListNode* expect_output = nullptr;

        print(std::make_tuple(input), output, expect_output);
    }

    {
        std::vector<ListNode*> input = {nullptr};
        auto output = solution.mergeKLists(input);
        ListNode* expect_output = nullptr;

        print(std::make_tuple(input), output, expect_output);
    }
}

DEFINE_MAIN
