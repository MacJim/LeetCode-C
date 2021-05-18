/*
 * 83. Remove Duplicates from Sorted List
 * https://leetcode.com/problems/remove-duplicates-from-sorted-list/
 */

#include <iostream>
#include <vector>

#include "helpers/ListNode.hpp"
#include "helpers/Operators.hpp"


#pragma mark - 1
/*
 * Actually I should have just compared `current->val` and `current->next->val`.
 *
 * The `dummyHead` is also extraneous.
 */
// Runtime: 12 ms, faster than 40.59% of C++ online submissions for Remove Duplicates from Sorted List.
// Memory Usage: 11.6 MB, less than 20.13% of C++ online submissions for Remove Duplicates from Sorted List.
class Solution1 {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if ((!head) || (!head->next)) {
            return head;
        }

        auto dummyHead = new ListNode(6);
        dummyHead->next = head;

        auto current = dummyHead;

        while (current->next->next) {
            if (current->next->val == current->next->next->val) {
                current->next->next = current->next->next->next;
            } else {
                current = current->next;
            }
        }

        return dummyHead->next;
    }
};


#pragma mark - 2. Simplifies 1
// Runtime: 4 ms, faster than 98.72% of C++ online submissions for Remove Duplicates from Sorted List.
// Memory Usage: 11.6 MB, less than 62.89% of C++ online submissions for Remove Duplicates from Sorted List.
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if ((!head) || (!head->next)) {
            return head;
        }

        auto current = head;

        while (current->next) {
            if (current->val == current->next->val) {
                current->next = current->next->next;
            } else {
                current = current->next;
            }
        }

        return head;
    }
};


void test(const std::vector<int>& listVec, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto head = ListHelper::deserialize(listVec);
    auto result = solutionInstance.deleteDuplicates(head);
    auto resultVec = ListHelper::serialize(result);

    if (resultVec == expectedResult) {
        std::cout << "[Correct] " << listVec << ": " << resultVec << std::endl;
    } else {
        std::cout << "[Wrong] " << listVec << ": " << resultVec << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,1,2}, {1,2});
    test({1,1,2,3,3}, {1,2,3});
    test({1,3,3,3,3,3,3,3}, {1,3});
    test({1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3}, {1,2,3});

    return 0;
}
