/*
 * https://leetcode.com/problems/reverse-nodes-in-k-group/
 * 25. Reverse Nodes in k-Group
 */

#include <iostream>

#include "helpers/ListNode.hpp"


// class Solution1 {
// public:
//     ListNode* reverseKGroup(ListNode* head, int k) {
//         if (head == nullptr) {
//             return head;
//         }

//         auto oldHead = head;

//         auto currentNode = head;
//         for (size_t i = 0; i < (k - 1); i += 1) {
//             currentNode = currentNode->next;
//         }

//         auto newHead = currentNode->next;
//         currentNode->next = nullptr;

//         currentNode = newHead;
//         while (currentNode->next != nullptr) {
//             currentNode = currentNode->next;
//         }

//         currentNode->next = oldHead;
//     }
// };


// MARK: - 1. Unfinished and wrong.
class Solution1 {
private:
    void reverseBack(ListNode* originalHead, ListNode* newHead) {
        auto currentNode = newHead;
        auto nextNode = newHead->next;
        while (currentNode != originalHead) {
            auto nextNextNode = nextNode->next;

            nextNode->next = currentNode;

            currentNode = nextNode;
            nextNode = nextNextNode;
        }
    }

    /// @return This portion's new head and the next portion's original head.
    std::pair<ListNode*, ListNode*> reversePortion(ListNode* head, int k) {
        if (k == 1) {
            // No reversal done.
            return std::make_pair(head, nullptr);
        }

        auto currentNode = head;
        auto nextNode = currentNode->next;
        for (size_t i = 1; i < k; i += 1) {
            if (nextNode == nullptr) {
                // Reverse back.
                reverseBack(head, currentNode);
                break;
            }

            auto nextNextNode = nextNode->next;

            nextNode->next = currentNode;

            currentNode = nextNode;
            nextNode = nextNextNode;
        }

        return std::make_pair(currentNode, nextNode);
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr) {
            return head;
        }

        auto result1 = reversePortion(head, k);
        auto newHead = result1.first;
        auto previousPortionOriginalHead = head;
        auto nextPortionOriginalHead = result1.second;

        while (true) {
            auto result2 = reversePortion(nextPortionOriginalHead, k);
            previousPortionOriginalHead->next = result2.first;
            if (result2.first == nextPortionOriginalHead) {
                break;
            } else {
                previousPortionOriginalHead = nextPortionOriginalHead;
                nextPortionOriginalHead = result2.second;
            }
        }

        return newHead;
    }
};


// MARK: - 2. Unfinished
class Solution2 {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr) {
            return head;
        }

        // 1. First portion and new head.
        ListNode* newHead = nullptr;

        auto currentNode = head;
        auto nextNode = currentNode->next;
        for (size_t i = 0; i < (k - 1); i += 1) {
            if (nextNode == nullptr) {
                // Restore the previous order.
                for (size_t j = 0; j < i; j += 1) {
                    auto node1 = currentNode;
                }
            }
            auto nextNextNode = nextNode->next;
            nextNode->next = currentNode;
            currentNode = nextNode;
            nextNode = nextNextNode;
        }

        newHead = currentNode;
        head->next = nextNode;

        // 2. Upcoming portions.

        return newHead;
    }
};


// MARK: - 3
// Runtime: 20 ms, faster than 95.75% of C++ online submissions for Reverse Nodes in k-Group.
// Memory Usage: 10.3 MB, less than 6.45% of C++ online submissions for Reverse Nodes in k-Group.
class Solution {
private:
    /**
     * @param previousTail The previous tail.
     * @return Current period tail.
     */
    ListNode* changeDirection(ListNode* previousTail, int k) {
        bool reachedEnd = false;

        auto currentHead = previousTail->next;

        auto node1 = currentHead;
        auto node2 = node1->next;
        
        for (int i = 1; i < k; i += 1) {
            if (node2 == nullptr) {
                // Restore order because list is shorter than `k`.
                reachedEnd = true;
                auto fakeHead = new ListNode(0);
                fakeHead->next = node1;
                auto finalNode = changeDirection(fakeHead, i);
                finalNode->next = nullptr;
                previousTail->next = currentHead;
                break;
            }

            auto node3 = node2->next;
            node2->next = node1;
            node1 = node2;
            node2 = node3;
        }
        
        if (reachedEnd) {
            return nullptr;
        } else {
            previousTail->next = node1;
            currentHead->next = node2;
            return currentHead;
        }
    }

public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr) {
            return head;
        }
        if (k <= 1) {
            return head;
        }
        
        auto fakeHead = new ListNode(0);
        fakeHead->next = head;

        auto currentTail = changeDirection(fakeHead, k);
        while ((currentTail != nullptr) && (currentTail->next != nullptr)) {
            currentTail = changeDirection(currentTail, k);
        }

        return fakeHead->next;
    }
};


void test(std::vector<int> testVector, int k) {
    static auto solutionInstance = Solution();
    auto testCase = ListHelper::deserialize(testVector);
    auto result = solutionInstance.reverseKGroup(testCase, k);
    auto readableResult = ListHelper::serialize(result);

    for (const auto& aResult: readableResult) {
        std::cout << aResult << " ";
    }
    std::cout << std::endl;
}


int main() {
    test({1, 2, 3, 4, 5}, 1);
    test({1, 2, 3, 4, 5}, 2);
    test({1, 2, 3, 4, 5}, 3);
    test({1, 2, 3, 4, 5}, 4);
    test({1, 2, 3, 4, 5}, 5);
    test({1, 2, 3, 4, 5}, 6);
    return 0;
}
