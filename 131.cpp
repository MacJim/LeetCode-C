/**
 * 131. Palindrome Partitioning
 * https://leetcode.com/problems/palindrome-partitioning/
 */

#include <iostream>
#include <vector>
#include <memory>

using namespace std;


class Solution {
public:
    //MARK: 1. Brute force.
    //Runtime: 12 ms, faster than 97.50% of C++ online submissions for Palindrome Partitioning.
    //Memory Usage: 12.7 MB, less than 85.19% of C++ online submissions for Palindrome Partitioning.
    /**
     * `startIndex` and `endIndex` are both inclusive.
     */
    bool isStringPartitionPalindrome(const string& s, int startIndex, int endIndex) {
        while (startIndex <= endIndex) {
            if (s.at(startIndex) != s.at(endIndex)) {
                return false;
            }
            
            startIndex += 1;
            endIndex -= 1;
        }
        
        return true;
    }
    
    void searchForPalindrome(const string& s, int startIndex, vector<string>& currentResult, vector<vector<string>>& allResults) {
        auto stringLength = s.length();
        if (startIndex >= stringLength) {
            allResults.push_back(currentResult);
            return;
        }
        
        //See if `startIndex ~ i` is a palindrome string.
        for (int i = startIndex; i < stringLength; i += 1) {
            if (!isStringPartitionPalindrome(s, startIndex, i)) {
                continue;
            }
            
            auto currentSubstring = s.substr(startIndex, i - startIndex + 1);
            currentResult.push_back(currentSubstring);
            searchForPalindrome(s, i + 1, currentResult, allResults);
            currentResult.pop_back();
        }
    }
    
    vector<vector<string>> partition(string s) {
        vector<vector<string>> returnValue;
        
        auto stringLength = s.length();
        if (stringLength == 0) {
            return returnValue;
        }
        
        vector<string> currentResult;
        
        searchForPalindrome(s, 0, currentResult, returnValue);
        
        return returnValue;
    }
};

void printResult(vector<vector<string>> resultToPrint) {
    cout << string(21, '=') << endl;
    for (auto aResultSet: resultToPrint) {
        for (auto aResult: aResultSet) {
            cout << aResult << " ";
        }
        cout << endl;
    }
}

int main() {
    unique_ptr<Solution> solutionInstance (new Solution());
    
    auto result1 = solutionInstance->partition("aab");
    printResult(result1);
    
    auto result2 = solutionInstance->partition("aabaa");
    printResult(result2);
    
    auto result3 = solutionInstance->partition("aaaabaa");
    printResult(result3);
    
    return 0;
}
