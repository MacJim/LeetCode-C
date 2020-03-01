/*
 * 24. Swap Nodes in Pairs
 * https://leetcode.com/problems/swap-nodes-in-pairs/
 */

#include <iostream>

#include "helpers/ListNode.hpp"


// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Swap Nodes in Pairs.
// Memory Usage: 7.8 MB, less than 100.00% of C++ online submissions for Swap Nodes in Pairs.
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if ((head == nullptr) || (head->next == nullptr)) {
            // 0 or 1 node.
            return head;
        }

        auto returnValue = head->next;

        auto currentNode = head;
        ListNode* previousNode = nullptr;
        while (true) {
            if (currentNode == nullptr) {
                previousNode->next = nullptr;
                break;
            }
            auto nextNode = currentNode->next;
            if (nextNode == nullptr) {
                previousNode->next = currentNode;
                break;
            }

            if (previousNode) {
                previousNode->next = nextNode;
            }
            previousNode = currentNode;

            std::swap(nextNode->next, currentNode);
        }

        return returnValue;
    }
};


void test(ListNode* testCase) {
    static auto solutionInstance = Solution();
    auto result = solutionInstance.swapPairs(testCase);
    auto readableResult1 = ListHelper::serialize(result);
    for (const auto& num: readableResult1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

}

int main() {
    auto testCase1 = ListHelper::deserialize({1, 2, 3, 4, 5, 6});
    test(testCase1);
    auto testCase2 = ListHelper::deserialize({1, 2, 3, 4, 5, 6, 7});
    test(testCase2);
    auto testCase3 = ListHelper::deserialize({1});
    test(testCase3);

    return 0;
}
