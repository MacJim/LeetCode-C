/*
 * This is a duplicate of question 297's solution.
 */

#include <iostream>
#include <string>


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class TreeHelper {
public:
    // MARK: 2. Simplified 1.
    // Runtime: 40 ms, faster than 60.65% of C++ online submissions for Serialize and Deserialize Binary Tree.
    // Memory Usage: 24.9 MB, less than 93.10% of C++ online submissions for Serialize and Deserialize Binary Tree.
    /*
     * - An empty character means no child at the specified position.
     *
     * Examples:
     *
     * - "1,2,5,3,,,,,4"
     */
    static std::string serialize(TreeNode* root);
    static TreeNode* deserialize(std::string data);
};