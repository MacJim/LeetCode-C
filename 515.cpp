/*
 * 515. Find Largest Value in Each Tree Row
 * https://leetcode.com/problems/find-largest-value-in-each-tree-row/
 */

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

#include "helpers/TreeNode.hpp"
#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. BFS, deque
// Runtime: 16 ms, faster than 29.59% of C++ online submissions for Find Largest Value in Each Tree Row.
// Memory Usage: 22.4 MB, less than 18.74% of C++ online submissions for Find Largest Value in Each Tree Row.
class Solution1 {
public:
    std::vector<int> largestValues(TreeNode* root) {
        if (!root) {
            return {};
        }

        auto returnValue = std::vector<int>();

        auto nodes = std::deque<std::pair<TreeNode*, size_t>>();
        nodes.emplace_back(root, 0);

        while (!nodes.empty()) {
            const auto& [node, depth] = nodes.front();
            if (returnValue.size() <= depth) {
                returnValue.resize(depth + 1, node->val);
            } else {
                returnValue[depth] = std::max(returnValue[depth], node->val);
            }

            if (node->left) {
                nodes.emplace_back(node->left, depth + 1);
            }
            if (node->right) {
                nodes.emplace_back(node->right, depth + 1);
            }

            nodes.pop_front();
        }

        return returnValue;
    }
};


#pragma mark - 2. DFS, recursion
// Runtime: 8 ms, faster than 85.50% of C++ online submissions for Find Largest Value in Each Tree Row.
// Memory Usage: 22.1 MB, less than 65.12% of C++ online submissions for Find Largest Value in Each Tree Row.
class Solution {
private:
    void recursion(const TreeNode* node, const size_t depth, std::vector<int>& returnValue) {
        if (returnValue.size() <= depth) {
            returnValue.resize(depth + 1, node->val);
        } else {
            returnValue[depth] = std::max(returnValue[depth], node->val);
        }

        if (node->left) {
            recursion(node->left, depth + 1, returnValue);
        }
        if (node->right) {
            recursion(node->right, depth + 1, returnValue);
        }
    }

public:
    std::vector<int> largestValues(TreeNode* root) {
        if (!root) {
            return {};
        }

        auto returnValue = std::vector<int>();

        recursion(root, 0, returnValue);

        return returnValue;
    }
};


void test(const std::string& treeStr, const std::vector<int>& expectedResult) {
    auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.largestValues(root);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << treeStr << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << treeStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("1,3,2,5,3,,9", {1,3,9});
    test("1,2,3", {1,3});
    test("1", {1});
    test("1,,2", {1,2});
    test("", {});

    return 0;
}
