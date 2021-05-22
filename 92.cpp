/*
 * 92. Reverse Linked List II
 * https://leetcode.com/problems/reverse-linked-list-ii/
 */

/*
 * Index parameters start at 1.
 */

#include <iostream>
#include <vector>

#include "helpers/ListNode.hpp"
#include "helpers/Operators.hpp"


#pragma mark - 1
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Reverse Linked List II.
// Memory Usage: 7.4 MB, less than 91.72% of C++ online submissions for Reverse Linked List II.
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right) {
            return head;
        }

        auto dummyHead = new ListNode(6);
        dummyHead->next = head;

        ListNode* leftLeftNode = dummyHead;

        // Find `left`.
        while (left > 1) {
            leftLeftNode = leftLeftNode->next;

            left -= 1;
            right -= 1;
        }
        ListNode* leftNode = leftLeftNode->next;

        auto previous = leftNode;
        ListNode* current = leftNode->next;

        // Change `next` direction.
        while (right > 1) {
            const auto next = current->next;
            current->next = previous;

            previous = current;
            current = next;

            right -= 1;
        }

        const auto rightNode = previous;
        const auto rightRightNode = current;

        leftLeftNode->next = rightNode;
        leftNode->next = rightRightNode;

        return dummyHead->next;
    }
};


#pragma mark - 2
/*
 * Can also use a swapping approach.
 *
 * After swapping left and right, let:
 * - left = right->next
 * - right = left->next
 *
 * This way, we can continue swapping the left and right elements until we reach the center.
 */


void test(const std::vector<int>& listVec, const int left, const int right, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto head = ListHelper::deserialize(listVec);
    auto result = solutionInstance.reverseBetween(head, left, right);
    auto resultVec = ListHelper::serialize(result);

    if (resultVec == expectedResult) {
        std::cout << "[Correct] " << listVec << ", " << left << ", " << right << ": " << resultVec << std::endl;
    } else {
        std::cout << "[Wrong] " << listVec << ", " << left << ", " << right << ": " << resultVec << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,4,5}, 2, 4, {1,4,3,2,5});
    test({1}, 1, 1, {1});
    test({1,2,3,4,5}, 2, 3, {1,3,2,4,5});
    test({1,2,3,4,5}, 3, 4, {1,2,4,3,5});
    test({1,2,3,4,5}, 2, 5, {1,5,4,3,2});
    test({1,2,3,4,5}, 1, 4, {4,3,2,1,5});
    test({1,2,3,4,5}, 1, 5, {5,4,3,2,1});

    return 0;
}
