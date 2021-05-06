/*
 * 117. Populating Next Right Pointers in Each Node II
 * https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
            : val(_val), left(_left), right(_right), next(_next) {}
};


#pragma mark - 1. Recursion
// WRONG ANSWER
// [1,2,3,4,5,null,6,7,null,null,null,null,8]
// [1,#,2,3,#,4,5,6,#,7,#] (should be [1,#,2,3,#,4,5,6,#,7,8,#])
class Solution1 {
private:
    void recursion(Node* root) {
        if (root == nullptr) {
            return;
        }

        recursion(root->left);
        recursion(root->right);

        auto left = root->left;
        auto right = root->right;
        while (left && right) {
            left->next = right;

            if (left->right) {
                left = left->right;
            } else {
                left = left->left;
            }
            if (right->left) {
                right = right->left;
            } else {
                right = right->right;
            }
        }
    }

public:
    Node* connect(Node* root) {
        if (root == nullptr) {
            return root;
        }

        recursion(root);

        return root;
    }
};


#pragma mark - 2. Use the `next` pointers to assist BFS (revisit)
// Runtime: 12 ms, faster than 73.31% of C++ online submissions for Populating Next Right Pointers in Each Node II.
// Memory Usage: 17.3 MB, less than 93.78% of C++ online submissions for Populating Next Right Pointers in Each Node II.
class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) {
            return root;
        }

        auto currentNode = root;
        Node* nextLayerFirst = nullptr;
        Node* nextLayerPrevious = nullptr;

        while (currentNode) {
            while (currentNode) {
                if (currentNode->left) {
                    if (nextLayerPrevious) {
                        nextLayerPrevious->next = currentNode->left;
                        nextLayerPrevious = currentNode->left;
                    } else {
                        nextLayerPrevious = currentNode->left;
                        nextLayerFirst = nextLayerPrevious;
                    }
                }
                if (currentNode->right) {
                    if (nextLayerPrevious) {
                        nextLayerPrevious->next = currentNode->right;
                        nextLayerPrevious = currentNode->right;
                    } else {
                        nextLayerPrevious = currentNode->right;
                        nextLayerFirst = nextLayerPrevious;
                    }
                }

                currentNode = currentNode->next;
            }

            currentNode = nextLayerFirst;
            nextLayerFirst = nullptr;
            nextLayerPrevious = nullptr;
        }

        return root;
    }
};


//void test(const std::vector<int>& ratings, const int expectedResult) {
//    static auto solutionInstance = Solution();
//
//    auto ratingsCopy = ratings;
//    auto result = solutionInstance.candy(ratingsCopy);
//
//    if (result == expectedResult) {
//        std::cout << "[Correct] " << ratings << ": " << result << std::endl;
//    } else {
//        std::cout << "[Wrong] " << ratings << ": " << result << " (should be " << expectedResult << ")" << std::endl;
//    }
//}


int main() {
    return 0;
}
