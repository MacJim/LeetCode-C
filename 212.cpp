/*
 * 212. Word Search II
 * https://leetcode.com/problems/word-search-ii/
 */

/*
 * Notes:
 * 
 * - The same letter cell may not be used more than once in a word.
 */


#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

using namespace std;


// MARK: 1
// Result: WRONG ANSWER. The same cell might be used more than once.
class SolutionOld1 {
private:
    vector<pair<int, int>> findCharacterPositionsInBoard(const vector<vector<char>>& board, char characterToFind) {
        vector<pair<int, int>> returnValue;

        for (int i = 0; i < board.size(); i += 1) {
            auto currentRow = board.at(i);
            for (int j = 0; j < currentRow.size(); j += 1) {
                char currentCharacter = currentRow.at(j);
                if (currentCharacter == characterToFind) {
                    returnValue.push_back(make_pair(i, j));
                }
            }
        }

        return returnValue;
    }

    unordered_map<char, vector<pair<int, int>>> characterPositionsInBoardCache;
    vector<pair<int, int>> findCharacterPositionsInBoardWithCache(const vector<vector<char>>& board, char characterToFind) {
        if (characterPositionsInBoardCache.find(characterToFind) != characterPositionsInBoardCache.end()) {
            // The current character has been cached.
            return characterPositionsInBoardCache.at(characterToFind);
        }

        vector<pair<int, int>> returnValue;

        for (int i = 0; i < board.size(); i += 1) {
            auto currentRow = board.at(i);
            for (int j = 0; j < currentRow.size(); j += 1) {
                char currentCharacter = currentRow.at(j);
                if (currentCharacter == characterToFind) {
                    returnValue.push_back(make_pair(i, j));
                }
            }
        }

        characterPositionsInBoardCache.emplace(characterToFind, returnValue);

        return returnValue;
    }

    bool findWordRecursively(const vector<vector<char>>& board, string wordToFind, int startX, int startY) {
        auto charactersCount = wordToFind.size();
        if (charactersCount == 0) {
            return true;
        }

        char firstCharacter = wordToFind.at(0);
        
        // 1. Right.
        int rightX = startX + 1;
        if (rightX < board.size()) {
            if (firstCharacter == board.at(rightX).at(startY)) {
                if (charactersCount == 1) {
                    return true;
                } else if (findWordRecursively(board, wordToFind.substr(1), rightX, startY)) {
                    return true;
                }
            }
        }

        // 2. Left.
        int leftX = startX - 1;
        if (leftX >= 0) {
            if (firstCharacter == board.at(leftX).at(startY)) {
                if (charactersCount == 1) {
                    return true;
                } else if (findWordRecursively(board, wordToFind.substr(1), leftX, startY)) {
                    return true;
                }
            }
        }

        // 3. Up.
        int upY = startY + 1;
        if (upY < board.at(0).size()) {
            if (firstCharacter == board.at(startX).at(upY)) {
                if (charactersCount == 1) {
                    return true;
                } else if (findWordRecursively(board, wordToFind.substr(1), startX, upY)) {
                    return true;
                }
            } 
        }

        // 4. Down.
        int downY = startY - 1;
        if (downY >= 0) {
            if (firstCharacter == board.at(startX).at(downY)) {
                if (charactersCount == 1) {
                    return true;
                } else if (findWordRecursively(board, wordToFind.substr(1), startX, downY)) {
                    return true;
                }
            }
        }

        return false;
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        auto wordsCount = words.size();
        if (wordsCount <= 0) {
            return {};
        }

        // 0. Clear the previous cache.
        characterPositionsInBoardCache.clear();

        // 1. Find all starting matches.
        bool shouldUseCacheToFindStartingPoints = false;
        if (wordsCount > 50) {
            shouldUseCacheToFindStartingPoints = true;
        }

        vector<vector<pair<int, int>>> wordsStartingPoints;

        for (const auto& aWord: words) {
            char firstCharacter = aWord.at(0);

            vector<pair<int, int>> matchingPositions;
            if (shouldUseCacheToFindStartingPoints) {
                matchingPositions = findCharacterPositionsInBoard(board, firstCharacter);
            } else {
                matchingPositions = findCharacterPositionsInBoardWithCache(board, firstCharacter);
            }

            wordsStartingPoints.push_back(matchingPositions);
        }

        // 2. Start from the starting matches.
        vector<string> returnValue = {};

        for (int i = 0; i < words.size(); i += 1) {
            auto currentStartingPoints = wordsStartingPoints.at(i);
            if (currentStartingPoints.size() == 0) {
                continue;
            }
            
            string currentWord = words.at(i);
            for (const auto& aStartingPoint: currentStartingPoints) {
                if (findWordRecursively(board, currentWord.substr(1), aStartingPoint.first, aStartingPoint.second)) {
                    returnValue.push_back(currentWord);
                    break;
                }
            }
        }

        return returnValue;
    }
};


// MARK: 2. Revised 1
// Result: Time Limit Exceeded.
class SolutionOld2 {
private:
    vector<pair<int, int>> findCharacterPositionsInBoard(const vector<vector<char>>& board, char characterToFind) {
        vector<pair<int, int>> returnValue;

        for (int i = 0; i < board.size(); i += 1) {
            auto currentRow = board.at(i);
            for (int j = 0; j < currentRow.size(); j += 1) {
                char currentCharacter = currentRow.at(j);
                if (currentCharacter == characterToFind) {
                    returnValue.push_back(make_pair(i, j));
                }
            }
        }

        return returnValue;
    }

    unordered_map<char, vector<pair<int, int>>> characterPositionsInBoardCache;
    vector<pair<int, int>> findCharacterPositionsInBoardWithCache(const vector<vector<char>>& board, char characterToFind) {
        if (characterPositionsInBoardCache.find(characterToFind) != characterPositionsInBoardCache.end()) {
            // The current character has been cached.
            return characterPositionsInBoardCache.at(characterToFind);
        }

        vector<pair<int, int>> returnValue;

        for (int i = 0; i < board.size(); i += 1) {
            auto currentRow = board.at(i);
            for (int j = 0; j < currentRow.size(); j += 1) {
                char currentCharacter = currentRow.at(j);
                if (currentCharacter == characterToFind) {
                    returnValue.push_back(make_pair(i, j));
                }
            }
        }

        characterPositionsInBoardCache.emplace(characterToFind, returnValue);

        return returnValue;
    }

    bool findWordRecursively(const vector<vector<char>>& board, string wordToFind, vector<pair<int, int>> previousSteps) {
        auto charactersCount = wordToFind.size();
        if (charactersCount == 0) {
            return true;
        }

        char firstCharacter = wordToFind.at(0);

        int startX = previousSteps.back().first;
        int startY = previousSteps.back().second;

        // 1. Right.
        int rightX = startX + 1;
        if (rightX < board.size()) {
            if ((firstCharacter == board.at(rightX).at(startY)) && (find(previousSteps.begin(), previousSteps.end(), make_pair(rightX, startY)) == previousSteps.end())) {
                if (charactersCount == 1) {
                    return true;
                } else {
                    auto currentSteps = previousSteps;
                    currentSteps.push_back(make_pair(rightX, startY));
                    if (findWordRecursively(board, wordToFind.substr(1), currentSteps)) {
                        return true;
                    }
                }
            }
        }

        // 2. Left.
        int leftX = startX - 1;
        if (leftX >= 0) {
            if ((firstCharacter == board.at(leftX).at(startY)) && (find(previousSteps.begin(), previousSteps.end(), make_pair(leftX, startY)) == previousSteps.end())) {
                if (charactersCount == 1) {
                    return true;
                } else {
                    auto currentSteps = previousSteps;
                    currentSteps.push_back(make_pair(leftX, startY));
                    if (findWordRecursively(board, wordToFind.substr(1), currentSteps)) {
                        return true;
                    }
                }
            }
        }

        // 3. Up.
        int upY = startY + 1;
        if (upY < board.at(0).size()) {
            if ((firstCharacter == board.at(startX).at(upY)) && (find(previousSteps.begin(), previousSteps.end(), make_pair(startX, upY)) == previousSteps.end())) {
                if (charactersCount == 1) {
                    return true;
                } else {
                    auto currentSteps = previousSteps;
                    currentSteps.push_back(make_pair(startX, upY));
                    if (findWordRecursively(board, wordToFind.substr(1), currentSteps)) {
                        return true;
                    }
                }
            } 
        }

        // 4. Down.
        int downY = startY - 1;
        if (downY >= 0) {
            if ((firstCharacter == board.at(startX).at(downY)) && (find(previousSteps.begin(), previousSteps.end(), make_pair(startX, downY)) == previousSteps.end())) {
                if (charactersCount == 1) {
                    return true;
                } else {
                    auto currentSteps = previousSteps;
                    currentSteps.push_back(make_pair(startX, downY));
                    if (findWordRecursively(board, wordToFind.substr(1), currentSteps)) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        auto wordsCount = words.size();
        if (wordsCount <= 0) {
            return {};
        }

        // 0. Clear the previous cache.
        characterPositionsInBoardCache.clear();

        // 1. Find all starting matches.
        bool shouldUseCacheToFindStartingPoints = false;
        if (wordsCount > 50) {
            shouldUseCacheToFindStartingPoints = true;
        }

        vector<vector<pair<int, int>>> wordsStartingPoints;

        for (const auto& aWord: words) {
            char firstCharacter = aWord.at(0);

            vector<pair<int, int>> matchingPositions;
            if (shouldUseCacheToFindStartingPoints) {
                matchingPositions = findCharacterPositionsInBoard(board, firstCharacter);
            } else {
                matchingPositions = findCharacterPositionsInBoardWithCache(board, firstCharacter);
            }

            wordsStartingPoints.push_back(matchingPositions);
        }

        // 2. Start from the starting matches.
        vector<string> returnValue = {};

        for (int i = 0; i < words.size(); i += 1) {
            auto currentStartingPoints = wordsStartingPoints.at(i);
            if (currentStartingPoints.size() == 0) {
                continue;
            }
            
            string currentWord = words.at(i);
            for (const auto& aStartingPoint: currentStartingPoints) {
                if (findWordRecursively(board, currentWord.substr(1), { make_pair(aStartingPoint.first, aStartingPoint.second) })) {
                    returnValue.push_back(currentWord);
                    break;
                }
            }
        }

        return returnValue;
    }
};


// MARK: 3. Improved 2. Set board value to ' ' temporarily.
// Runtime: 1456 ms, faster than 5.05% of C++ online submissions for Word Search II. 😂😂😂...
// Memory Usage: 41.4 MB, less than 25.00% of C++ online submissions for Word Search II.
class SolutionOld3 {
private:
    vector<pair<int, int>> findCharacterPositionsInBoard(const vector<vector<char>>& board, char characterToFind) {
        vector<pair<int, int>> returnValue;

        for (int i = 0; i < board.size(); i += 1) {
            auto currentRow = board.at(i);
            for (int j = 0; j < currentRow.size(); j += 1) {
                char currentCharacter = currentRow.at(j);
                if (currentCharacter == characterToFind) {
                    returnValue.push_back(make_pair(i, j));
                }
            }
        }

        return returnValue;
    }

    vector<pair<int, int>> findCharacterPositionsInBoardWithCache(const vector<vector<char>>& board, char characterToFind, unordered_map<char, vector<pair<int, int>>>& characterPositionsInBoardCache) {
        if (characterPositionsInBoardCache.find(characterToFind) != characterPositionsInBoardCache.end()) {
            // The current character has been cached.
            return characterPositionsInBoardCache.at(characterToFind);
        }

        vector<pair<int, int>> returnValue;

        for (int i = 0; i < board.size(); i += 1) {
            auto currentRow = board.at(i);
            for (int j = 0; j < currentRow.size(); j += 1) {
                char currentCharacter = currentRow.at(j);
                if (currentCharacter == characterToFind) {
                    returnValue.push_back(make_pair(i, j));
                }
            }
        }

        characterPositionsInBoardCache.emplace(characterToFind, returnValue);

        return returnValue;
    }

    bool findWordRecursively(vector<vector<char>>& board, string wordToFind, int startX, int startY) {
        auto charactersCount = wordToFind.size();
        if (charactersCount == 0) {
            return true;
        }

        char firstCharacter = wordToFind.at(0);

        // 1. Right.
        int rightX = startX + 1;
        if (rightX < board.size()) {
            if (firstCharacter == board.at(rightX).at(startY)) {
                if (charactersCount == 1) {
                    return true;
                } else {
                    board.at(rightX).at(startY) = ' ';    // Set that location to an empty character to avoid revisiting it.
                    bool recursionResult = findWordRecursively(board, wordToFind.substr(1), rightX, startY);
                    board.at(rightX).at(startY) = firstCharacter;
                    if (recursionResult) {
                        return true;
                    }
                }
            }
        }

        // 2. Left.
        int leftX = startX - 1;
        if (leftX >= 0) {
            if (firstCharacter == board.at(leftX).at(startY)) {
                if (charactersCount == 1) {
                    return true;
                } else {
                    board.at(leftX).at(startY) = ' ';
                    bool recursionResult = findWordRecursively(board, wordToFind.substr(1), leftX, startY);
                    board.at(leftX).at(startY) = firstCharacter;
                    if (recursionResult) {
                        return true;
                    }
                }
            }
        }

        // 3. Up.
        int upY = startY + 1;
        if (upY < board.at(0).size()) {
            if (firstCharacter == board.at(startX).at(upY)) {
                if (charactersCount == 1) {
                    return true;
                } else {
                    board.at(startX).at(upY) = ' ';
                    bool recursionResult = findWordRecursively(board, wordToFind.substr(1), startX, upY);
                    board.at(startX).at(upY) = firstCharacter;
                    if (recursionResult) {
                        return true;
                    }
                }
            } 
        }

        // 4. Down.
        int downY = startY - 1;
        if (downY >= 0) {
            if (firstCharacter == board.at(startX).at(downY)) {
                if (charactersCount == 1) {
                    return true;
                } else {
                    board.at(startX).at(downY) = ' ';
                    bool recursionResult = findWordRecursively(board, wordToFind.substr(1), startX, downY);
                    board.at(startX).at(downY) = firstCharacter;
                    if (recursionResult) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        auto wordsCount = words.size();
        if (wordsCount <= 0) {
            return {};
        }

        // 1. Should use cache to calculate character positions.
        unordered_map<char, vector<pair<int, int>>> characterPositionsInBoardCache;
        bool shouldUseCacheToFindStartingPoints = false;
        if (wordsCount > 50) {
            shouldUseCacheToFindStartingPoints = true;
        }

        //2. Find all starting matches.
        vector<vector<pair<int, int>>> wordsStartingPoints;

        for (const auto& aWord: words) {
            const char firstCharacter = aWord.at(0);

            vector<pair<int, int>> matchingPositions;
            if (shouldUseCacheToFindStartingPoints) {
                matchingPositions = findCharacterPositionsInBoard(board, firstCharacter);
            } else {
                matchingPositions = findCharacterPositionsInBoardWithCache(board, firstCharacter, characterPositionsInBoardCache);
            }

            wordsStartingPoints.push_back(matchingPositions);
        }

        // 3. Start from starting matches.
        vector<string> returnValue = {};

        for (int i = 0; i < words.size(); i += 1) {
            auto currentStartingPoints = wordsStartingPoints.at(i);
            if (currentStartingPoints.size() == 0) {
                continue;
            }
            
            string currentWord = words.at(i);
            for (const auto& aStartingPoint: currentStartingPoints) {
                int startX = aStartingPoint.first;
                int startY = aStartingPoint.second;
                
                const char currentBoardValue = board.at(startX).at(startY);
                board.at(startX).at(startY) = ' ';
                bool recursionResult = findWordRecursively(board, currentWord.substr(1), startX, startY);
                board.at(startX).at(startY) = currentBoardValue;
                
                if (recursionResult) {
                    returnValue.push_back(currentWord);
                    break;
                }
            }
        }

        return returnValue;
    }
};


// MARK: 4. Use a map to store all the connections.
// Unfinished.
class SolutionOld4 {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // 1. Boundary cases.
        auto wordsCount = words.size();
        if (wordsCount <= 0) {
            return {};
        }

        auto boardWidth = board.size();
        if (boardWidth <= 0) {
            return {};
        }
        auto boardHeight = board.at(0).size();
        if (boardHeight <= 0) {
            return {};
        }

        // 2. Initialize map.
        /// (start x, start y, end x, end y).
        unordered_map<string, vector<vector<int>>> boardLookUpCache;
        for (int x = 0; x < boardWidth; x += 1) {
            for (int y = 0; y < boardHeight; y += 1) {
                char currentCharacter = board.at(x).at(y);
                // Right.
                if (x < (boardWidth - 1)) {
                    char rightCharacter = board.at(x + 1).at(y);

                    // string possibleString1 = {rightCharacter, currentCharacter};
                    // auto iterator1 = boardLookUpCache.find(possibleString1);
                    // if (iterator1 == boardLookUpCache.end()) {
                    //     vector<vector<int>> currentVector = {{x + 1, y, x, y}};
                    //     boardLookUpCache.insert(make_pair(possibleString1, currentVector));
                    // } else {
                    //     iterator1->second.push_back({x + 1, y, x, y});
                    // }

                    string possibleString2 = {currentCharacter, rightCharacter};
                    auto iterator2 = boardLookUpCache.find(possibleString2);
                    if (iterator2 == boardLookUpCache.end()) {
                        vector<vector<int>> currentVector = {{x, y, x + 1, y}};
                        boardLookUpCache.insert(make_pair(possibleString2, currentVector));
                    } else {
                        iterator2->second.push_back({x, y, x + 1, y});
                    }
                }
                // Left.
                if (x > 0) {
                    char leftCharacter = board.at(x - 1).at(y);

                    // string possibleString1 = {leftCharacter, currentCharacter};
                    // auto iterator1 = boardLookUpCache.find(possibleString1);
                    // if (iterator1 == boardLookUpCache.end()) {
                    //     vector<vector<int>> currentVector = {{x - 1, y, x, y}};
                    //     boardLookUpCache.insert(make_pair(possibleString1, currentVector));
                    // } else {
                    //     iterator1->second.push_back({x - 1, y, x, y});
                    // }

                    string possibleString2 = {currentCharacter, leftCharacter};
                    auto iterator2 = boardLookUpCache.find(possibleString2);
                    if (iterator2 == boardLookUpCache.end()) {
                        vector<vector<int>> currentVector = {{x, y, x - 1, y}};
                        boardLookUpCache.insert(make_pair(possibleString2, currentVector));
                    } else {
                        iterator2->second.push_back({x, y, x - 1, y});
                    } 
                }
                // Up.
                if (y < (boardHeight - 1)) {
                    char upCharacter = board.at(x).at(y + 1);

                    // string possibleString1 = {upCharacter, currentCharacter};
                    // auto iterator1 = boardLookUpCache.find(possibleString1);
                    // if (iterator1 == boardLookUpCache.end()) {
                    //     vector<vector<int>> currentVector = {{x, y + 1, x, y}};
                    //     boardLookUpCache.insert(make_pair(possibleString1, currentVector));
                    // } else {
                    //     iterator1->second.push_back({x, y + 1, x, y});
                    // }

                    string possibleString2 = {currentCharacter, upCharacter};
                    auto iterator2 = boardLookUpCache.find(possibleString2);
                    if (iterator2 == boardLookUpCache.end()) {
                        vector<vector<int>> currentVector = {{x, y, x, y + 1}};
                        boardLookUpCache.insert(make_pair(possibleString2, currentVector));
                    } else {
                        iterator2->second.push_back({x, y, x, y + 1});
                    }
                }
                // Down.
                if (y > 0) {
                    char downCharacter = board.at(x).at(y - 1);

                    // string possibleString1 = {downCharacter, currentCharacter};
                    // auto iterator1 = boardLookUpCache.find(possibleString1);
                    // if (iterator1 == boardLookUpCache.end()) {
                    //     vector<vector<int>> currentVector = {{x, y - 1, x, y}};
                    //     boardLookUpCache.insert(make_pair(possibleString1, currentVector));
                    // } else {
                    //     iterator1->second.push_back({x, y - 1, x, y});
                    // }

                    string possibleString2 = {currentCharacter, downCharacter};
                    auto iterator2 = boardLookUpCache.find(possibleString2);
                    if (iterator2 == boardLookUpCache.end()) {
                        vector<vector<int>> currentVector = {{x, y, x, y - 1}};
                        boardLookUpCache.insert(make_pair(possibleString2, currentVector));
                    } else {
                        iterator2->second.push_back({x, y, x, y - 1});
                    }
                }
            }
        }

        // auto testResult1 = *(boardLookUpCache.find("hk"));
        // auto testResult2 = *(boardLookUpCache.find("ka"));

        //3. Find those words in the board cache.
        vector<string> returnValue;

        for (const string& aWord: words) {
            vector<pair<int, int>> traceInBoard;
            for (int i = 0; i < (aWord.size() - 1); i += 1) {
                string currentSubString = aWord.substr(i, 2);
                auto iterator = boardLookUpCache.find(currentSubString);
                if (iterator == boardLookUpCache.end()) {
                    break;
                }

                auto possibleLinksInBoard = iterator->second;
                for (const vector<int>& aPossibleLink: possibleLinksInBoard) {
                    
                }
            }
        }

        return returnValue;
    }
};


// Runtime: 52 ms, faster than 76.48% of C++ online submissions for Word Search II.
// Memory Usage: 38 MB, less than 25.00% of C++ online submissions for Word Search II.
#define CHILDREN_CANDIDATE_SIZE 26
class TrieNode {
public:
    vector<TrieNode*>* children;
    string* word;

    TrieNode() {
        children = new vector<TrieNode*> (CHILDREN_CANDIDATE_SIZE, nullptr);
        word = nullptr;
    }

    ~TrieNode() {
        delete children;
        delete word;
    }
};

class Solution {
public:
    void searchForWordInTrieRecursively(int x, int y, vector<vector<char>>& board, const size_t& boardWidth, const size_t& boardHeight, TrieNode* currentNode, vector<string>& returnValue) {
        char currentCharacterInBoard = board.at(x).at(y);
        if (currentCharacterInBoard == '.') {
            return;
        }

        int currentCharacterIndex = currentCharacterInBoard - 'a';

        TrieNode* nextNode = currentNode->children->at(currentCharacterIndex);
        if (nextNode == nullptr) {
            return;
        }
        if (nextNode->word != nullptr) {
            // Finds a word.
            returnValue.push_back(*(nextNode->word));
            nextNode->word = nullptr;    // No need to search for this word again.
        }

        board.at(x).at(y) = '.';    // Placeholder for visited characters.
        if (x > 0) {
            searchForWordInTrieRecursively(x - 1, y, board, boardWidth, boardHeight, nextNode, returnValue);
        }
        if (x < (boardWidth - 1)) {
            searchForWordInTrieRecursively(x + 1, y, board, boardWidth, boardHeight, nextNode, returnValue);
        }
        if (y > 0) {
            searchForWordInTrieRecursively(x, y - 1, board, boardWidth, boardHeight, nextNode, returnValue);
        }
        if (y < (boardHeight - 1)) {
            searchForWordInTrieRecursively(x, y + 1, board, boardWidth, boardHeight, nextNode, returnValue);
        }
        board.at(x).at(y) = currentCharacterInBoard;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // 1. Boundary cases.
        auto wordsCount = words.size();
        if (wordsCount <= 0) {
            return {};
        }

        auto boardWidth = board.size();
        if (boardWidth <= 0) {
            return {};
        }
        auto boardHeight = board.at(0).size();
        if (boardHeight <= 0) {
            return {};
        }

        // 2. Build trie.
        TrieNode* rootNode = new TrieNode();
        for (const string& aWord: words) {
            TrieNode* currentNode = rootNode;
            for (const char& aCharacter: aWord) {
                int characterIndex = aCharacter - 'a';
                if (currentNode->children->at(characterIndex) == nullptr) {
                    currentNode->children->at(characterIndex) = new TrieNode();
                }
                currentNode = currentNode->children->at(characterIndex);
            }
            currentNode->word = new string(aWord);
        }

        // 3. Search for each word.
        vector<string> returnValue;
        for (int x = 0; x < boardWidth; x += 1) {
            for (int y = 0; y < boardHeight; y += 1) {
                searchForWordInTrieRecursively(x, y, board, boardWidth, boardHeight, rootNode, returnValue);
            }
        }

        return returnValue;
    }
};


void test(vector<vector<char>>& board, vector<string>& words) {
    unique_ptr<Solution> solutionInstance (new Solution());
    auto results = solutionInstance->findWords(board, words);
    if (results.size() == 0) {
        cout << "No result!" << endl;
    } else {
        for (const auto& aResult: results) {
            cout << aResult << " ";
        }
        cout << endl;
    }
    
//    unique_ptr<SolutionOld2> solutionInstance2 (new SolutionOld2());
//    auto results2 = solutionInstance2->findWords(board, words);
//    if (results2 != results) {
//        cout << "Contradictory results! Expected: ";
//        for (const auto& aResult: results2) {
//            cout << aResult << " ";
//        }
//        cout << endl;
//    }
}

int main() {
    vector<vector<char>> board1 = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };
    vector<string> words1 = {"oath","pea","eat","rain"};
    test(board1, words1);    // "eat","oath"
    
    vector<vector<char>> board2 = {
        {{"a","a"}}
    };
    vector<string> words2 = {"aaa"};
    test(board2, words2);    // Empty result.

    vector<vector<char>> board3 = {
        {'a','a','a','a'},{'a','a','a','a'},{'a','a','a','a'},{'a','a','a','a'},{'b','c','d','e'},{'f','g','h','i'},{'j','k','l','m'},{'n','o','p','q'},{'r','s','t','u'},{'v','w','x','y'},{'z','z','z','z'}
    };
    vector<string> words3 = {"aaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaab","aaaaaaaaaaaaaaac","aaaaaaaaaaaaaaad","aaaaaaaaaaaaaaae","aaaaaaaaaaaaaaaf","aaaaaaaaaaaaaaag","aaaaaaaaaaaaaaah","aaaaaaaaaaaaaaai","aaaaaaaaaaaaaaaj","aaaaaaaaaaaaaaak","aaaaaaaaaaaaaaal","aaaaaaaaaaaaaaam","aaaaaaaaaaaaaaan","aaaaaaaaaaaaaaao","aaaaaaaaaaaaaaap","aaaaaaaaaaaaaaaq","aaaaaaaaaaaaaaar","aaaaaaaaaaaaaaas","aaaaaaaaaaaaaaat","aaaaaaaaaaaaaaau","aaaaaaaaaaaaaaav","aaaaaaaaaaaaaaaw","aaaaaaaaaaaaaaax","aaaaaaaaaaaaaaay","aaaaaaaaaaaaaaaz","aaaaaaaaaaaaaaba","aaaaaaaaaaaaaabb","aaaaaaaaaaaaaabc","aaaaaaaaaaaaaabd","aaaaaaaaaaaaaabe","aaaaaaaaaaaaaabf","aaaaaaaaaaaaaabg","aaaaaaaaaaaaaabh","aaaaaaaaaaaaaabi","aaaaaaaaaaaaaabj","aaaaaaaaaaaaaabk","aaaaaaaaaaaaaabl","aaaaaaaaaaaaaabm","aaaaaaaaaaaaaabn","aaaaaaaaaaaaaabo","aaaaaaaaaaaaaabp","aaaaaaaaaaaaaabq","aaaaaaaaaaaaaabr","aaaaaaaaaaaaaabs","aaaaaaaaaaaaaabt","aaaaaaaaaaaaaabu","aaaaaaaaaaaaaabv","aaaaaaaaaaaaaabw","aaaaaaaaaaaaaabx","aaaaaaaaaaaaaaby","aaaaaaaaaaaaaabz","aaaaaaaaaaaaaaca","aaaaaaaaaaaaaacb","aaaaaaaaaaaaaacc","aaaaaaaaaaaaaacd","aaaaaaaaaaaaaace","aaaaaaaaaaaaaacf","aaaaaaaaaaaaaacg","aaaaaaaaaaaaaach","aaaaaaaaaaaaaaci","aaaaaaaaaaaaaacj","aaaaaaaaaaaaaack","aaaaaaaaaaaaaacl","aaaaaaaaaaaaaacm","aaaaaaaaaaaaaacn","aaaaaaaaaaaaaaco","aaaaaaaaaaaaaacp","aaaaaaaaaaaaaacq","aaaaaaaaaaaaaacr","aaaaaaaaaaaaaacs","aaaaaaaaaaaaaact","aaaaaaaaaaaaaacu","aaaaaaaaaaaaaacv","aaaaaaaaaaaaaacw","aaaaaaaaaaaaaacx","aaaaaaaaaaaaaacy","aaaaaaaaaaaaaacz","aaaaaaaaaaaaaada","aaaaaaaaaaaaaadb","aaaaaaaaaaaaaadc","aaaaaaaaaaaaaadd","aaaaaaaaaaaaaade","aaaaaaaaaaaaaadf","aaaaaaaaaaaaaadg","aaaaaaaaaaaaaadh","aaaaaaaaaaaaaadi","aaaaaaaaaaaaaadj","aaaaaaaaaaaaaadk","aaaaaaaaaaaaaadl","aaaaaaaaaaaaaadm","aaaaaaaaaaaaaadn","aaaaaaaaaaaaaado","aaaaaaaaaaaaaadp","aaaaaaaaaaaaaadq","aaaaaaaaaaaaaadr","aaaaaaaaaaaaaads","aaaaaaaaaaaaaadt","aaaaaaaaaaaaaadu","aaaaaaaaaaaaaadv","aaaaaaaaaaaaaadw","aaaaaaaaaaaaaadx","aaaaaaaaaaaaaady","aaaaaaaaaaaaaadz","aaaaaaaaaaaaaaea","aaaaaaaaaaaaaaeb","aaaaaaaaaaaaaaec","aaaaaaaaaaaaaaed","aaaaaaaaaaaaaaee","aaaaaaaaaaaaaaef","aaaaaaaaaaaaaaeg","aaaaaaaaaaaaaaeh","aaaaaaaaaaaaaaei","aaaaaaaaaaaaaaej","aaaaaaaaaaaaaaek","aaaaaaaaaaaaaael","aaaaaaaaaaaaaaem","aaaaaaaaaaaaaaen","aaaaaaaaaaaaaaeo","aaaaaaaaaaaaaaep","aaaaaaaaaaaaaaeq","aaaaaaaaaaaaaaer","aaaaaaaaaaaaaaes","aaaaaaaaaaaaaaet","aaaaaaaaaaaaaaeu","aaaaaaaaaaaaaaev","aaaaaaaaaaaaaaew","aaaaaaaaaaaaaaex","aaaaaaaaaaaaaaey","aaaaaaaaaaaaaaez","aaaaaaaaaaaaaafa","aaaaaaaaaaaaaafb","aaaaaaaaaaaaaafc","aaaaaaaaaaaaaafd","aaaaaaaaaaaaaafe","aaaaaaaaaaaaaaff","aaaaaaaaaaaaaafg","aaaaaaaaaaaaaafh","aaaaaaaaaaaaaafi","aaaaaaaaaaaaaafj","aaaaaaaaaaaaaafk","aaaaaaaaaaaaaafl","aaaaaaaaaaaaaafm","aaaaaaaaaaaaaafn","aaaaaaaaaaaaaafo","aaaaaaaaaaaaaafp","aaaaaaaaaaaaaafq","aaaaaaaaaaaaaafr","aaaaaaaaaaaaaafs","aaaaaaaaaaaaaaft","aaaaaaaaaaaaaafu","aaaaaaaaaaaaaafv","aaaaaaaaaaaaaafw","aaaaaaaaaaaaaafx","aaaaaaaaaaaaaafy","aaaaaaaaaaaaaafz","aaaaaaaaaaaaaaga","aaaaaaaaaaaaaagb","aaaaaaaaaaaaaagc","aaaaaaaaaaaaaagd","aaaaaaaaaaaaaage","aaaaaaaaaaaaaagf","aaaaaaaaaaaaaagg","aaaaaaaaaaaaaagh","aaaaaaaaaaaaaagi","aaaaaaaaaaaaaagj","aaaaaaaaaaaaaagk","aaaaaaaaaaaaaagl","aaaaaaaaaaaaaagm","aaaaaaaaaaaaaagn","aaaaaaaaaaaaaago","aaaaaaaaaaaaaagp","aaaaaaaaaaaaaagq","aaaaaaaaaaaaaagr","aaaaaaaaaaaaaags","aaaaaaaaaaaaaagt","aaaaaaaaaaaaaagu","aaaaaaaaaaaaaagv","aaaaaaaaaaaaaagw","aaaaaaaaaaaaaagx","aaaaaaaaaaaaaagy","aaaaaaaaaaaaaagz","aaaaaaaaaaaaaaha","aaaaaaaaaaaaaahb","aaaaaaaaaaaaaahc","aaaaaaaaaaaaaahd","aaaaaaaaaaaaaahe","aaaaaaaaaaaaaahf","aaaaaaaaaaaaaahg","aaaaaaaaaaaaaahh","aaaaaaaaaaaaaahi","aaaaaaaaaaaaaahj","aaaaaaaaaaaaaahk","aaaaaaaaaaaaaahl","aaaaaaaaaaaaaahm","aaaaaaaaaaaaaahn","aaaaaaaaaaaaaaho","aaaaaaaaaaaaaahp","aaaaaaaaaaaaaahq","aaaaaaaaaaaaaahr","aaaaaaaaaaaaaahs","aaaaaaaaaaaaaaht","aaaaaaaaaaaaaahu","aaaaaaaaaaaaaahv","aaaaaaaaaaaaaahw","aaaaaaaaaaaaaahx","aaaaaaaaaaaaaahy","aaaaaaaaaaaaaahz","aaaaaaaaaaaaaaia","aaaaaaaaaaaaaaib","aaaaaaaaaaaaaaic","aaaaaaaaaaaaaaid","aaaaaaaaaaaaaaie","aaaaaaaaaaaaaaif","aaaaaaaaaaaaaaig","aaaaaaaaaaaaaaih","aaaaaaaaaaaaaaii","aaaaaaaaaaaaaaij","aaaaaaaaaaaaaaik","aaaaaaaaaaaaaail","aaaaaaaaaaaaaaim","aaaaaaaaaaaaaain","aaaaaaaaaaaaaaio","aaaaaaaaaaaaaaip","aaaaaaaaaaaaaaiq","aaaaaaaaaaaaaair","aaaaaaaaaaaaaais","aaaaaaaaaaaaaait","aaaaaaaaaaaaaaiu","aaaaaaaaaaaaaaiv","aaaaaaaaaaaaaaiw","aaaaaaaaaaaaaaix","aaaaaaaaaaaaaaiy","aaaaaaaaaaaaaaiz","aaaaaaaaaaaaaaja","aaaaaaaaaaaaaajb","aaaaaaaaaaaaaajc","aaaaaaaaaaaaaajd","aaaaaaaaaaaaaaje","aaaaaaaaaaaaaajf","aaaaaaaaaaaaaajg","aaaaaaaaaaaaaajh","aaaaaaaaaaaaaaji","aaaaaaaaaaaaaajj","aaaaaaaaaaaaaajk","aaaaaaaaaaaaaajl","aaaaaaaaaaaaaajm","aaaaaaaaaaaaaajn","aaaaaaaaaaaaaajo","aaaaaaaaaaaaaajp","aaaaaaaaaaaaaajq","aaaaaaaaaaaaaajr","aaaaaaaaaaaaaajs","aaaaaaaaaaaaaajt","aaaaaaaaaaaaaaju","aaaaaaaaaaaaaajv","aaaaaaaaaaaaaajw","aaaaaaaaaaaaaajx","aaaaaaaaaaaaaajy","aaaaaaaaaaaaaajz","aaaaaaaaaaaaaaka","aaaaaaaaaaaaaakb","aaaaaaaaaaaaaakc","aaaaaaaaaaaaaakd","aaaaaaaaaaaaaake","aaaaaaaaaaaaaakf","aaaaaaaaaaaaaakg","aaaaaaaaaaaaaakh","aaaaaaaaaaaaaaki","aaaaaaaaaaaaaakj","aaaaaaaaaaaaaakk","aaaaaaaaaaaaaakl","aaaaaaaaaaaaaakm","aaaaaaaaaaaaaakn","aaaaaaaaaaaaaako","aaaaaaaaaaaaaakp","aaaaaaaaaaaaaakq","aaaaaaaaaaaaaakr","aaaaaaaaaaaaaaks","aaaaaaaaaaaaaakt","aaaaaaaaaaaaaaku","aaaaaaaaaaaaaakv","aaaaaaaaaaaaaakw","aaaaaaaaaaaaaakx","aaaaaaaaaaaaaaky","aaaaaaaaaaaaaakz","aaaaaaaaaaaaaala","aaaaaaaaaaaaaalb","aaaaaaaaaaaaaalc","aaaaaaaaaaaaaald","aaaaaaaaaaaaaale","aaaaaaaaaaaaaalf","aaaaaaaaaaaaaalg","aaaaaaaaaaaaaalh","aaaaaaaaaaaaaali","aaaaaaaaaaaaaalj","aaaaaaaaaaaaaalk","aaaaaaaaaaaaaall","aaaaaaaaaaaaaalm","aaaaaaaaaaaaaaln","aaaaaaaaaaaaaalo","aaaaaaaaaaaaaalp","aaaaaaaaaaaaaalq","aaaaaaaaaaaaaalr","aaaaaaaaaaaaaals","aaaaaaaaaaaaaalt","aaaaaaaaaaaaaalu","aaaaaaaaaaaaaalv","aaaaaaaaaaaaaalw","aaaaaaaaaaaaaalx","aaaaaaaaaaaaaaly","aaaaaaaaaaaaaalz","aaaaaaaaaaaaaama","aaaaaaaaaaaaaamb","aaaaaaaaaaaaaamc","aaaaaaaaaaaaaamd","aaaaaaaaaaaaaame","aaaaaaaaaaaaaamf","aaaaaaaaaaaaaamg","aaaaaaaaaaaaaamh","aaaaaaaaaaaaaami","aaaaaaaaaaaaaamj","aaaaaaaaaaaaaamk","aaaaaaaaaaaaaaml","aaaaaaaaaaaaaamm","aaaaaaaaaaaaaamn","aaaaaaaaaaaaaamo","aaaaaaaaaaaaaamp","aaaaaaaaaaaaaamq","aaaaaaaaaaaaaamr","aaaaaaaaaaaaaams","aaaaaaaaaaaaaamt","aaaaaaaaaaaaaamu","aaaaaaaaaaaaaamv","aaaaaaaaaaaaaamw","aaaaaaaaaaaaaamx","aaaaaaaaaaaaaamy","aaaaaaaaaaaaaamz","aaaaaaaaaaaaaana","aaaaaaaaaaaaaanb","aaaaaaaaaaaaaanc","aaaaaaaaaaaaaand","aaaaaaaaaaaaaane","aaaaaaaaaaaaaanf","aaaaaaaaaaaaaang","aaaaaaaaaaaaaanh","aaaaaaaaaaaaaani","aaaaaaaaaaaaaanj","aaaaaaaaaaaaaank","aaaaaaaaaaaaaanl","aaaaaaaaaaaaaanm","aaaaaaaaaaaaaann","aaaaaaaaaaaaaano","aaaaaaaaaaaaaanp","aaaaaaaaaaaaaanq","aaaaaaaaaaaaaanr","aaaaaaaaaaaaaans","aaaaaaaaaaaaaant","aaaaaaaaaaaaaanu","aaaaaaaaaaaaaanv","aaaaaaaaaaaaaanw","aaaaaaaaaaaaaanx","aaaaaaaaaaaaaany","aaaaaaaaaaaaaanz","aaaaaaaaaaaaaaoa","aaaaaaaaaaaaaaob","aaaaaaaaaaaaaaoc","aaaaaaaaaaaaaaod","aaaaaaaaaaaaaaoe","aaaaaaaaaaaaaaof","aaaaaaaaaaaaaaog","aaaaaaaaaaaaaaoh","aaaaaaaaaaaaaaoi","aaaaaaaaaaaaaaoj","aaaaaaaaaaaaaaok","aaaaaaaaaaaaaaol","aaaaaaaaaaaaaaom","aaaaaaaaaaaaaaon","aaaaaaaaaaaaaaoo","aaaaaaaaaaaaaaop","aaaaaaaaaaaaaaoq","aaaaaaaaaaaaaaor","aaaaaaaaaaaaaaos","aaaaaaaaaaaaaaot","aaaaaaaaaaaaaaou","aaaaaaaaaaaaaaov","aaaaaaaaaaaaaaow","aaaaaaaaaaaaaaox","aaaaaaaaaaaaaaoy","aaaaaaaaaaaaaaoz","aaaaaaaaaaaaaapa","aaaaaaaaaaaaaapb","aaaaaaaaaaaaaapc","aaaaaaaaaaaaaapd","aaaaaaaaaaaaaape","aaaaaaaaaaaaaapf","aaaaaaaaaaaaaapg","aaaaaaaaaaaaaaph","aaaaaaaaaaaaaapi","aaaaaaaaaaaaaapj","aaaaaaaaaaaaaapk","aaaaaaaaaaaaaapl","aaaaaaaaaaaaaapm","aaaaaaaaaaaaaapn","aaaaaaaaaaaaaapo","aaaaaaaaaaaaaapp","aaaaaaaaaaaaaapq","aaaaaaaaaaaaaapr","aaaaaaaaaaaaaaps","aaaaaaaaaaaaaapt","aaaaaaaaaaaaaapu","aaaaaaaaaaaaaapv","aaaaaaaaaaaaaapw","aaaaaaaaaaaaaapx","aaaaaaaaaaaaaapy","aaaaaaaaaaaaaapz","aaaaaaaaaaaaaaqa","aaaaaaaaaaaaaaqb","aaaaaaaaaaaaaaqc","aaaaaaaaaaaaaaqd","aaaaaaaaaaaaaaqe","aaaaaaaaaaaaaaqf","aaaaaaaaaaaaaaqg","aaaaaaaaaaaaaaqh","aaaaaaaaaaaaaaqi","aaaaaaaaaaaaaaqj","aaaaaaaaaaaaaaqk","aaaaaaaaaaaaaaql","aaaaaaaaaaaaaaqm","aaaaaaaaaaaaaaqn","aaaaaaaaaaaaaaqo","aaaaaaaaaaaaaaqp","aaaaaaaaaaaaaaqq","aaaaaaaaaaaaaaqr","aaaaaaaaaaaaaaqs","aaaaaaaaaaaaaaqt","aaaaaaaaaaaaaaqu","aaaaaaaaaaaaaaqv","aaaaaaaaaaaaaaqw","aaaaaaaaaaaaaaqx","aaaaaaaaaaaaaaqy","aaaaaaaaaaaaaaqz","aaaaaaaaaaaaaara","aaaaaaaaaaaaaarb","aaaaaaaaaaaaaarc","aaaaaaaaaaaaaard","aaaaaaaaaaaaaare","aaaaaaaaaaaaaarf","aaaaaaaaaaaaaarg","aaaaaaaaaaaaaarh","aaaaaaaaaaaaaari","aaaaaaaaaaaaaarj","aaaaaaaaaaaaaark","aaaaaaaaaaaaaarl","aaaaaaaaaaaaaarm","aaaaaaaaaaaaaarn","aaaaaaaaaaaaaaro","aaaaaaaaaaaaaarp","aaaaaaaaaaaaaarq","aaaaaaaaaaaaaarr","aaaaaaaaaaaaaars","aaaaaaaaaaaaaart","aaaaaaaaaaaaaaru","aaaaaaaaaaaaaarv","aaaaaaaaaaaaaarw","aaaaaaaaaaaaaarx","aaaaaaaaaaaaaary","aaaaaaaaaaaaaarz","aaaaaaaaaaaaaasa","aaaaaaaaaaaaaasb","aaaaaaaaaaaaaasc","aaaaaaaaaaaaaasd","aaaaaaaaaaaaaase","aaaaaaaaaaaaaasf","aaaaaaaaaaaaaasg","aaaaaaaaaaaaaash","aaaaaaaaaaaaaasi","aaaaaaaaaaaaaasj","aaaaaaaaaaaaaask","aaaaaaaaaaaaaasl","aaaaaaaaaaaaaasm","aaaaaaaaaaaaaasn","aaaaaaaaaaaaaaso","aaaaaaaaaaaaaasp","aaaaaaaaaaaaaasq","aaaaaaaaaaaaaasr","aaaaaaaaaaaaaass","aaaaaaaaaaaaaast","aaaaaaaaaaaaaasu","aaaaaaaaaaaaaasv","aaaaaaaaaaaaaasw","aaaaaaaaaaaaaasx","aaaaaaaaaaaaaasy","aaaaaaaaaaaaaasz","aaaaaaaaaaaaaata","aaaaaaaaaaaaaatb","aaaaaaaaaaaaaatc","aaaaaaaaaaaaaatd","aaaaaaaaaaaaaate","aaaaaaaaaaaaaatf","aaaaaaaaaaaaaatg","aaaaaaaaaaaaaath","aaaaaaaaaaaaaati","aaaaaaaaaaaaaatj","aaaaaaaaaaaaaatk","aaaaaaaaaaaaaatl","aaaaaaaaaaaaaatm","aaaaaaaaaaaaaatn","aaaaaaaaaaaaaato","aaaaaaaaaaaaaatp","aaaaaaaaaaaaaatq","aaaaaaaaaaaaaatr","aaaaaaaaaaaaaats","aaaaaaaaaaaaaatt","aaaaaaaaaaaaaatu","aaaaaaaaaaaaaatv","aaaaaaaaaaaaaatw","aaaaaaaaaaaaaatx","aaaaaaaaaaaaaaty","aaaaaaaaaaaaaatz","aaaaaaaaaaaaaaua","aaaaaaaaaaaaaaub","aaaaaaaaaaaaaauc","aaaaaaaaaaaaaaud","aaaaaaaaaaaaaaue","aaaaaaaaaaaaaauf","aaaaaaaaaaaaaaug","aaaaaaaaaaaaaauh","aaaaaaaaaaaaaaui","aaaaaaaaaaaaaauj","aaaaaaaaaaaaaauk","aaaaaaaaaaaaaaul","aaaaaaaaaaaaaaum","aaaaaaaaaaaaaaun","aaaaaaaaaaaaaauo","aaaaaaaaaaaaaaup","aaaaaaaaaaaaaauq","aaaaaaaaaaaaaaur","aaaaaaaaaaaaaaus","aaaaaaaaaaaaaaut","aaaaaaaaaaaaaauu","aaaaaaaaaaaaaauv","aaaaaaaaaaaaaauw","aaaaaaaaaaaaaaux","aaaaaaaaaaaaaauy","aaaaaaaaaaaaaauz","aaaaaaaaaaaaaava","aaaaaaaaaaaaaavb","aaaaaaaaaaaaaavc","aaaaaaaaaaaaaavd","aaaaaaaaaaaaaave","aaaaaaaaaaaaaavf","aaaaaaaaaaaaaavg","aaaaaaaaaaaaaavh","aaaaaaaaaaaaaavi","aaaaaaaaaaaaaavj","aaaaaaaaaaaaaavk","aaaaaaaaaaaaaavl","aaaaaaaaaaaaaavm","aaaaaaaaaaaaaavn","aaaaaaaaaaaaaavo","aaaaaaaaaaaaaavp","aaaaaaaaaaaaaavq","aaaaaaaaaaaaaavr","aaaaaaaaaaaaaavs","aaaaaaaaaaaaaavt","aaaaaaaaaaaaaavu","aaaaaaaaaaaaaavv","aaaaaaaaaaaaaavw","aaaaaaaaaaaaaavx","aaaaaaaaaaaaaavy","aaaaaaaaaaaaaavz","aaaaaaaaaaaaaawa","aaaaaaaaaaaaaawb","aaaaaaaaaaaaaawc","aaaaaaaaaaaaaawd","aaaaaaaaaaaaaawe","aaaaaaaaaaaaaawf","aaaaaaaaaaaaaawg","aaaaaaaaaaaaaawh","aaaaaaaaaaaaaawi","aaaaaaaaaaaaaawj","aaaaaaaaaaaaaawk","aaaaaaaaaaaaaawl","aaaaaaaaaaaaaawm","aaaaaaaaaaaaaawn","aaaaaaaaaaaaaawo","aaaaaaaaaaaaaawp","aaaaaaaaaaaaaawq","aaaaaaaaaaaaaawr","aaaaaaaaaaaaaaws","aaaaaaaaaaaaaawt","aaaaaaaaaaaaaawu","aaaaaaaaaaaaaawv","aaaaaaaaaaaaaaww","aaaaaaaaaaaaaawx","aaaaaaaaaaaaaawy","aaaaaaaaaaaaaawz","aaaaaaaaaaaaaaxa","aaaaaaaaaaaaaaxb","aaaaaaaaaaaaaaxc","aaaaaaaaaaaaaaxd","aaaaaaaaaaaaaaxe","aaaaaaaaaaaaaaxf","aaaaaaaaaaaaaaxg","aaaaaaaaaaaaaaxh","aaaaaaaaaaaaaaxi","aaaaaaaaaaaaaaxj","aaaaaaaaaaaaaaxk","aaaaaaaaaaaaaaxl","aaaaaaaaaaaaaaxm","aaaaaaaaaaaaaaxn","aaaaaaaaaaaaaaxo","aaaaaaaaaaaaaaxp","aaaaaaaaaaaaaaxq","aaaaaaaaaaaaaaxr","aaaaaaaaaaaaaaxs","aaaaaaaaaaaaaaxt","aaaaaaaaaaaaaaxu","aaaaaaaaaaaaaaxv","aaaaaaaaaaaaaaxw","aaaaaaaaaaaaaaxx","aaaaaaaaaaaaaaxy","aaaaaaaaaaaaaaxz","aaaaaaaaaaaaaaya","aaaaaaaaaaaaaayb","aaaaaaaaaaaaaayc","aaaaaaaaaaaaaayd","aaaaaaaaaaaaaaye","aaaaaaaaaaaaaayf","aaaaaaaaaaaaaayg","aaaaaaaaaaaaaayh","aaaaaaaaaaaaaayi","aaaaaaaaaaaaaayj","aaaaaaaaaaaaaayk","aaaaaaaaaaaaaayl","aaaaaaaaaaaaaaym","aaaaaaaaaaaaaayn","aaaaaaaaaaaaaayo","aaaaaaaaaaaaaayp","aaaaaaaaaaaaaayq","aaaaaaaaaaaaaayr","aaaaaaaaaaaaaays","aaaaaaaaaaaaaayt","aaaaaaaaaaaaaayu","aaaaaaaaaaaaaayv","aaaaaaaaaaaaaayw","aaaaaaaaaaaaaayx","aaaaaaaaaaaaaayy","aaaaaaaaaaaaaayz","aaaaaaaaaaaaaaza","aaaaaaaaaaaaaazb","aaaaaaaaaaaaaazc","aaaaaaaaaaaaaazd","aaaaaaaaaaaaaaze","aaaaaaaaaaaaaazf","aaaaaaaaaaaaaazg","aaaaaaaaaaaaaazh","aaaaaaaaaaaaaazi","aaaaaaaaaaaaaazj","aaaaaaaaaaaaaazk","aaaaaaaaaaaaaazl","aaaaaaaaaaaaaazm","aaaaaaaaaaaaaazn","aaaaaaaaaaaaaazo","aaaaaaaaaaaaaazp","aaaaaaaaaaaaaazq","aaaaaaaaaaaaaazr","aaaaaaaaaaaaaazs","aaaaaaaaaaaaaazt","aaaaaaaaaaaaaazu","aaaaaaaaaaaaaazv","aaaaaaaaaaaaaazw","aaaaaaaaaaaaaazx","aaaaaaaaaaaaaazy","aaaaaaaaaaaaaazz"};
    test(board3, words3);

    vector<vector<char>> board4 = {{'a','b'},{'c','d'}};
    vector<string> words4 = {"ab","cb","ad","bd","ac","ca","da","bc","db","adcb","dabc","abb","acb"};
    test(board4, words4);    // Expected: ["ab","ac","bd","ca","db"]


    return 0;
}
