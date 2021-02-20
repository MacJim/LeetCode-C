/*
 * 148. Sort List
 * https://leetcode.com/problems/sort-list/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/ListNode.hpp"


#pragma mark - 1. Merge sort
// Runtime: 80 ms, faster than 95.51% of C++ online submissions for Sort List.
// Memory Usage: 29.2 MB, less than 77.57% of C++ online submissions for Sort List.
class Solution {
private:
    ListNode* getMid(ListNode* head) {
        auto slow = head;
        auto fast = head;

        while (true) {
            fast = fast->next;
            if (!fast) {
                auto returnValue = slow->next;
                slow->next = nullptr;
                return returnValue;
            }
            fast = fast->next;
            if (!fast) {
                auto returnValue = slow->next;
                slow->next = nullptr;
                return returnValue;
            }
            slow = slow->next;
        }
    }

    ListNode* merge(ListNode* h1, ListNode* h2) {
        ListNode* head = nullptr;
        if (h1->val < h2->val) {
            head = h1;
            h1 = h1->next;
        } else {
            head = h2;
            h2 = h2->next;
        }

        ListNode* current = head;
        while (h1 && h2) {
            if (h1->val < h2->val) {
                current->next = h1;
                h1 = h1->next;
            } else {
                current->next = h2;
                h2 = h2->next;
            }
            current = current->next;
        }

        if (h1) {
            current->next = h1;
        }
        if (h2) {
            current->next = h2;
        }

        return head;
    }

    ListNode* sortRecursively(ListNode* head) {
        if (head->next == nullptr) {
            return head;
        }

        auto mid = getMid(head);
        auto left = sortRecursively(head);
        auto right = sortRecursively(mid);
        auto newHead = merge(left, right);
        return newHead;
    }

public:
    ListNode* sortList(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        return sortRecursively(head);
    }
};


void test(const std::vector<int>& listVec, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto head = ListHelper::deserialize(listVec);
    auto result = solutionInstance.sortList(head);
    auto resultVec = ListHelper::serialize(result);

    if (resultVec == expectedResult) {
        std::cout << "[Correct] " << listVec << ": " << resultVec << std::endl;
    } else {
        std::cout << "[Wrong] " << listVec << ": " << resultVec << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({4,2,1,3}, {1,2,3,4});
    test({5,2,3,1,4}, {1,2,3,4,5});

    return 0;
}
