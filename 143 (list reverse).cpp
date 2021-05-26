/*
 * 143. Reorder List
 * https://leetcode.com/problems/reorder-list/
 */

#include <iostream>
#include <vector>

#include "helpers/ListNode.hpp"
#include "helpers/Operators.hpp"


#pragma mark - 1. Reverse the second part
// Runtime: 40 ms, faster than 50.01% of C++ online submissions for Reorder List.
// Memory Usage: 17.8 MB, less than 42.81% of C++ online submissions for Reorder List.
class Solution {
private:
    inline ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        auto current = head;
        auto next = head->next;
        head->next = nullptr;

        while (next) {
            auto nextNext = next->next;

            next->next = current;

            current = next;
            next = nextNext;
        }

        return current;
    }

public:
    void reorderList(ListNode* head) {
        if (!head || !head->next || !head->next->next) {
            // Too few nodes.
            return;
        }

        // Get the middle node.
        auto slow = head;
        auto fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        auto part1End = slow;
        auto part2Start = slow->next;
        part1End->next = nullptr;

        auto reversedPart2 = reverseList(part2Start);

        // Insert `p2` between `previous` and `next`.
        auto previous = head;
        auto next = head->next;
        auto p2 = reversedPart2;
        while (p2) {    // Part 1 is always longer or has equal length as part 2.
            previous->next = p2;
            p2 = p2->next;

            previous->next->next = next;

            previous = next;
            next = previous->next;
        }
    }
};


void test(const std::vector<int>& listVec, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto head = ListHelper::deserialize(listVec);
    solutionInstance.reorderList(head);
//    head = solutionInstance.reverseList(head);
    auto result = ListHelper::serialize(head);

    if (result == expectedResult) {
        std::cout << "[Correct] " << listVec << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << listVec << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,4}, {1,4,2,3});
    test({1,2,3,4,5}, {1,5,2,4,3});
    test({1,2,3,4,5,6}, {1,6,2,5,3,4});
    test({1,2,3,4,5,6,7}, {1,7,2,6,3,5,4});
    return 0;
}
