/*
 * 49. Group Anagrams
 * https://leetcode.com/problems/group-anagrams/
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>


// MARK: - 1
class Solution1 {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& inputStrings) {
        const auto inputStringsSize = inputStrings.size();
        if (inputStringsSize == 0) {
            return {};
        }

        auto returnValue = std::vector<std::vector<std::string>>();
        auto returnValueCharactersOccurrances = std::vector<std::vector<int>>();

        for (const auto& anInputString: inputStrings) {
            
        }

        return returnValue;
    }
};


// MARK: - 2. Sort strings
// Runtime: 272 ms, faster than 5.01% of C++ online submissions for Group Anagrams.
// Memory Usage: 17.7 MB, less than 95.52% of C++ online submissions for Group Anagrams.
class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& inputStrings) {
        const auto inputStringsSize = inputStrings.size();
        if (inputStringsSize == 0) {
            return {};
        }
        
        auto sortedStrings = inputStrings;
        for (auto& aString: sortedStrings) {
            std::sort(aString.begin(), aString.end());
        }

        auto returnValue = std::vector<std::vector<std::string>>();
        auto returnValueSortedRepresentations = std::vector<std::string>(); 

        for (size_t i = 0; i < inputStringsSize; i += 1) {
            auto currentInput = inputStrings.at(i);
            auto currentRepresentation = sortedStrings.at(i);
            auto iterator = std::find(returnValueSortedRepresentations.begin(), returnValueSortedRepresentations.end(), currentRepresentation);
            if (iterator == returnValueSortedRepresentations.end()) {
                returnValue.push_back({currentInput});
                returnValueSortedRepresentations.push_back(currentRepresentation);
            } else {
                const auto returnValueIndex = std::distance(returnValueSortedRepresentations.begin(), iterator);
                returnValue.at(returnValueIndex).push_back(currentInput);
            }
        }

        return returnValue;
    }
};


void printResult(std::vector<std::vector<std::string>> result) {
    for (const auto& aGroup: result) {
        for (const auto& aString: aGroup) {
            std::cout << aString << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main () {
    auto solutionInstance = Solution();

    std::vector<std::string> testCase1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto solution1 = solutionInstance.groupAnagrams(testCase1);
    printResult(solution1);
    
    return 0;
}
