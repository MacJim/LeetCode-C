/*
 * 255. Verify Preorder Sequence in Binary Search Tree
 * https://leetcode.com/problems/verify-preorder-sequence-in-binary-search-tree/
 */

#include <iostream>
#include <vector>
#include <stack>
#include <climits>

#include "helpers/Operators.hpp"
//#include "helpers/TreeNode.hpp"


#pragma mark - 1. Recursion
// WRONG
class Solution1 {
private:
    std::pair<int, int> recursion(std::vector<int>& preOrder) {
        if (preOrder.size() == 1) {
            return std::make_pair(preOrder[0], preOrder[0]);
        }

        int rootVal = preOrder[0];
        int returnMin = rootVal;
        int returnMax = rootVal;

        // Find the left and right sub-trees.
        const int leftStart = 1;
        int leftEnd = 0;
        int rightStart = 1;
//        const int rightEnd = preOrder.size();

        while ((rightStart < preOrder.size()) && (preOrder[rightStart] < rootVal)) {
            rightStart += 1;
        }
        if (rightStart == 1) {
            // The value right after root is larger than root.
            throw false;
        }

        leftEnd = rightStart;

        if (leftEnd != 1) {
            // Left sub-tree.
            auto leftSubTree = std::vector<int>(preOrder.begin() + leftStart, preOrder.begin() + leftEnd);
            auto [leftMin, leftMax] = recursion(leftSubTree);
            if (leftMax > rootVal) {
                throw false;
            }
            returnMin = leftMin;
        }
        if (rightStart != preOrder.size()) {
            // Right sub-tree.
            auto rightSubTree = std::vector<int>(preOrder.begin() + rightStart, preOrder.end());
            auto [rightMin, rightMax] = recursion(rightSubTree);
            if (rightMin < rootVal) {
                throw false;
            }
            returnMax = rightMax;
        }

        return std::make_pair(returnMin, returnMax);
    }

public:
    bool verify(std::vector<int>& preOrder) {
        if (preOrder.size() <= 1) {
            return true;
        }

//        recursion(preOrder);
//        return true;
        try {
            recursion(preOrder);
            return true;
        } catch (...) {
            return false;
        };
    }
};


#pragma mark - 2. Stack-based: push all left offsprings, then pop and push the right child (revisit)
// Source: https://leetcode.ca/2016-08-11-255-Verify-Preorder-Sequence-in-Binary-Search-Tree/
class Solution {
public:
    bool verify(std::vector<int>& preOrder) {
        if (preOrder.size() <= 1) {
            return true;
        }

        int minNum = INT_MIN;
        auto previousNums = std::stack<int>();
        for (const auto& num: preOrder) {
            if (num < minNum) {
                return false;
            }

            while ((!previousNums.empty()) && (num > previousNums.top())) {
                minNum = previousNums.top();
                previousNums.pop();
            }

            previousNums.push(num);
        }

        return true;
    }
};


void test(const std::vector<int>& preOrder, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto preOrderCopy = preOrder;
    auto result = solutionInstance.verify(preOrderCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << preOrder << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << preOrder << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2}, true);    // Note that this one is `true` because 2 is the right child.
    test({2,1}, true);
    test({2,1,3}, true);
    test({5,2,6,1,3}, false);
    test({5,2,1,3,6}, true);

    return 0;
}
