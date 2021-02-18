/*
 * 236. Lowest Common Ancestor of a Binary Tree
 */

#include <iostream>
#include <string>
#include <deque>
#include <algorithm>

//#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Back-order DFS with history (I think this is LeetCode's official solution 3)
/*
 * Tree traversal using a stack is tedious.
 * I think it's always best to start with a recursive approach instead of using stacks.
 *
 * I think this solution also consumes more memory than recursion since I saved the "status" of each node in history.
 */
// Runtime: 16 ms, faster than 80.87% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
// Memory Usage: 15.1 MB, less than 22.84% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
class Solution1 {
private:
    /*
     * (node, children visited status)
     *
     * Statuses: 0: both left and right children are unvisited, 1: visited left child, 2: visited both left and right children.
     */
    std::deque<std::pair<TreeNode*, short>> history = std::deque<std::pair<TreeNode*, short>>();

    std::deque<std::pair<TreeNode*, short>> pHistory = std::deque<std::pair<TreeNode*, short>>();
    std::deque<std::pair<TreeNode*, short>> qHistory = std::deque<std::pair<TreeNode*, short>>();

    inline TreeNode* findCommonNode() {
        TreeNode* commonNode = nullptr;

        for (size_t i = 0; i < std::min(pHistory.size(), qHistory.size()); i += 1) {
            const auto& node1 = pHistory[i].first;
            const auto& node2 = qHistory[i].first;
            if (node1 == node2) {
                commonNode = node1;
            } else {
                break;
            }
        }

        return commonNode;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        history.emplace_back(root, false);
        while (true) {
            if (history.back().first == p) {
                if (qHistory.empty()) {
                    pHistory = history;
                } else {
                    pHistory = std::move(history);
                    return findCommonNode();
                }
            } else if (history.back().first == q) {
                 if (pHistory.empty()) {
                     qHistory = history;
                 } else {
                     qHistory = std::move(history);
                     return findCommonNode();
                 }
            }

            if (history.back().second == 0) {
                history.back().second = 1;

                if (history.back().first->left) {
                    history.emplace_back(history.back().first->left, 0);
                }
            } else if (history.back().second == 1) {
                history.back().second = 2;

                if (history.back().first->right) {
                    history.emplace_back(history.back().first->right, 0);
                }
            } else {
                // Useless child node.
                history.pop_back();
            }
        }
    }

//    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//        while (true) {
//            while (root) {
//                history.push_back(root);
//                root = root->left;
//            }
//
//            root = history.back();
//
//            if (root == p) {
//                if (qHistory.empty()) {
//                    pHistory = history;
//                } else {
//                    // Find.
//                    pHistory = std::move(history);
//                    return findCommonNode();
//                }
//            } else if (root == q) {
//                if (pHistory.empty()) {
//                    qHistory = history;
//                } else {
//                    // Find.
//                    qHistory = std::move(history);
//                    return findCommonNode();
//                }
//            }
//
//            history.pop_back();
//
//            root = root->right;
//        }
//    }
};


#pragma mark - 2. Don't log history, but log "node found" flag (revisit)
// Runtime: 12 ms, faster than 96.71% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
// Memory Usage: 14.2 MB, less than 84.42% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
class Solution {
private:
    bool resultFound = false;
    TreeNode* result = nullptr;

    std::pair<bool, bool> findNode(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (resultFound) {
            // Terminate pre-maturely in later recursion levels.
            return std::make_pair(false, false);
        }

        if (root == nullptr) {
            return std::make_pair(false, false);
        } else {
            const auto leftResult = findNode(root->left, p, q);
            const auto rightResult = findNode(root->right, p, q);

            if (resultFound) {
                // Terminate pre-maturely in earlier recursion levels.
                return std::make_pair(false, false);
            }

            const auto pResult = (root == p) || (leftResult.first) || (rightResult.first);
            const auto qResult = (root == q) || (leftResult.second) || (rightResult.second);
            if (pResult && qResult) {
                resultFound = true;
                result = root;
            }

            return std::make_pair(pResult, qResult);
        }
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        findNode(root, p, q);
        return result;
    }
};


void test(const std::string& treeStr, const std::string& pStr, const std::string& qStr, const int expectedResult) {
    // Don't use a static instance here.
    auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);

    auto p = root;
    for (const auto& c: pStr) {
        if (c == 'l') {
            p = p->left;
        } else {
            p = p->right;
        }
    }
    auto q = root;
    for (const auto& c: qStr) {
        if (c == 'l') {
            q = q->left;
        } else {
            q = q->right;
        }
    }

    auto result = solutionInstance.lowestCommonAncestor(root, p, q);

    if (result->val == expectedResult) {
        std::cout << "[Correct] " << treeStr + " " + pStr + " " + qStr << ": " << result->val << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr + " " + pStr + " " + qStr << ": " << result->val << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("3,5,1,6,2,0,8,,,7,4", "l", "r", 3);
    test("3,5,1,6,2,0,8,,,7,4", "l", "lrr", 5);
    test("1,2", "", "l", 1);

    return 0;
}
