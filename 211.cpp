/*
 * 211. Design Add and Search Words Data Structure
 * https://leetcode.com/problems/design-add-and-search-words-data-structure/
 */

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <memory>


#pragma mark - 1. Trie + DFS
// Runtime: 164 ms, faster than 8.81% of C++ online submissions for Design Add and Search Words Data Structure.
// Memory Usage: 40.8 MB, less than 85.15% of C++ online submissions for Design Add and Search Words Data Structure.
class TrieNode {
public:
    bool isTerminal;    // Don't forget about this.
    std::unordered_map<char, TrieNode*> children;

public:
//    TrieNode(const char& value): value(value), children(std::unordered_map<char, TrieNode*>()) {};
    TrieNode(bool isTerminal): isTerminal(isTerminal), children(std::unordered_map<char, TrieNode*>()) {};
};


class WordDictionary {
private:
    TrieNode* root;

public:
    /** Initialize your data structure here. */
    WordDictionary(): root(new TrieNode(false)) {}

public:
    void addWord(const std::string& word) {
        auto currentNode = root;
        for (const char& c: word) {
            if (currentNode->children.count(c)) {
                currentNode = currentNode->children[c];
            } else {
                auto child = new TrieNode(false);
                currentNode->children[c] = child;
                currentNode = child;
            }
        }

        currentNode->isTerminal = true;    // The final node.
    }

private:
    bool searchRecursively(const std::string& word, const size_t startIndex, TrieNode* currentNode) {
        if (startIndex == word.size()) {
            if (currentNode && currentNode->isTerminal) {
                return true;
            } else {
                return false;
            }
        }

        if (word[startIndex] == '.') {
            // Search all sub-trees.
            for (auto [c, child]: currentNode->children) {
                const bool subResult = searchRecursively(word, startIndex + 1, child);
                if (subResult) {
                    return true;
                }
            }

            return false;
        } else if (currentNode->children.count(word[startIndex])) {
            // Found the current character in `children`.
            auto child = currentNode->children[word[startIndex]];
            const bool subResult = searchRecursively(word, startIndex + 1, child);
            return subResult;
        } else {
            return false;
        }
    }

public:
    bool search(const std::string& word) {
        const auto result = searchRecursively(word, 0, root);

        return result;
    }
};


//void test(const std::vector<int>& nums, const int expectedResult) {
//    static auto solutionInstance = Solution();
//
//    auto numsCopy = nums;
//    auto result = solutionInstance.findMin(numsCopy);
//
//    if (result == expectedResult) {
//        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
//    } else {
//        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
//    }
//}


int main() {
    auto wd1 = std::make_unique<WordDictionary>();
    wd1->addWord("bad");
    wd1->addWord("dad");
    wd1->addWord("mad");
    wd1->addWord("pad");
    assert(wd1->search("bad"));
    assert(wd1->search(".ad"));
    assert(wd1->search("b.."));
    assert(wd1->search("..d"));
    assert(!wd1->search("bab"));
    assert(!wd1->search(".ab"));

    auto wd2 = std::make_unique<WordDictionary>();
    wd2->addWord("at");
    wd2->addWord("and");
    wd2->addWord("an");
    wd2->addWord("add");
    assert(!wd2->search("a"));
    assert(!wd2->search(".at"));
    wd2->addWord("bat");
    assert(wd2->search(".at"));
    assert(wd2->search("an."));

    return 0;
}
