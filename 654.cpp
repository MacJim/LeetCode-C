/*
 * 654. Maximum Binary Tree
 * https://leetcode.com/problems/maximum-binary-tree/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Recursion
class Solution {
private:
    TreeNode* recursion(const std::vector<int>& nums, int start, int end) {
        if (start == end) {
            return new TreeNode(nums[start]);
        } else if (start > end) {
            return nullptr;
        }
        
        int maxIndex = start;
        for (int i = start; i <= end; i += 1) {
            if (nums[i] > nums[maxIndex]) {
                maxIndex = i;
            }
        }
        
        auto maxNode = new TreeNode(nums[maxIndex]);
        maxNode->left = recursion(nums, start, maxIndex - 1);
        maxNode->right = recursion(nums, maxIndex + 1, end);

        return maxNode;
    }
    
public:
    TreeNode* constructMaximumBinaryTree(const std::vector<int>& nums) {
//        if (nums.size() == 1) {
//            return new TreeNode(nums[0]);
//        }
        
        auto returnValue = recursion(nums, 0, nums.size() - 1);
        
        return returnValue;
    }
};


void test(const std::vector<int>& nums, const std::string& expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.constructMaximumBinaryTree(nums);
    auto resultStr = TreeHelper::serialize(result);

    if (resultStr.find(expectedResult) == 0) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << resultStr << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << resultStr << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({3,2,1,6,0,5}, "6,3,5,,2,0,,,1");
    test({3,2,1}, "3,,2,,1");

    return 0;
}
