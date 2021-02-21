/*
 * 138. Copy List with Random Pointer
 * https://leetcode.com/problems/copy-list-with-random-pointer/
 */

#include <iostream>

//#include "helpers/Operators.hpp"


class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};


#pragma mark - 1 (unfinished)
/*
 * Transformations:
 *
 * 1. Copy next relationship
 * 2. Remove next relationship in original
 * 3. Original `next`s point to corresponding node in copy
 * 4. Copy `random`s point to corresponding node in original
 *
 * For each node in copy:
 *
 * 1. Get corresponding original node
 * 2. Get original node's `random`
 * 3. Get `random`'s correspondence in copy
 * 4. Assign copy's `random`
 *
 * For each node in copy:
 *
 * 1. Restore original's `next`
 */
// WRONG ANSWER because later nodes' `random` attributes may still reference earlier nodes
class Solution1 {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        } else if (head->next == nullptr) {
            return new Node(head->val);
        }

        auto copyHead = new Node(head->val);

        auto current = head->next;
        auto copyPrevious = copyHead;
        while (current) {
            copyPrevious->next = new Node(current->val);
            copyPrevious->next->random = current;

            auto nextCurrent = current->next;
            current->next = copyPrevious->next;

            copyPrevious = copyPrevious->next;
            current = nextCurrent;
        }

        auto copyCurrent = copyHead;
        while (copyCurrent) {
            auto original = copyCurrent->random;
            if (original->random) {
                auto copyRandom = original->random->next;
                copyCurrent->random = copyRandom;
            } else {
                copyCurrent->random = nullptr;
            }
        }

        copyCurrent = copyHead;

        return copyHead;
    }
};


#pragma mark - 2. Copy a new node behind each node in the original linked list (revisit)
// Runtime: 4 ms, faster than 98.26% of C++ online submissions for Copy List with Random Pointer.
// Memory Usage: 11.2 MB, less than 93.85% of C++ online submissions for Copy List with Random Pointer.
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        } else if (head->next == nullptr) {
            auto returnValue = new Node(head->val);
            if (head->random) {
                returnValue->random = returnValue;
            }
            return returnValue;
        }

        // 1. Copy
        auto current = head;
        while (current) {
            auto originalNext = current->next;
            current->next = new Node(current->val);
            current->next->next = originalNext;
            current = originalNext;
        }

        // 2. Assign `random`
        current = head;
        while (current) {
            auto originalNext = current->next->next;
            if (current->random) {
                current->next->random = current->random->next;
            }
            current = originalNext;
        }

        // 3. Separate new nodes.
        current = head;
        Node* newHead = nullptr;
        Node* newCurrent = nullptr;
        while (current) {
            auto originalNext = current->next->next;
            auto copy = current->next;

            current->next = originalNext;
            if (newHead) {
                newCurrent->next = copy;
                newCurrent = newCurrent->next;
            } else {
                newHead = copy;
                newCurrent = copy;
            }

            current = originalNext;
        }

        return newHead;
    }
};


int main() {
    auto solutionInstance = Solution();

    auto node1 = new Node(-1);
    node1->random = node1;
    auto result = solutionInstance.copyRandomList(node1);

    return 0;
}
