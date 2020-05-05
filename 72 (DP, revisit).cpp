/*
 * 72. Edit Distance
 * https://leetcode.com/problems/edit-distance/
 */

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <numeric>    // std::iota


#pragma mark - 1. My own "Tree Trim" solution
// This solution is WRONG. Under certain cases we don't retain the same characters because they are in utterly different positions.
class Solution1 {
private:
    /// Find the longest same characters in the same order.
    int evaluateSubstrings(std::string& targetString, std::string& dictionaryString, size_t& targetStringLength, size_t& dictionaryStringLength, size_t startIndexInTargetString, size_t startIndexInDictionary) {
        int returnValue = 0;

        for (size_t i = startIndexInDictionary; i < dictionaryStringLength; i += 1) {
            const char& currentChar = dictionaryString.at(i);
            const auto targetI = targetString.find(currentChar, startIndexInTargetString);    // This is the index in the target string.

            if (targetI == std::string::npos) {
                // Not found.
                continue;
            }

            if (targetI == (targetStringLength - 1)) {
                // This is the last character.
                returnValue = std::max(returnValue, 1);
            } else {
                // This character has been found in the target string.
                returnValue = std::max(returnValue, evaluateSubstrings(targetString, dictionaryString, targetStringLength, dictionaryStringLength, targetI + 1, i + 1) + 1);
            }
        }

        return returnValue;
    }

public:
    int minDistance(std::string word1, std::string word2) {
        auto length1 = word1.size();
        auto length2 = word2.size();

        // `word1` is always longer than `word2`.
        if (length1 < length2) {
            std::swap(word1, word2);
            std::swap(length1, length2);
        }

        int recurringCharactersCount = evaluateSubstrings(word1, word2, length1, length2, 0, 0);

        int additions = length1 - length2;
        int replacements = length2 - recurringCharactersCount;
        int returnValue = additions + replacements;

        return returnValue;
    }
};


#pragma mark - 2. Dynamic Programming
/*
 * Reference: https://leetcode.com/problems/edit-distance/discuss/25846/C%2B%2B-O(n)-space-DP
 *
 * Key idea: DP: Compare word1[0:i] and word2[0:j]
 *
 * - When word1[i] == word2[j], distance[i, j] = distance[i - 1, j - 1]
 * - When they don't equal, we may:
 *   - Add a character: distance[i, j] = distance[i, j - 1] + 1
 *   - Delete a character: distance[i, j] = distance[i, j - 1] + 1
 *   - Replace a character: distance[i, j] = distance[i - 1, j - 1] + 1
 */
// Runtime: 28 ms, faster than 18.56% of C++ online submissions for Edit Distance.
// Memory Usage: 11.1 MB, less than 65.63% of C++ online submissions for Edit Distance.
class Solution2 {
public:
    int minDistance(std::string word1, std::string word2) {
        const auto wordLen1 = word1.size();
        const auto wordLen2 = word2.size();

        const auto arrayLen1 = wordLen1 + 1;
        const auto arrayLen2 = wordLen2 + 1;

        /// Indices: word1, word2
        /// Index 0 is reserved for the empty string.
        auto distances = std::vector<std::vector<size_t>>(arrayLen1, std::vector<size_t>(arrayLen2, 0));

        for (size_t j = 0; j < arrayLen2; j += 1) {
            distances.at(0).at(j) = j;
        }

        for (size_t i = 0; i < wordLen1; i += 1) {
            const auto& c1 = word1.at(i);

            distances.at(i + 1).at(0) = i + 1;

            for (size_t j = 0; j < wordLen2; j += 1) {
                const auto& c2 = word2.at(j);

                if (c1 == c2) {
                    distances.at(i + 1).at(j + 1) = distances.at(i).at(j);
                } else {
                    distances.at(i + 1).at(j + 1) = std::min(distances.at(i).at(j), std::min(distances.at(i + 1).at(j), distances.at(i).at(j + 1))) + 1;
                }
            }
        }

        return distances.at(arrayLen1 - 1).at(arrayLen2 - 1);
    }
};


#pragma mark - 3. Improved 2
// Runtime: 20 ms, faster than 36.99% of C++ online submissions for Edit Distance.
// Memory Usage: 10.4 MB, less than 71.88% of C++ online submissions for Edit Distance.
class Solution {
public:
    int minDistance(std::string word1, std::string word2) {
        const auto wordLen1 = word1.size();
        const auto wordLen2 = word2.size();

        const auto arrayLen1 = wordLen1 + 1;
        const auto arrayLen2 = wordLen2 + 1;

        auto previousRowDistances = std::vector<size_t>(arrayLen2, 0);
        auto currentRowDistances = std::vector<size_t>(arrayLen2, 0);

        std::iota(previousRowDistances.begin(), previousRowDistances.end(), 0);

        for (size_t i = 0; i < wordLen1; i += 1) {
            const auto& c1 = word1.at(i);

            currentRowDistances.at(0) = i + 1;

            for (size_t j = 0; j < wordLen2; j += 1) {
                const auto& c2 = word2.at(j);
                if (c1 == c2) {
                    currentRowDistances.at(j + 1) = previousRowDistances.at(j);
                } else {
                    currentRowDistances.at(j + 1) = std::min(previousRowDistances.at(j), std::min(previousRowDistances.at(j + 1), currentRowDistances.at(j))) + 1;
                }
            }

            previousRowDistances = std::move(currentRowDistances);
            currentRowDistances = std::vector<size_t>(arrayLen2, 0);
        }

        return previousRowDistances.back();
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<std::pair<std::string, std::string>> testCases = {
        std::make_pair("horse", "ros"),    // 3
        std::make_pair("intention", "execution"),    // 5
    };

    for (const auto &testCase: testCases) {
        int result = solutionInstance.minDistance(testCase.first, testCase.second);
        std::cout << testCase.first << " -> " << testCase.second << " cost: " << result << std::endl;
    }

    return 0;
}
