/*
 * 173. Binary Search Tree Iterator
 * https://leetcode.com/problems/binary-search-tree-iterator/
 */

#include <iostream>
//#include <vector>
#include <stack>

#include "helpers/TreeNode.hpp"
//#include "helpers/Operators.hpp"
//#include "helpers/terminal_format.h"


#pragma mark - 1. Stack-based in-order tree walk
// Runtime: 28 ms, faster than 58.80% of C++ online submissions for Binary Search Tree Iterator.
// Memory Usage: 24.1 MB, less than 35.05% of C++ online submissions for Binary Search Tree Iterator.
class BSTIterator {
private:
    std::stack<TreeNode*> s;

    inline void addLeftElements(TreeNode* root) {
        while (root) {
            s.push(root);
            root = root->left;
        }
    }

public:
    BSTIterator(TreeNode* root) {
        addLeftElements(root);
    }

    int next() {
        auto topNode = s.top();
        s.pop();

        if (topNode->right) {
            addLeftElements(topNode->right);
        }

        return topNode->val;
    }

    bool hasNext() {
        return !s.empty();
    }
};


//void test(const std::vector<int>& nums, const int expectedResult) {
//    static auto solutionInstance = Solution();
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
    return 0;
}
