/*
 * 187. Repeated DNA Sequences
 * https://leetcode.com/problems/repeated-dna-sequences/
 */

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <cmath>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Custom rolling hash
// Runtime: 44 ms, faster than 89.78% of C++ online submissions for Repeated DNA Sequences.
// Memory Usage: 15.5 MB, less than 92.47% of C++ online submissions for Repeated DNA Sequences.
/**
 * We only have 4 chars.
 * Thus, a collision-free hasher is possible.
 */
class Hasher {
private:
    int maxLength;

public:
    /**
     * Each character occupies 2 bits in `currentHash`.
     *
     * Max length 10 -> need 20 bits.
     */
    int currentHash;

public:
    Hasher(int maxLength): maxLength(maxLength), currentHash(0) {}

public:
    void updateCharacter(const char& c) {
        currentHash <<= 2;

        switch (c) {
            case 'A':
                currentHash += 3;
                break;
            case 'C':
                currentHash += 2;
                break;
            case 'G':
                currentHash += 1;
                break;
//            case 'T':
//                currentHash += 0;
//                break;
            default:
                break;
        }
    }

    void updateCharacter(const char& previousChar, const char& currentChar) {
        int previousCharHash = 0;
        switch (previousChar) {
            case 'A':
                previousCharHash = 3;
                break;
            case 'C':
                previousCharHash = 2;
                break;
            case 'G':
                previousCharHash = 1;
                break;
//            case 'T':
//                currentHash += 0;
//                break;
            default:
                break;
        }
        previousCharHash <<= ((maxLength - 1) * 2);
        currentHash -= previousCharHash;

        updateCharacter(currentChar);
    }
};


class Solution {
public:
    std::vector<std::string> findRepeatedDnaSequences(const std::string& s) {
        if (s.size() <= 10) {
            // Not enough characters. No duplicates.
            return {};
        }

        auto returnValue = std::unordered_set<std::string>();

        auto hashes = std::unordered_set<int>();    // We can also store sub-strings in this hash map. But IMO that is slower than storing the hashes.
        auto hasher = Hasher(10);

        for (size_t i = 0; i < 10; i += 1) {
            hasher.updateCharacter(s[i]);
        }
        hashes.insert(hasher.currentHash);

        for (size_t i = 10; i < s.size(); i += 1) {
            hasher.updateCharacter(s[i - 10], s[i]);
            if (hashes.count(hasher.currentHash)) {
                const auto subStr = s.substr(i - 9, 10);
                returnValue.insert(subStr);
            } else {
                hashes.insert(hasher.currentHash);
            }
        }

        return std::vector(returnValue.begin(), returnValue.end());
    }
};


void test(const std::string& s, const std::set<std::string>& expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.findRepeatedDnaSequences(s);
    auto resultSet = std::set(result.begin(), result.end());

    if (resultSet == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << ": " << resultSet << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << ": " << resultSet << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
//    auto hasher = Hasher(10);
//    for (int i = 0; i < 5; i += 1) {
//        hasher.updateCharacter('A');
//    }
//    for (int i = 0; i < 5; i += 1) {
//        hasher.updateCharacter('C');
//    }
//    std::cout << hasher.currentHash << std::endl;
//    for (int i = 0; i < 5; i += 1) {
//        hasher.updateCharacter('A', 'A');
//    }
//    for (int i = 0; i < 5; i += 1) {
//        hasher.updateCharacter('C', 'C');
//    }
//    std::cout << hasher.currentHash << std::endl;

    for (size_t len = 11; len < 100; len += 1) {
        auto testString = std::string(len, 'A');
        test(testString, {"AAAAAAAAAA"});
    }

    test("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT", {"AAAAACCCCC","CCCCCAAAAA"});
    test("GGAAAAACCCCCAAAAACCCCCCAAAAAGGGTTTGG", {"AAAAACCCCC","CCCCCAAAAA"});

    return 0;
}
