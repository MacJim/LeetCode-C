/*
 * 234. Palindrome Linked List
 * https://leetcode.com/problems/palindrome-linked-list/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/ListNode.hpp"


#pragma mark - Find middle, reverse 2nd half, compare
// Runtime: 20 ms, faster than 72.36% of C++ online submissions for Palindrome Linked List.
// Memory Usage: 13.8 MB, less than 96.00% of C++ online submissions for Palindrome Linked List.
class Solution {
private:
    ListNode* findMid(ListNode* head) {
        auto slow = head;
        auto fast = head;

        while (fast) {
            slow = slow->next;
            fast = fast->next;
            if (!fast) {
                return slow;
            }
            fast = fast->next;
            if (!fast) {
                return slow;
            }
        }

        return nullptr;
    }

    ListNode* reverse(ListNode* head) {
        if ((head == nullptr) || (head->next == nullptr)) {
            return head;
        }

        auto previous = head;
        auto current = head->next;
        head->next = nullptr;

        while (current) {
            auto newCurrent = current->next;

            current->next = previous;

            previous = current;
            current = newCurrent;
        }

        return previous;
    }

public:
    bool isPalindrome(ListNode* head) {
        if ((head == nullptr) || (head->next == nullptr)) {
            return true;
        }

        auto mid = findMid(head);
        mid = reverse(mid);

        while (head && mid) {
            if (head->val != mid->val) {
                return false;
            }

            head = head->next;
            mid = mid->next;
        }

        return true;
    }
};


void test(const std::vector<int>& listStr, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto head = ListHelper::deserialize(listStr);
    auto result = solutionInstance.isPalindrome(head);

    if (result == expectedResult) {
        std::cout << "[Correct] " << listStr << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << listStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,2,1}, true);
    test({1,2,2,1}, true);
    test({1,2}, false);
    test({1,2,2,2}, false);
    test({1,2,3,2,2}, false);

    return 0;
}
