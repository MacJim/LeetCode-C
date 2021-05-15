/*
 * 328. Odd Even Linked List
 * https://leetcode.com/problems/odd-even-linked-list/
 */

#include <iostream>
#include <vector>

#include "helpers/ListNode.hpp"
#include "helpers/Operators.hpp"


#pragma mark - 1. Put the even elements behind the odd elements
// Maybe I should just put the even and odd elements in 2 separate lists before merging them lastly.
// Runtime: 8 ms, faster than 91.60% of C++ online submissions for Odd Even Linked List.
// Memory Usage: 10.5 MB, less than 23.25% of C++ online submissions for Odd Even Linked List.
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if ((!head) || (!head->next)) {
            return head;
        }

        auto lastOdd = head;
        auto firstEven = head->next;
        auto currentEven = head->next;

        while (currentEven) {
            auto currentOdd = currentEven->next;
            if (!currentOdd) {
                break;
            }

            auto nextEven = currentOdd->next;

            lastOdd->next = currentOdd;
            lastOdd = currentOdd;
            currentOdd->next = firstEven;
            currentEven->next = nextEven;
            currentEven = nextEven;
        }

        return head;
    }
};


void test(const std::vector<int>& listVec, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto head = ListHelper::deserialize(listVec);
    auto result = solutionInstance.oddEvenList(head);

    auto resultVec = ListHelper::serialize(result);
    if (resultVec == expectedResult) {
        std::cout << "[Correct] " << listVec << ": " << resultVec << std::endl;
    } else {
        std::cout << "[Wrong] " << listVec << ": " << resultVec << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,4,5}, {1,3,5,2,4});
    test({2,1,3,5,6,4,7}, {2,3,6,7,1,5,4});

    test({}, {});

    test({1,2,3,4,5,6,7,8}, {1,3,5,7,2,4,6,8});

    return 0;
}
