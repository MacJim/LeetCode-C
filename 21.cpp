/*
 * 21. Merge Two Sorted Lists
 * https://leetcode.com/problems/merge-two-sorted-lists/
 */

#include <iostream>

#include "helpers/ListNode.hpp"


// Runtime: 8 ms, faster than 90.60% of C++ online submissions for Merge Two Sorted Lists.
// Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for Merge Two Sorted Lists.
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        }
        if (l2 == nullptr) {
            return l1;
        }
        
        auto node1 = l1;
        auto node2 = l2;

        ListNode* head = nullptr;

        if (node1->val > node2->val) {
            head = node2;
            node2 = node2->next;
            if (node2 == nullptr) {
                head->next = node1;
                return head;
            }
        } else {
            head = node1;
            node1 = node1->next;
            if (node1 == nullptr) {
                head->next = node2;
                return head;
            }
        }

        ListNode* previousNode = head;
        while (true) {
            if (node1->val > node2->val) {
                previousNode->next = node2;
                previousNode = node2;

                node2 = node2->next;
                if (node2 == nullptr) {
                    previousNode->next = node1;
                    break;
                }
            } else {
                previousNode->next = node1;
                previousNode = node1;

                node1 = node1->next;
                if (node1 == nullptr) {
                    previousNode->next = node2;
                    break;
                }
            }
        }

        return head;
    }
};

int main() {
    auto solutionInstance = Solution();

    auto list1 = ListHelper::deserialize({1, 2, 4});
    auto list2 = ListHelper::deserialize({1, 3, 4});
    auto result1 = solutionInstance.mergeTwoLists(list1, list2);
    auto resultVector1 = ListHelper::serialize(result1);
    for (const auto& num: resultVector1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
