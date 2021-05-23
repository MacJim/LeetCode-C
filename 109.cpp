/*
 * 109. Convert Sorted List to Binary Search Tree
 * https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
 */

#include <iostream>
#include <vector>

#include "helpers/ListNode.hpp"
#include "helpers/TreeNode.hpp"
#include "helpers/Operators.hpp"


#pragma mark - 1. Slow and fast pointers
// Runtime: 40 ms, faster than 9.94% of C++ online submissions for Convert Sorted List to Binary Search Tree.
// Memory Usage: 30.9 MB, less than 70.52% of C++ online submissions for Convert Sorted List to Binary Search Tree.
class Solution1 {
private:
    TreeNode* recursion(ListNode* head) {
        if (!head) {
            return nullptr;
        }
        if (!head->next) {
            return new TreeNode(head->val);
        }

        ListNode* previous = nullptr;
        auto slow = head;
        auto fast = head;

        while (fast->next && fast->next->next) {
            previous = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        auto root = new TreeNode(slow->val);

        if (previous) {
            previous->next = nullptr;
            root->left = recursion(head);
        }
        root->right = recursion(slow->next);

        return root;
    }

public:
    TreeNode* sortedListToBST(ListNode* head) {
        return recursion(head);
    }
};


#pragma mark - 2. Create the tree in-order with a temporary value (not my solution, no need to re-visit)
/*
 * 1. Count the amount of nodes
 * 2. Create a tree using the same method as solution 1
 * 3. Assign value according to in-order
 */
// Runtime: 44 ms, faster than 8.87% of C++ online submissions for Convert Sorted List to Binary Search Tree.
// Memory Usage: 31.1 MB, less than 49.39% of C++ online submissions for Convert Sorted List to Binary Search Tree.
class Solution {
private:
    ListNode* currentListNode;

    TreeNode* recursion(int left, int right) {
        if (left > right) {
            return nullptr;
        }

        auto mid = (left + right) / 2;

        auto leftChild = recursion(left, mid - 1);

        auto currentTreeNode = new TreeNode(currentListNode->val);
        currentListNode = currentListNode->next;

        auto rightChild = recursion(mid + 1, right);

        currentTreeNode->left = leftChild;
        currentTreeNode->right = rightChild;

        return currentTreeNode;
    }

public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) {
            return nullptr;
        }
        if (!head->next) {
            return new TreeNode(head->val);
        }

        currentListNode = head;
        int count = 0;
        while (currentListNode) {
            count += 1;
            currentListNode = currentListNode->next;
        }

        currentListNode = head;

        return recursion(0, count - 1);
    }
};


void test(const std::vector<int>& listVec) {
    static auto solutionInstance = Solution();

    auto head = ListHelper::deserialize(listVec);
    auto result = solutionInstance.sortedListToBST(head);
    auto resultVec = TreeHelper::inOrderTraverse(result);

    if (listVec == resultVec) {
        std::cout << "[Correct] " << listVec << ": " << resultVec << std::endl;
    } else {
        std::cout << "[Wrong] " << listVec << ": " << resultVec << " (should be " << listVec << ")" << std::endl;
    }
}


int main() {
    test({1,2});
    test({1,2,3});
    test({1,2,3,4});
    test({1,2,3,4,5});
    test({1,2,3,4,5,6});
    test({1,2,3,4,5,6,7});
    test({1,2,3,4,5,6,7,8});
    test({1,2,3,4,5,6,7,8,9});
    test({-10,-3,0,5,9});
    test({});
    test({0});
    test({1,3});

//    test({1,2,3}, "2,1,3");
//    test({1,2,3,4}, "2,1,3,,,,4");
//    test({1,2,3,4,5}, "3,2,4,1,,,5");
//    test({-10,-3,0,5,9}, "0,-3,9,-10,,5");
//    test({}, "");
//    test({0}, "0");
//    test({1,3}, "3,1");

    return 0;
}
