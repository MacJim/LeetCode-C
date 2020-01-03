#include <vector>
#include <sstream>

#include "TreeNode.hpp"


std::string TreeHelper::serialize(TreeNode* root) {
    if (root == nullptr) {
        return "";
    }
    
    std::string returnValue = "";
    
    std::vector<TreeNode*> currentNodesToWalk;
    std::vector<TreeNode*> nextNodesToWalk;
    
    // Root node.
    returnValue += std::to_string(root->val);
    currentNodesToWalk.push_back(root->left);
    currentNodesToWalk.push_back(root->right);
    
    while (!currentNodesToWalk.empty()) {
        for (const auto& currentNodeToInspect: currentNodesToWalk) {
            if (currentNodeToInspect == nullptr) {
                returnValue += ",";
            } else {
                int currentValue = currentNodeToInspect->val;
                returnValue += ("," + std::to_string(currentValue));
                
                nextNodesToWalk.push_back(currentNodeToInspect->left);
                nextNodesToWalk.push_back(currentNodeToInspect->right);
            }
        }
        
        currentNodesToWalk = nextNodesToWalk;
        nextNodesToWalk.clear();
    }
    
    return returnValue;
}

TreeNode* TreeHelper::deserialize(std::string data) {
    auto dataLength = data.size();
    
    if (dataLength == 0) {
        return nullptr;
    }
    
    std::vector<TreeNode*> currentNumbersToProcess;
    std::vector<TreeNode*> followingNumbersToProcess;
    
    // Helpers variables in.
    std::stringstream dataStream (data);
    std::string currentString;
    
    // First number.
    getline(dataStream, currentString, ',');
    int firstNumber = std::stoi(currentString);
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
