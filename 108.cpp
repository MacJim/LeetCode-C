/*
 * 108. Convert Sorted Array to Binary Search Tree
 * https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
 */

#include <iostream>
#include <vector>

#include "helpers/TreeNode.hpp"
#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Recursion
// Runtime: 8 ms, faster than 94.79% of C++ online submissions for Convert Sorted Array to Binary Search Tree.
// Memory Usage: 21.5 MB, less than 42.53% of C++ online submissions for Convert Sorted Array to Binary Search Tree.
class Solution {
private:
    TreeNode* recursion(const std::vector<int>& nums, const int startIndex, const int endIndex) {
        if (startIndex > endIndex) {
            // No elements.
            return nullptr;
        }
        if (startIndex == endIndex) {
            // Only 1 element.
            return new TreeNode(nums[startIndex]);
        }

        const int midIndex = (startIndex + endIndex) / 2;
        auto midNode = new TreeNode(nums[midIndex]);

        midNode->left = recursion(nums, startIndex, midIndex - 1);
        midNode->right = recursion(nums, midIndex + 1, endIndex);

        return midNode;
    }

public:
    TreeNode* sortedArrayToBST(const std::vector<int>& nums) {
        auto returnValue = recursion(nums, 0, nums.size() - 1);

        return returnValue;
    }
};


void test(const std::vector<int>& nums) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.sortedArrayToBST(nums);

    auto resultVec = TreeHelper::inOrderTraverse(result);

    if (nums == resultVec) {
        // Print nothing becasue there are too many test cases.
//        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << resultVec << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << resultVec << " (should be " << nums << ")" << std::endl;
    }
}


int main() {
    for (int length = 1; length <= 10000; length += 1) {
        auto testCase = std::vector<int>(length, 0);
        for (int i = 0; i < length; i += 1) {
            testCase[i] = i;
        }

        test(testCase);
    }

    return 0;
}
