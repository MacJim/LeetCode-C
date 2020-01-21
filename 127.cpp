/*
 * 127. Word Ladder
 * https://leetcode.com/problems/word-ladder/
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>


// MARK: - 1. Graph
// Neighbor nodes are recorded in a graph.
// Runtime: 288 ms, faster than 48.96% of C++ online submissions for Word Ladder.
// Memory Usage: 16.6 MB, less than 45.45% of C++ online submissions for Word Ladder.
class Solution {
public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
        // 1. Find `endWord` in `wordList`.
        auto endWordIterator = std::find(wordList.begin(), wordList.end(), endWord);
        if (endWordIterator == wordList.end()) {
            // `endWord` not found in `wordList`.
            return 0;
        }

        // 2. Find if `beginWord` equals `endWord`.
        if (beginWord == endWord) {
            return 1;
        }

        const size_t wordListCount = wordList.size();
        const auto endWordIndex = std::distance(wordList.begin(), endWordIterator);

        // 3. Initialize neighborhood graph.
        auto beginWordNeighbors = std::unordered_set<int>();
        auto otherNeighbors = std::vector<std::vector<int>>(wordListCount, std::vector<int>());

        const auto beginWordLength = beginWord.size();

        for (size_t i = 0; i < wordListCount; i += 1) {
            const auto& word1 = wordList.at(i);
            const auto length1 = word1.size();

            // Begin word.
            if (length1 == beginWordLength) {
                int differencesFound = 0;
                for (size_t k = 0; k < length1; k += 1) {
                    if (beginWord.at(k) != word1.at(k)) {
                        differencesFound += 1;
                        if (differencesFound > 1) {
                            // More than 1 differences.
                            break;
                        }
                    }
                }

                if (differencesFound == 1) {
                    beginWordNeighbors.insert(i);
                }
            }

            // Other words.
            for (size_t j = (i + 1); j < wordListCount; j += 1) {
                const auto& word2 = wordList.at(j);
                const auto length2 = word2.size();

                if (length1 != length2) {
                    continue;
                }

                int differencesFound = 0;
                for (size_t k = 0; k < length1; k += 1) {
                    if (word1.at(k) != word2.at(k)) {
                        differencesFound += 1;
                        if (differencesFound > 1) {
                            // More than 1 difference.
                            break;
                        }
                    }
                }

                if (differencesFound == 1) {
                    // They are neighbors.
                    otherNeighbors.at(i).push_back(j);
                    otherNeighbors.at(j).push_back(i);
                }
            }
        }

        // 4. Search in graph.
        int currentDistance = 2;
        // Distance from begin word to words in the word list.
        // -1 means unreachable.
        auto distances = std::vector<int>(wordListCount, -1);

        auto currentWordIndices = beginWordNeighbors;
        auto nextWordIndices = std::unordered_set<int>();

        for (; !currentWordIndices.empty(); currentDistance += 1) {
            for (const int& currentWordIndex: currentWordIndices) {
                auto& recordedDistance = distances.at(currentWordIndex);
                if ((recordedDistance == -1) || (recordedDistance > currentDistance)) {
                    if (currentWordIndex == endWordIndex) {
                        return currentDistance;
                    }

                    recordedDistance = currentDistance;
                    for (const int& aNeighborIndex: otherNeighbors.at(currentWordIndex)) {
                        nextWordIndices.insert(aNeighborIndex);
                    }
                }
            }

            currentWordIndices = std::move(nextWordIndices);
            nextWordIndices = std::unordered_set<int>();
        }

        return 0;
    }
};


int main() {
    auto solutionInstance = Solution();

    std::string startWord1 = "hit";
    std::string endWord1 = "cog";
    std::vector<std::string> wordList1 = {"hot","dot","dog","lot","log","cog"};
    std::cout << solutionInstance.ladderLength(startWord1, endWord1, wordList1) << std::endl;    // 5
    
    std::string startWord2 = "hit";
    std::string endWord2 = "cog";
    std::vector<std::string> wordList2 = {"hot","dot","dog","lot","log"};
    std::cout << solutionInstance.ladderLength(startWord2, endWord2, wordList2) << std::endl;    // 0 (end word not in word list)

    std::string startWord3 = "hit";
    std::string endWord3 = "hot";
    std::vector<std::string> wordList3 = {"hot","dot","dog","lot","log"};
    std::cout << solutionInstance.ladderLength(startWord3, endWord3, wordList3) << std::endl;    // 2

    return 0;
}
