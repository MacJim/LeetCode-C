/*
 * 652. Find Duplicate Subtrees
 * https://leetcode.com/problems/find-duplicate-subtrees/
 */

#include <iostream>
#include <vector>
#include <memory>
#include <iterator>
#include <sstream>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Codec297 {
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
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "";
        }
        
        string returnValue = "";
        
        vector<TreeNode*> currentNodesToWalk;
        vector<TreeNode*> nextNodesToWalk;
        
        // Root node.
        returnValue += to_string(root->val);
        currentNodesToWalk.push_back(root->left);
        currentNodesToWalk.push_back(root->right);
        
        while (!currentNodesToWalk.empty()) {
            for (const auto& currentNodeToInspect: currentNodesToWalk) {
                if (currentNodeToInspect == nullptr) {
                    returnValue += ",";
                } else {
                    int currentValue = currentNodeToInspect->val;
                    returnValue += ("," + to_string(currentValue));
                    
                    nextNodesToWalk.push_back(currentNodeToInspect->left);
                    nextNodesToWalk.push_back(currentNodeToInspect->right);
                }
            }
            
            currentNodesToWalk = nextNodesToWalk;
            nextNodesToWalk.clear();
        }
        
        return returnValue;
    }
    
    TreeNode* deserialize(string data) {
        auto dataLength = data.size();
        
        if (dataLength == 0) {
            return nullptr;
        }
        
        vector<TreeNode*> currentNumbersToProcess;
        vector<TreeNode*> followingNumbersToProcess;
        
        // Helpers variables in.
        stringstream dataStream (data);
        string currentString;
        
        // First number.
        getline(dataStream, currentString, ',');
        int firstNumber = stoi(currentString);
        TreeNode* rootNode = new TreeNode(firstNumber);
        currentNumbersToProcess.push_back(rootNode);
        
        // Split the string into substrings.
        bool areStringsLeft = true;
        while (areStringsLeft && (!currentNumbersToProcess.empty())) {
            for (const auto& currentNodeToInspect: currentNumbersToProcess) {
                if (getline(dataStream, currentString, ',')) {
                    if (currentString != "") {
                        // `currentNodeToInspect` has a left child.
                        int leftNumber = stoi(currentString);
                        TreeNode* leftNode = new TreeNode(leftNumber);
                        currentNodeToInspect->left = leftNode;
                        followingNumbersToProcess.push_back(leftNode);
                    }
                } else {
                    // No more strings left.
                    areStringsLeft = false;
                    break;
                }
                
                if (getline(dataStream, currentString, ',')) {
                    if (currentString != "") {
                        // `currentNodeToInspect` has a right child.
                        int rightNumber = stoi(currentString);
                        TreeNode* rightNode = new TreeNode(rightNumber);
                        currentNodeToInspect->right = rightNode;
                        followingNumbersToProcess.push_back(rightNode);
                    }
                } else {
                    // No more strings left.
                    areStringsLeft = false;
                    break;
                }
            }
            
            currentNumbersToProcess = followingNumbersToProcess;
            followingNumbersToProcess.clear();
        }
        
        return rootNode;
    }
};


class Solution {
public:    // MARK: Question 297
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
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "";
        }
        
        string returnValue = "";
        
        vector<TreeNode*> currentNodesToWalk;
        vector<TreeNode*> nextNodesToWalk;
        
        // Root node.
        returnValue += to_string(root->val);
        currentNodesToWalk.push_back(root->left);
        currentNodesToWalk.push_back(root->right);
        
        while (!currentNodesToWalk.empty()) {
            for (const auto& currentNodeToInspect: currentNodesToWalk) {
                if (currentNodeToInspect == nullptr) {
                    returnValue += ",";
                } else {
                    int currentValue = currentNodeToInspect->val;
                    returnValue += ("," + to_string(currentValue));
                    
                    nextNodesToWalk.push_back(currentNodeToInspect->left);
                    nextNodesToWalk.push_back(currentNodeToInspect->right);
                }
            }
            
            currentNodesToWalk = nextNodesToWalk;
            nextNodesToWalk.clear();
        }
        
        return returnValue;
    }
    
    TreeNode* deserialize(string data) {
        auto dataLength = data.size();
        
        if (dataLength == 0) {
            return nullptr;
        }
        
        vector<TreeNode*> currentNumbersToProcess;
        vector<TreeNode*> followingNumbersToProcess;
        
        // Helpers variables in.
        stringstream dataStream (data);
        string currentString;
        
        // First number.
        getline(dataStream, currentString, ',');
        int firstNumber = stoi(currentString);
        TreeNode* rootNode = new TreeNode(firstNumber);
        currentNumbersToProcess.push_back(rootNode);
        
        // Split the string into substrings.
        bool areStringsLeft = true;
        while (areStringsLeft && (!currentNumbersToProcess.empty())) {
            for (const auto& currentNodeToInspect: currentNumbersToProcess) {
                if (getline(dataStream, currentString, ',')) {
                    if (currentString != "") {
                        // `currentNodeToInspect` has a left child.
                        int leftNumber = stoi(currentString);
                        TreeNode* leftNode = new TreeNode(leftNumber);
                        currentNodeToInspect->left = leftNode;
                        followingNumbersToProcess.push_back(leftNode);
                    }
                } else {
                    // No more strings left.
                    areStringsLeft = false;
                    break;
                }
                
                if (getline(dataStream, currentString, ',')) {
                    if (currentString != "") {
                        // `currentNodeToInspect` has a right child.
                        int rightNumber = stoi(currentString);
                        TreeNode* rightNode = new TreeNode(rightNumber);
                        currentNodeToInspect->right = rightNode;
                        followingNumbersToProcess.push_back(rightNode);
                    }
                } else {
                    // No more strings left.
                    areStringsLeft = false;
                    break;
                }
            }
            
            currentNumbersToProcess = followingNumbersToProcess;
            followingNumbersToProcess.clear();
        }
        
        return rootNode;
    }

    
public:
    // MARK: 1. Start from leaf nodes.
    // Doesn't work. There's no reference to the parent node!
    vector<TreeNode*> findDuplicateSubtrees1(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }
        
        vector<TreeNode*> returnValue = {};
        
        // 1. Find all leaves.
        vector<TreeNode*> leafNodes;
        stack<TreeNode*> leafNodesFindingTemporaryStack;
        
        leafNodesFindingTemporaryStack.push(root);
        while (!leafNodesFindingTemporaryStack.empty()) {
            auto currentNodeToInspect = leafNodesFindingTemporaryStack.top();
            leafNodesFindingTemporaryStack.pop();
            
            if ((currentNodeToInspect->left == nullptr) && (currentNodeToInspect->right == nullptr)) {
                // This is a leaf.
                leafNodes.push_back(currentNodeToInspect);
            } else {
                // This is not a leaf.
                if (currentNodeToInspect->left != nullptr) {
                    leafNodesFindingTemporaryStack.push(currentNodeToInspect->left);
                }
                if (currentNodeToInspect->right != nullptr) {
                    leafNodesFindingTemporaryStack.push(currentNodeToInspect->right);
                }
            }
        }
        
        // 2. Find same value leaves.
        unordered_map<int, vector<TreeNode*>> sameValueLeaves;
        for (const auto& aLeafNode: leafNodes) {
            if (sameValueLeaves.find(aLeafNode->val) == sameValueLeaves.end()) {
                vector<TreeNode*> temporaryVector = {aLeafNode};
                sameValueLeaves.emplace(aLeafNode->val, temporaryVector);
            } else {
                sameValueLeaves.at(aLeafNode->val).push_back(aLeafNode);
            }
        }
        
        if (!sameValueLeaves.empty()) {
            unordered_map<int, vector<TreeNode*>> sameValueMiddleNodes = move(sameValueLeaves);
            
            while (!sameValueMiddleNodes.empty()) {
                for (const auto& aGroupOfNodes: sameValueMiddleNodes) {
                    returnValue.push_back(aGroupOfNodes.second.front());
                    
                    for (const auto& aNode: aGroupOfNodes.second) {
                        
                    }
                }
            }
        }
        
        
        return returnValue;
    }
    
    
    // MARK: 2. Compare serialization results.
    // Runtime: 580 ms, faster than 5.63% of C++ online submissions for Find Duplicate Subtrees.
    // Memory Usage: 56.6 MB, less than 33.33% of C++ online submissions for Find Duplicate Subtrees.
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }
        
        vector<TreeNode*> returnValue = {};
        
        map<string, int> serializationCounts;
        
        stack<TreeNode*> temporaryStack;
        if (root->left) {
            temporaryStack.push(root->left);
        }
        if (root->right) {
            temporaryStack.push(root->right);
        }
        
        while (!temporaryStack.empty()) {
            TreeNode* topNode = temporaryStack.top();
            temporaryStack.pop();
            if (topNode->left) {
                temporaryStack.push(topNode->left);
            }
            if (topNode->right) {
                temporaryStack.push(topNode->right);
            }
            
            string serializationResult = serialize(topNode);
            
            if (serializationCounts.find(serializationResult) == serializationCounts.end()) {
                // This tree was not found before.
                serializationCounts.emplace(serializationResult, 1);
            } else {
                if (serializationCounts.at(serializationResult) == 1) {
                    // This tree was found once before.
                    returnValue.push_back(topNode);
                    serializationCounts.at(serializationResult) += 1;
                }
            }
        }
        
        return returnValue;
    }
};


int main() {
    unique_ptr<Codec297> codecInstance (new Codec297());
    auto testTree1 = codecInstance->deserialize("1,2,3,4,,2,4,,,4");
    auto testTree2 = codecInstance->deserialize("1,2,2,3,3,3,3");
    
    unique_ptr<Solution> solutionInstance (new Solution());
    auto solution1 = solutionInstance->findDuplicateSubtrees(testTree1);
    auto solution2 = solutionInstance->findDuplicateSubtrees(testTree2);
    
    return 0;
}
