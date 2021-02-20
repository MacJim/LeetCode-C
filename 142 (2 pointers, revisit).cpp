/*
 * 142. Linked List Cycle II
 * https://leetcode.com/problems/linked-list-cycle-ii/
 */

#include <iostream>
#include <vector>

//#include "helpers/Operators.hpp"
#include "helpers/ListNode.hpp"


#pragma mark - 1. Fast and slow pointers (revisit)
// I figured out using 1 and 2 dilated pointers, but didn't figure out their distances.
/*
 * Fast and slow pointers, but this time you want to record where the two pointers meet. When the two pointers meet, let one of the pointers start from the head of the linked list, then start moving again, and the position where they meet again is the starting position of the ring in the linked list.
 * Because the fast pointer moves 2 each time and the slow pointer moves 1 each time, the fast pointer travels twice as far as the slow pointer. And the fast pointer goes one more circle than the slow pointer.
 * So the distance from head to the starting point of the ring, plus, the starting point of the ring to the point where they meet, is equal to the distance of one circle of the ring. Now start again, the distance from head to the starting point of the ring and the distance from the meeting point to the starting point of the ring is also equal, which is equivalent to subtracting the distance from the beginning of the ring to the point where they meet.
 */
// Runtime: 4 ms, faster than 99.34% of C++ online submissions for Linked List Cycle II.
// Memory Usage: 7.7 MB, less than 57.50% of C++ online submissions for Linked List Cycle II.
class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }

        auto p1 = head;
        auto p2 = head;

        do {
            p1 = p1->next;

            p2 = p2->next;
            if (p2 == nullptr) {
                return nullptr;
            }
            p2 = p2->next;
            if (p2 == nullptr) {
                return nullptr;
            }
        } while (p1 != p2);

        p2 = head;
        while (p1 != p2) {
            p1 = p1->next;
            p2 = p2->next;
        }

        return p1;
    }
};


//void test(const std::vector<int>& listVec, const int expectedResult) {
//    static auto solutionInstance = Solution();
//
//    auto head = ListHelper::deserialize(listVec);
//    auto result = solutionInstance.detectCycle(head);
//
//    if (result == expectedResult) {
//        std::cout << "[Correct] " << listVec << ": " << result << std::endl;
//    } else {
//        std::cout << "[Wrong] " << listVec << ": " << result << " (should be " << expectedResult << ")" << std::endl;
//    }
//}


int main() {
    return 0;
}
