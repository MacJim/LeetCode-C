/*
 * 116. Populating Next Right Pointers in Each Node
 * https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
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

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
            : val(_val), left(_left), right(_right), next(_next) {}
};


#pragma mark - 1. Recursion, get right-most nodes of left subtree and left-most nodes of right subtree
// Runtime: 20 ms, faster than 53.58% of C++ online submissions for Populating Next Right Pointers in Each Node.
// Memory Usage: 16.7 MB, less than 86.88% of C++ online submissions for Populating Next Right Pointers in Each Node.
class Solution {
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

            left = left->right;
            right = right->left;
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
