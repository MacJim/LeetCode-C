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
class Solution2 {
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


// MARK: - 3. Use string as character occurrance hash.
// Runtime: 116 ms, faster than 11.46% of C++ online submissions for Group Anagrams.
// Memory Usage: 27 MB, less than 5.97% of C++ online submissions for Group Anagrams.
class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        const auto strsSize = strs.size();
        if (strsSize == 0) {
            return {};
        }

        auto hashes = std::unordered_map<std::string, std::vector<size_t>>();

        for (size_t i = 0; i < strs.size(); i += 1) {
            const auto& aStr = strs.at(i);

            // 26 characters
            auto occurrances = std::vector<int>(26, 0);
            for (const char& c: aStr) {
                const size_t j = c - 'a';
                occurrances.at(j) += 1;
            }

            std::string hash = "";
            for (const int& anOccurrance: occurrances) {
                hash += std::to_string(anOccurrance);
                hash += ".";
            }
            
            auto it = hashes.find(hash);
            if (it == hashes.end()) {
                std::vector<size_t> pos = {i};
                hashes.emplace(hash, std::move(pos));
            } else {
                it->second.push_back(i);
            }
        }

        auto returnValue = std::vector<std::vector<std::string>>();
        for (const auto& aPair: hashes) {
            auto currentReturnValue = std::vector<std::string>();
            for (const auto& i: aPair.second) {
                currentReturnValue.push_back(strs.at(i));
            }
            returnValue.push_back(std::move(currentReturnValue));
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
