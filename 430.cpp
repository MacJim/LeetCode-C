/*
 * 430. Flatten a Multilevel Doubly Linked List
 * https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/
 */

#include <iostream>
#include <vector>
#include <stack>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    explicit Node(int val) {
        this->val = val;
        this->prev = nullptr;
        this->next = nullptr;
        this->child = nullptr;
    }
};


#pragma mark - 1. Stack
// Runtime: 4 ms, faster than 81.02% of C++ online submissions for Flatten a Multilevel Doubly Linked List.
// Memory Usage: 7.5 MB, less than 19.06% of C++ online submissions for Flatten a Multilevel Doubly Linked List.
class Solution {
public:
    Node* flatten(Node* head) {
        if (!head) {
            return head;
        }

        auto currentNode = head;
        auto nextNodes = std::stack<Node*>();

        while (true) {
            if (currentNode->child) {
                // Connect with child.
                if (currentNode->next) {
                    nextNodes.push(currentNode->next);
                }

//                std::cout << "Connecting " << currentNode->val << " with " << currentNode->child->val << "." << std::endl;

                currentNode->next = currentNode->child;
                currentNode->child->prev = currentNode;

                const auto nextNode = currentNode->child;
                currentNode->child = nullptr;    // Not sure if this is needed.
                currentNode = nextNode;
            } else if (!currentNode->next) {
                if (nextNodes.empty()) {
                    // This is the final node.
                    break;
                }

                // Connect with stack top.
//                std::cout << "Connecting " << currentNode->val << " with " << nextNodes.top()->val << "." << std::endl;

                currentNode->next = nextNodes.top();
                nextNodes.top()->prev = currentNode;
                currentNode = nextNodes.top();
                nextNodes.pop();
            } else {
                // Continue with current list.
                currentNode = currentNode->next;
            }
        }

        return head;
    }
};


//void test(const std::vector<int>& nums, const int expectedResult) {
//    auto solutionInstance = Solution();
//
//    auto numsCopy = nums;
//    auto result = solutionInstance.findMin(numsCopy);
//
//    if (result == expectedResult) {
//        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
//    } else {
//        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
//    }
//}


int main() {
    auto solutionInstance = Solution();

    auto node1 = new Node(1);
    auto node2 = new Node(2);
    auto node3 = new Node(3);
    node1->child = node2;
    node2->child = node3;

    auto result = solutionInstance.flatten(node1);

    return 0;
}
