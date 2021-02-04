/*
 * 222. Count Complete Tree Nodes
 * https://leetcode.com/problems/count-complete-tree-nodes/
 */

/*
 * Related problem: https://leetcode.com/discuss/interview-question/236898
 */

#include <iostream>
#include <vector>
#include <string>

//#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. BFS
// Runtime: 52 ms, faster than 15.83% of C++ online submissions for Count Complete Tree Nodes.
// Memory Usage: 31.7 MB, less than 17.02% of C++ online submissions for Count Complete Tree Nodes.
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int returnValue = 1;

        auto currentNodes = std::vector<TreeNode*>({root});
        auto nextNodes = std::vector<TreeNode*>();

        while (!currentNodes.empty()) {
            for (const auto& node: currentNodes) {
                if (node->left) {
                    returnValue += 1;
                    nextNodes.push_back(node->left);
                } else {
                    return returnValue;
                }

                if (node->right) {
                    returnValue += 1;
                    nextNodes.push_back(node->right);
                } else {
                    return returnValue;
                }
            }

            std::swap(currentNodes, nextNodes);
            nextNodes.clear();
        }

        return returnValue;
    }
};


#pragma mark - 2. DFS (revisit)
/*
 * Source: https://leetcode.com/problems/count-complete-tree-nodes/discuss/61953/Easy-short-c%2B%2B-recursive-solution
 *
 * We know that the tree may only miss elements from the bottom right.
 * Thus, we can find the left-most and right-most children and compare their heights.
 *
 * If they equal, result = pow(2, height) - 1;
 *
 * Otherwise, run recursion on the left and right sub-trees.
 * One of them must be a complete tree since the tree may only miss elements from the bottom right.
 *
 * Then, run recursion on the unbalanced sub-tree's sub-trees.
 */


void test(const std::string& treeString, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeString);
    auto result = solutionInstance.countNodes(root);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeString << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeString << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("1,2,3,4,5,6", 6);
    test("", 0);
    test("1", 1);

    return 0;
}
