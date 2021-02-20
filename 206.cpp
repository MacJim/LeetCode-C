/*
 * 206. Reverse Linked List
 */

#include <iostream>

#include "helpers/Operators.hpp"
#include "helpers/ListNode.hpp"


// Runtime: 4 ms, faster than 97.93% of C++ online submissions for Reverse Linked List.
// Memory Usage: 8.3 MB, less than 61.62% of C++ online submissions for Reverse Linked List.
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
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
};


void test(const std::vector<int>& listVec, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto head = ListHelper::deserialize(listVec);
    auto result = solutionInstance.reverseList(head);
    auto resultVec = ListHelper::serialize(result);

    if (resultVec == expectedResult) {
        std::cout << "[Correct] " << listVec << ": " << resultVec << std::endl;
    } else {
        std::cout << "[Wrong] " << listVec << ": " << resultVec << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,4,5}, {5,4,3,2,1});
    test({1,2}, {2,1});

    return 0;
}
