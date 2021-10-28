/*
 * 1530. Number of Good Leaf Nodes Pairs
 * https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/
 */

#include <iostream>
#include <utility>
#include <unordered_map>
#include <map>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Recursion: Calculate each node's children
// Runtime: 136 ms, faster than 22.18% of C++ online submissions for Number of Good Leaf Nodes Pairs.
// Memory Usage: 64.6 MB, less than 6.39% of C++ online submissions for Number of Good Leaf Nodes Pairs.

// (return value, (distance, count))
using ReturnType1 = std::pair<int, std::unordered_map<int, int>>;

class Solution1 {
private:
    ReturnType1 recursion(TreeNode* node, const int distanceLimit) {
        if (!node) {
            return std::make_pair(0, std::unordered_map<int, int>());
        }

        auto [leftResult, leftChildren] = recursion(node->left, distanceLimit);
        auto [rightResult, rightChildren] = recursion(node->right, distanceLimit);

        int currentResult = 0;
        // MARK: This part is brute force and is very slow. Maybe I can replace this with `std::map` to terminate quicker?
        for (const auto [leftDistance, leftCount]: leftChildren) {
            for (const auto [rightDistance, rightCount]: rightChildren) {
                if ((leftDistance + rightDistance) <= distanceLimit) {
                    currentResult += (leftCount * rightCount);
                }
            }
        }

        auto newChildren = std::unordered_map<int, int>();
        for (const auto [leftDistance, leftCount]: leftChildren) {
            newChildren[leftDistance + 1] += leftCount;
        }
        for (const auto [rightDistance, rightCount]: rightChildren) {
            newChildren[rightDistance + 1] += rightCount;
        }
        if (!node->left && !node->right) {
            newChildren[1] += 1;
        }

        return std::make_pair(currentResult + leftResult + rightResult, newChildren);
    }

public:
    int countPairs(TreeNode* root, const int distanceLimit) {
        return recursion(root, distanceLimit).first;
    }
};


#pragma mark - 2. Optimized 1: Replace `unordered_map` with `map`
// Runtime: 84 ms, faster than 58.82% of C++ online submissions for Number of Good Leaf Nodes Pairs.
// Memory Usage: 46.6 MB, less than 10.92% of C++ online submissions for Number of Good Leaf Nodes Pairs.

// (return value, (distance, count))
using ReturnType2 = std::pair<int, std::map<int, int>>;

class Solution2 {
private:
    ReturnType2 recursion(TreeNode* node, const int distanceLimit) {
        if (!node) {
            return std::make_pair(0, std::map<int, int>());
        }

        auto [leftResult, leftChildren] = recursion(node->left, distanceLimit);
        auto [rightResult, rightChildren] = recursion(node->right, distanceLimit);

        int currentResult = 0;
        for (const auto [leftDistance, leftCount]: leftChildren) {
            for (const auto [rightDistance, rightCount]: rightChildren) {
                if ((leftDistance + rightDistance) <= distanceLimit) {
                    currentResult += (leftCount * rightCount);
                } else {
                    break;
                }
            }
        }

        auto newChildren = std::map<int, int>();
        for (const auto [leftDistance, leftCount]: leftChildren) {
            newChildren[leftDistance + 1] += leftCount;
        }
        for (const auto [rightDistance, rightCount]: rightChildren) {
            newChildren[rightDistance + 1] += rightCount;
        }
        if (!node->left && !node->right) {
            newChildren[1] += 1;
        }

        return std::make_pair(currentResult + leftResult + rightResult, newChildren);
    }

public:
    int countPairs(TreeNode* root, const int distanceLimit) {
        return recursion(root, distanceLimit).first;
    }
};


#pragma mark - 3. Optimized 2: Don't log distances that are longer than `distanceLimit`
// Runtime: 60 ms, faster than 86.89% of C++ online submissions for Number of Good Leaf Nodes Pairs.
// Memory Usage: 41.4 MB, less than 13.95% of C++ online submissions for Number of Good Leaf Nodes Pairs.

// (return value, (distance, count))
using ReturnType = std::pair<int, std::map<int, int>>;

class Solution {
private:
    ReturnType recursion(TreeNode* node, const int distanceLimit) {
        if (!node) {
            return std::make_pair(0, std::map<int, int>());
        }

        auto [leftResult, leftChildren] = recursion(node->left, distanceLimit);
        auto [rightResult, rightChildren] = recursion(node->right, distanceLimit);

        int currentResult = 0;
        for (const auto [leftDistance, leftCount]: leftChildren) {
            for (const auto [rightDistance, rightCount]: rightChildren) {
                if ((leftDistance + rightDistance) <= distanceLimit) {
                    currentResult += (leftCount * rightCount);
                } else {
                    break;
                }
            }
        }

        auto newChildren = std::map<int, int>();
        for (const auto [leftDistance, leftCount]: leftChildren) {
            if (leftDistance == distanceLimit) {
                // Don't log distances that are longer than `distanceLimit`
                break;
            }
            newChildren[leftDistance + 1] += leftCount;
        }
        for (const auto [rightDistance, rightCount]: rightChildren) {
            if (rightDistance == distanceLimit) {
                // Don't log distances that are longer than `distanceLimit`
                break;
            }
            newChildren[rightDistance + 1] += rightCount;
        }
        if (!node->left && !node->right) {
            newChildren[1] += 1;
        }

        return std::make_pair(currentResult + leftResult + rightResult, newChildren);
    }

public:
    int countPairs(TreeNode* root, const int distanceLimit) {
        return recursion(root, distanceLimit).first;
    }
};


#pragma mark - 4. DFS from every leaf node (official solution)
// I don't like this solution :(
// Remember to divide answer by 2, because each pair is counted twice.


void test(const std::string& treeStr, const int distance, const int expectedResult) {
    auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.countPairs(root, distance);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << treeStr << ", " << distance << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << treeStr << ", " << distance << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("1,2,3,,4", 3, 1);
    test("1,2,3,4,5,6,7", 3, 2);
    test("7,1,4,6,,5,3,,,,,,2", 3, 1);
    test("1", 1, 0);

    return 0;
}
