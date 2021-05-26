/*
 * 147. Insertion Sort List
 * https://leetcode.com/problems/insertion-sort-list/
 */

#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
#include <random>
#include <algorithm>

#include "helpers/ListNode.hpp"
#include "helpers/Operators.hpp"


#pragma mark - 1. In-place
// Time Limit Exceeded
class Solution1 {
public:
    ListNode* insertionSortList(ListNode* head) {
        if (!head->next) {
            return head;
        }

        auto dummyHead = new ListNode(INT_MIN);
        dummyHead->next = head;

        auto currentNode = head;
        while (currentNode->next) {
            auto nextNode = currentNode->next;

            auto firstNode = dummyHead;
            while (firstNode->next && (firstNode->next != currentNode->next) && (firstNode->next->val <= currentNode->next->val)) {
                firstNode = firstNode->next;
            }

            if (firstNode->next != currentNode->next) {
                auto nodeToMove = currentNode->next;
                currentNode->next = currentNode->next->next;

                nodeToMove->next = firstNode->next;
                firstNode->next = nodeToMove;
            }

            currentNode = nextNode;
        }

        return dummyHead->next;
    }
};


#pragma mark - 2. Not in-place (in practice it's the same idea)
// This way, we don't need to check `firstNode->next != currentNode->next`
// Runtime: 36 ms, faster than 64.14% of C++ online submissions for Insertion Sort List.
// Memory Usage: 9.6 MB, less than 30.69% of C++ online submissions for Insertion Sort List.
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if (!head->next) {
            return head;
        }

        // Create a new list for return value.
        auto dummyHead = new ListNode(INT_MIN);
        dummyHead->next = head;

        auto originalNode = head->next;
        head->next = nullptr;    // This separates the original list and our new list.

        while (originalNode) {
            auto nextNode = originalNode->next;

            auto newNode = dummyHead;
            while (newNode->next && (newNode->next->val <= originalNode->val)) {
                newNode = newNode->next;
            }

            originalNode->next = newNode->next;
            newNode->next = originalNode;

            originalNode = nextNode;
        }

        return dummyHead->next;
    }
};


void test(const std::vector<int>& nums) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;

    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto generator = std::default_random_engine(seed);
    std::shuffle(numsCopy.begin(), numsCopy.end(), generator);

    auto head = ListHelper::deserialize(numsCopy);
    auto result = solutionInstance.insertionSortList(head);
    auto resultVec = ListHelper::serialize(result);

    if (resultVec == nums) {
        std::cout << "[Correct] " << numsCopy << ": " << resultVec << std::endl;
    } else {
        std::cout << "[Wrong] " << numsCopy << ": " << resultVec << " (should be " << nums << ")" << std::endl;
    }
}


int main() {
    test({1});
    test({1,2});
    test({1,2,3});
    test({1,2,3,4});
    test({1,2,3,4,5});
    test({1,2,3,4,5,6});
    test({1,2,3,4,5,6,7});

    return 0;
}
