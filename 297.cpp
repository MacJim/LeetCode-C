/*
 * 297. Serialize and Deserialize Binary Tree
 * https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
 */

/*
 * Must encode to a string.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <memory>
#include <stack>
#include <queue>

using namespace std;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:
    // MARK: 1. The LeetCode format "1,2,3,n,n,4,5".
    // Result: Time Limit Exceeded
    // Encodes a tree to a single string.
    string serialize1(TreeNode* root) {
        if (root == nullptr) {
            return "";
        }
        
        string returnValue = "";
        
        vector<TreeNode*> lastNodes = {root};
        
        vector<TreeNode*> currentNodes;
        //`true` if `currentNodes` contains at least one non-null value.
        bool hasValidCurrentNodes = false;
        
        while (true) {
            for (auto& aNode: lastNodes) {
                if (aNode == nullptr) {
                    currentNodes.push_back(nullptr);
                    currentNodes.push_back(nullptr);
                    returnValue += ",n";
                } else {
                    returnValue += "," + to_string(aNode->val);
                    
                    currentNodes.push_back(aNode->left);
                    currentNodes.push_back(aNode->right);
                    
                    if ((aNode->left != nullptr) || (aNode->right != nullptr)) {
                        hasValidCurrentNodes = true;
                    }
                }
            }
            
            if (!hasValidCurrentNodes) {
                break;
            } else {
                lastNodes.clear();
                lastNodes = currentNodes;
                currentNodes.clear();
                hasValidCurrentNodes = false;
            }
        }
        
        returnValue.erase(returnValue.begin());
        
        return returnValue;
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize1(string data) {
        auto dataLength = data.size();
        
        if (dataLength == 0) {
            return nullptr;
        }
        
        TreeNode* rootNode = nullptr;
        
        vector<TreeNode*> lastNodes;
        int currentIndexInLastNodes = 0;
        bool isLeftChildInLastNodes = true;
        
        vector<TreeNode*> currentNodes;
        
        //Split the string into substrings.
        stringstream dataStream (data);
        string currentString;
        while (getline(dataStream, currentString, ',')) {
            //1. Get current node value.
            TreeNode* currentNode = nullptr;
            if (currentString != "n") {
                //Convert number to int.
                int decodedNumber = stoi(currentString);
                currentNode = new TreeNode(decodedNumber);
            }
            
            //2. Root node.
            if (rootNode == nullptr) {
                rootNode = currentNode;
                lastNodes = {rootNode};
                currentIndexInLastNodes = 0;
                isLeftChildInLastNodes = true;
                
                continue;
            }
            
            //3. Add current node to tree structure.
            currentNodes.push_back(currentNode);
            if (isLeftChildInLastNodes) {
                auto parentNode = lastNodes.at(currentIndexInLastNodes);
                if (parentNode != nullptr) {
                    lastNodes.at(currentIndexInLastNodes)->left = currentNode;
                }
                isLeftChildInLastNodes = false;
            } else {
                auto parentNode = lastNodes.at(currentIndexInLastNodes);
                if (parentNode != nullptr) {
                    lastNodes.at(currentIndexInLastNodes)->right = currentNode;
                }
                currentIndexInLastNodes += 1;
                isLeftChildInLastNodes = true;
                
                //4. See if all nodes in `lastNodes` have their children.
                if (currentIndexInLastNodes >= lastNodes.size()) {
                    currentIndexInLastNodes = 0;
                    
                    lastNodes.clear();
                    lastNodes = currentNodes;
                    currentNodes.clear();
                }
            }
        }
        
        return rootNode;
    }
    
    
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

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));


int main() {
    unique_ptr<Codec> solutionInstance (new Codec());
    
    /*
     * Test strings:
     * - 1,2,3,n,n,4,5
     */
//    string testString;
//    while (cin >> testString) {
//        auto deserializeResult = solutionInstance->deserialize(testString);
//
//        cout << endl;
//    }
    
    // MARK: Test 1
//    vector<string> testStrings1 = {
//        "1,2,3,n,n,4,5",
//        "1,2,n,4,5,n,n"
//    };
//
//    for (const auto& testString: testStrings1) {
//        auto deserializationResult = solutionInstance->deserialize1(testString);
//        auto serializationResult = solutionInstance->serialize1(deserializationResult);
//
//        if (serializationResult == testString) {
//            cout << "Match!" << endl;
//        } else {
//            cout << "Don't match!" << endl;
//        }
//    }
    
    // MARK: Test 2
    vector<string> testStrings2 = {
//        "1,2,5,3,,,,,4",
//        "1,2,3,,,4,5",
//        "1",
        "1,,"
    };
    
    for (const auto& aString: testStrings2) {
        auto deserializationResult = solutionInstance->deserialize(aString);
        auto serializationResult = solutionInstance->serialize(deserializationResult);
        
        cout << flush;
    }
    
    
    return 0;
}
