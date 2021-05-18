/*
 * 82. Remove Duplicates from Sorted List II
 * https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
 */

#include <iostream>
#include <vector>

#include "helpers/ListNode.hpp"
#include "helpers/Operators.hpp"


#pragma mark - 1
// Runtime: 8 ms, faster than 57.19% of C++ online submissions for Remove Duplicates from Sorted List II.
// Memory Usage: 11 MB, less than 98.97% of C++ online submissions for Remove Duplicates from Sorted List II.
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if ((!head) || (!head->next)) {
            return head;
        }

        auto dummyHead = new ListNode(6);
        dummyHead->next = head;

        auto current = dummyHead;
        while (current->next && current->next->next) {
            if (current->next->val == current->next->next->val) {
                const auto duplicateVal = current->next->val;

                auto duplicate = current->next->next;
                while (duplicate && (duplicate->val == duplicateVal)) {
                    duplicate = duplicate->next;
                }

                // Now `duplicate` points to the first non-duplicate element.
                current->next = duplicate;
            } else {
                current = current->next;
            }
        }

        return dummyHead->next;
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
    test({1,1,1}, {});
    test({1,1,2,2,2,3,3,3,3,4,4,5,5,6,6,6,7,7}, {});
    test({1,2,3,3,4,4,5}, {1,2,5});
    test({1,1,1,2,3}, {2,3});
    test({1,2,2,2,2,3,4,4,4,5,5}, {1,3});
    test({}, {});

    return 0;
}
