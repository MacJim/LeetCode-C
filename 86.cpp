/*
 * 86. Partition List
 * https://leetcode.com/problems/partition-list/
 */

#include <iostream>
#include <vector>

#include "helpers/ListNode.hpp"
#include "helpers/Operators.hpp"


#pragma mark - 1. Move in place
// Runtime: 4 ms, faster than 88.86% of C++ online submissions for Partition List.
// Memory Usage: 10.2 MB, less than 92.65% of C++ online submissions for Partition List.
class Solution {
private:
    inline void moveBiggerChain(ListNode* biggerPrevious, ListNode* biggerLast, ListNode* smallerLast) const {
        if (!biggerPrevious) {
            // No bigger sequence.
            return;
        }

        auto biggerFirst = biggerPrevious->next;
        auto smallerFirst = biggerLast->next;

        // Swap.
        biggerPrevious->next = smallerFirst;
        biggerLast->next = smallerLast->next;
        smallerLast->next = biggerFirst;
    }

public:
    ListNode* partition(ListNode* head, int threshold) {
        // Empty list.
        if ((!head) || (!head->next)) {
            return head;
        }

        auto dummyHead = new ListNode(21);
        dummyHead->next = head;

        ListNode* biggerPrevious = (head->val >= threshold)? dummyHead: nullptr;
//        ListNode* biggerFirst = nullptr;
        ListNode* biggerLast = (head->val >= threshold)? head: nullptr;

//        ListNode* smallerPrevious = nullptr;
//        ListNode* smallerFirst = nullptr;
        ListNode* smallerLast = nullptr;

        auto previous = dummyHead;
        auto current = head;
        while (current) {
            if (current->val >= threshold) {
                // Current node is bigger.
                if (smallerLast) {
                    // We have a previous unfulfilled smaller chain.
                    moveBiggerChain(biggerPrevious, biggerLast, smallerLast);

                    // Reset values.
                    biggerPrevious = smallerLast;
                    smallerLast = nullptr;
                }

                if (biggerPrevious) {
                    // Continue on the previous bigger node chain.
                    biggerLast = current;
                } else {
                    // Create a new bigger node chain.
                    // This is supposed to be called only once.
                    biggerPrevious = previous;
                    biggerLast = current;
                }
            } else {
                // Current node is smaller.
                if (biggerPrevious) {
                    // If we have previous bigger nodes.
                    // We must log the smaller nodes.
                    smallerLast = current;
                }
            }

            previous = current;
            current = current->next;
        }

        // The final element is smaller.
        if (smallerLast) {
            // We have a previous unfulfilled smaller chain.
            moveBiggerChain(biggerPrevious, biggerLast, smallerLast);
        }

        return dummyHead->next;
    }
};


void test(const std::vector<int>& listStr, const int x, const std::vector<int>& expectedResultStr) {
    static auto solutionInstance = Solution();

    auto head = ListHelper::deserialize(listStr);
    auto result = solutionInstance.partition(head, x);

    auto resultStr = ListHelper::serialize(result);

    if (resultStr == expectedResultStr) {
        std::cout << "[Correct] " << listStr << ", " << x << ": " << resultStr << std::endl;
    } else {
        std::cout << "[Wrong] " << listStr << ", " << x << ": " << resultStr << " (should be " << expectedResultStr << ")" << std::endl;
    }
}


int main() {
    test({1,4,3,2,5,2}, 3, {1,2,2,4,3,5});
    test({2,1}, 2, {1,2});
    test({1,5,6,7,8,9,2,3,4}, 5, {1,2,3,4,5,6,7,8,9});

    return 0;
}
