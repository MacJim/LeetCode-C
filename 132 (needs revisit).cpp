/**
 * 132. Palindrome Partitioning II
 * https://leetcode.com/problems/palindrome-partitioning-ii/
 */

#include <iostream>
#include <vector>
#include <memory>

using namespace std;


class Solution {
public:
    // MARK: 1. Copied from question 131.
    // Result: Memory Limit Exceeded!!! On my computer, the memory usage easily exceeded 2GB...
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
    
    int minCut1(string s) {
        auto stringLength = s.length();
        if (stringLength == 0) {
            return 0;
        }
        
        auto partitionResult = partition(s);
        int minimumPartitionsCount = INT_MAX;
        
        for (auto& aPartition: partitionResult) {
            auto currentPartitionsCount = aPartition.size();
            if (currentPartitionsCount < minimumPartitionsCount) {
                minimumPartitionsCount = currentPartitionsCount;
            }
        }
        
        return minimumPartitionsCount - 1;
    }
    
    
    // MARK: 2. Greedier
    // Result: Time Limit Exceeded.
    void searchForLongestPalindromeFromStart(const string& s, int startIndex, int& currentPartitionsCount, int& minimumPartitionsCount) {
        auto stringLength = s.length();
        if (startIndex >= stringLength) {
            if ((currentPartitionsCount < minimumPartitionsCount) || (minimumPartitionsCount == -1)) {
                minimumPartitionsCount = currentPartitionsCount;
            }
        }
        
        for (int i = stringLength - 1; i >= startIndex; i -= 1) {
            if (!isStringPartitionPalindrome(s, startIndex, i)) {
                continue;
            }
            
            currentPartitionsCount += 1;
            searchForLongestPalindromeFromStart(s, i + 1, currentPartitionsCount, minimumPartitionsCount);
            currentPartitionsCount -= 1;
            
            if (minimumPartitionsCount == 1) {
                return;
            }
        }
    }
    
    int minCut2(string s) {
        auto stringLength = s.length();
        if (stringLength == 0) {
            return 0;
        }
        
        int minimumPartitionsCount = -1;
        int currentPartitionsCount = 0;
        searchForLongestPalindromeFromStart(s, 0, currentPartitionsCount, minimumPartitionsCount);
        
        return (minimumPartitionsCount - 1);
    }
    
    
    // MARK: 3
    // Source: https://leetcode.com/problems/palindrome-partitioning-ii/discuss/42212/Two-C%2B%2B-versions-given-(one-DP-28ms-one-Manancher-like-algorithm-10-ms)
    // Runtime: 8 ms, faster than 95.89% of C++ online submissions for Palindrome Partitioning II.
    // Memory Usage: 8.5 MB, less than 90.98% of C++ online submissions for Palindrome Partitioning II.
    int minCut(string s) {
        auto stringLength = s.length();
        if (stringLength == 0) {
            return 0;
        }

        int minCuts[stringLength + 1];
        for (int i = 0; i <= stringLength; i += 1) {
            minCuts[i] = i - 1;
        }

        for (int center = 1; center < stringLength; center += 1) {
            // Odd-length substrings.
            for (int sideLength = 0; (center >= sideLength) && ((center + sideLength) < stringLength) && (s[center - sideLength] == s[center + sideLength]); sideLength += 1) {
                // Update the min cuts count if `s[center - sideLength]` to `s[center + sideLength]` is a palindrome.
                minCuts[center + sideLength + 1] = min(minCuts[center + sideLength + 1], 1 + minCuts[center - sideLength]);
            }

            // Even-length substrings.
            for (int sideLength = 0; (center >= (sideLength + 1)) && ((center + sideLength) < stringLength) && (s[center - sideLength - 1] == s[center + sideLength]); sideLength += 1) {
                // Update the min cuts count if `s[center - sideLength - 1]` to `s[center + sideLength]` is a palindrome.
                minCuts[center + sideLength + 1] = min(minCuts[center + sideLength + 1], 1 + minCuts[center - sideLength - 1]);
            }
        }
        return minCuts[stringLength];
    }
};

int main() {
    unique_ptr<Solution> solutionInstance (new Solution());
    
    cout << solutionInstance->minCut("aab") << endl;    //1
    cout << solutionInstance->minCut("ababababababababababababcbabababababababababababa") << endl;    //0
    cout << solutionInstance->minCut("aabaa") << endl;    //0
    cout << solutionInstance->minCut("") << endl;    //0
    cout << solutionInstance->minCut("aaaabaa") << endl;    //1
    cout << solutionInstance->minCut("apjesgpsxoeiokmqmfgvjslcjukbqxpsobyhjpbgdfruqdkeiszrlmtwgfxyfostpqczidfljwfbbrflkgdvtytbgqalguewnhvvmcgxboycffopmtmhtfizxkmeftcucxpobxmelmjtuzigsxnncxpaibgpuijwhankxbplpyejxmrrjgeoevqozwdtgospohznkoyzocjlracchjqnggbfeebmuvbicbvmpuleywrpzwsihivnrwtxcukwplgtobhgxukwrdlszfaiqxwjvrgxnsveedxseeyeykarqnjrtlaliyudpacctzizcftjlunlgnfwcqqxcqikocqffsjyurzwysfjmswvhbrmshjuzsgpwyubtfbnwajuvrfhlccvfwhxfqthkcwhatktymgxostjlztwdxritygbrbibdgkezvzajizxasjnrcjwzdfvdnwwqeyumkamhzoqhnqjfzwzbixclcxqrtniznemxeahfozp") << endl;    //452
    
    return 0;
}

