/*
 * 133. Clone Graph
 * https://leetcode.com/problems/clone-graph/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


// Definition for a Node.
class Node {
public:
    int val;
    std::vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = std::vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = std::vector<Node*>();
    }
    Node(int _val, std::vector<Node*>& _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


#pragma mark - 1. Use 2 auxiliary vectors
// Runtime: 4 ms, faster than 95.43% of C++ online submissions for Clone Graph.
// Memory Usage: 8.6 MB, less than 86.62% of C++ online submissions for Clone Graph.
class Solution {
private:
    void recursion(Node* node, std::vector<Node*>& originalNodesVec) {
        if (node->val > 100) {
            // This node has already been visited.
            return;
        }

        const auto index = node->val - 1;
        if (originalNodesVec.size() <= index) {
            originalNodesVec.resize(index + 1);
        } else if (originalNodesVec[index]) {
            return;
        }

        originalNodesVec[index] = node;
        node->val += 100;    // Add 100 to mark as visited.

        for (const auto neighbor: node->neighbors) {
            recursion(neighbor, originalNodesVec);
        }
    }

public:
    Node* cloneGraph(Node* node) {
        if (!node) {
            return nullptr;
        }

        if (node->neighbors.empty()) {
            return new Node(node->val);
        }

        auto originalNodes = std::vector<Node*>();
        recursion(node, originalNodes);
        // Change the original value back because LeetCode actually uses the original graph for comparison.
        for (const auto originalNode: originalNodes) {
            originalNode->val -= 100;
        }

        auto newNodes = std::vector<Node*>(originalNodes.size());
        for (size_t i = 0; i < originalNodes.size(); i += 1) {
            newNodes[i] = new Node(originalNodes[i]->val);
        }
        for (size_t i = 0; i < originalNodes.size(); i += 1) {
            auto neighbors = originalNodes[i]->neighbors;
            for (const auto& originalNeighbor: neighbors) {
                auto index = originalNeighbor->val - 1;
                newNodes[i]->neighbors.push_back(newNodes[index]);
            }
        }

//        for (const auto originalNode: originalNodes) {
//            std::cout << originalNode->val << " ";
//        }
//        std::cout << "\n";
//        for (const auto newNode: newNodes) {
//            std::cout << newNode->val << " ";
//        }
//        std::cout << std::endl;

        return newNodes[0];
    }
};


//void test(const std::vector<int>& nums, const int expectedResult) {
//    static auto solutionInstance = Solution();
//
//    auto numsCopy = nums;
//    auto result = solutionInstance.findMin(numsCopy);
//
//    if (result == expectedResult) {
//        std::cout << "[Correct] " << nums << ": " << result << std::endl;
//    } else {
//        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
//    }
//}


int main() {
    auto solutionInstance = Solution();
    auto node1 = new Node(1);
    auto node2 = new Node(2);
    node1->neighbors.push_back(node2);
    auto result = solutionInstance.cloneGraph(node1);

    return 0;
}
