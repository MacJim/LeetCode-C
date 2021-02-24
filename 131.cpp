/**
 * 131. Palindrome Partitioning
 * https://leetcode.com/problems/palindrome-partitioning/
 */

#include <iostream>
#include <vector>
#include <memory>

#include "helpers/Operators.hpp"

using namespace std;


#pragma mark - 1. Brute force
// June 2019 (runtime and memory usage might be outdated)
// Runtime: 12 ms, faster than 97.50% of C++ online submissions for Palindrome Partitioning.
// Memory Usage: 12.7 MB, less than 85.19% of C++ online submissions for Palindrome Partitioning.
class Solution1 {
public:
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


#pragma mark - 2. Recursion
// Feb 2021
// Runtime: 428 ms, faster than 11.07% of C++ online submissions for Palindrome Partitioning.
// Memory Usage: 350.3 MB, less than 5.01% of C++ online submissions for Palindrome Partitioning.
class Solution2 {
private:
    bool isPalindrome(const std::string& s, int start, int end) {
        if (start == end) {
            return true;
        }

        while (start < end) {
            if (s[start] != s[end]) {
                return false;
            }
            start += 1;
            end -= 1;
        }

        return true;
    }

    std::vector<std::vector<std::string>> partitionRecursively(const std::string& s, const int end) {
        if (end == 0) {
            // First char.
            return {{std::string(1, s[0])}};
        }

        auto returnValue = std::vector<std::vector<std::string>>();

        // Odd. Centered on i.
        for (int i = end; (i - (end - i)) >= 0; i -= 1) {
            const int start = i - (end - i);
            if (isPalindrome(s, start, end)) {
                auto subStr = s.substr(start, end - start + 1);
                if (start == 0) {
                    returnValue.push_back({subStr});
                } else {
                    auto remainingPartition = partitionRecursively(s, start - 1);
                    for (auto partition: remainingPartition) {
                        partition.push_back(subStr);
                        returnValue.push_back(std::move(partition));
                    }
                }
            }
        }

        // Even.
        // i is in fact (i - 0.5).
        for (int i = end; ((i - 1) - (end - i)) >= 0; i -= 1) {
            const int start = (i - 1) - (end - i);
            if (isPalindrome(s, start, end)) {
                auto subStr = s.substr(start, end - start + 1);
                if (start == 0) {
                    returnValue.push_back({subStr});
                } else {
                    auto remainingPartition = partitionRecursively(s, start - 1);
                    for (auto partition: remainingPartition) {
                        partition.push_back(subStr);
                        returnValue.push_back(std::move(partition));
                    }
                }
            }
        }

        return returnValue;
    }

public:
    std::vector<std::vector<std::string>> partition(const std::string& s) {
        if (s.size() == 1) {
            return {{s}};
        }

        return partitionRecursively(s, s.size() - 1);
    }
};


#pragma mark - 3. Optimized 2: Use references
// Feb 2021
// Runtime: 208 ms, faster than 38.71% of C++ online submissions for Palindrome Partitioning.
// Memory Usage: 135.5 MB, less than 30.62% of C++ online submissions for Palindrome Partitioning.
class Solution {
private:
    bool isPalindrome(const std::string& s, int start, int end) {
        if (start == end) {
            return true;
        }

        while (start < end) {
            if (s[start] != s[end]) {
                return false;
            }
            start += 1;
            end -= 1;
        }

        return true;
    }

    std::vector<std::vector<std::string>> partitionRecursively(const std::string& s, const int end) {
        if (end == 0) {
            // First char.
            return {{std::string(1, s[0])}};
        }

        auto returnValue = std::vector<std::vector<std::string>>();

        // Odd. Centered on i.
        for (int i = end; (i - (end - i)) >= 0; i -= 1) {
            const int start = i - (end - i);
            if (isPalindrome(s, start, end)) {
                auto subStr = s.substr(start, end - start + 1);
                if (start == 0) {
                    returnValue.push_back({std::move(subStr)});
                } else {
                    auto remainingPartition = partitionRecursively(s, start - 1);
                    for (auto& partition: remainingPartition) {
                        partition.push_back(subStr);
                        returnValue.push_back(std::move(partition));
                    }
                }
            }
        }

        // Even.
        // i is in fact (i - 0.5).
        for (int i = end; ((i - 1) - (end - i)) >= 0; i -= 1) {
            const int start = (i - 1) - (end - i);
            if (isPalindrome(s, start, end)) {
                auto subStr = s.substr(start, end - start + 1);
                if (start == 0) {
                    returnValue.push_back({std::move(subStr)});
                } else {
                    auto remainingPartition = partitionRecursively(s, start - 1);
                    for (auto& partition: remainingPartition) {
                        partition.push_back(subStr);
                        returnValue.push_back(std::move(partition));
                    }
                }
            }
        }

        return returnValue;
    }

public:
    std::vector<std::vector<std::string>> partition(const std::string& s) {
        if (s.size() == 1) {
            return {{s}};
        }

        return partitionRecursively(s, s.size() - 1);
    }
};


void printResult(const vector<vector<string>>& resultToPrint) {
    std::cout << string(21, '=') << std::endl;
    for (const auto& aResultSet: resultToPrint) {
        std::cout << aResultSet << std::endl;
    }
}

int main() {
    unique_ptr<Solution> solutionInstance1 (new Solution());
    auto result1 = solutionInstance1->partition("aab");
    printResult(result1);

    unique_ptr<Solution> solutionInstance2 (new Solution());
    auto result2 = solutionInstance2->partition("aabaa");
    printResult(result2);    // 6 results

    unique_ptr<Solution> solutionInstance3 (new Solution());
    auto result3 = solutionInstance3->partition("aaaabaa");
    printResult(result3);    // 22 results

    unique_ptr<Solution> solutionInstance4 (new Solution());
    auto result4 = solutionInstance4->partition("a");
    printResult(result4);    // {{"a"}}
    
    return 0;
}
