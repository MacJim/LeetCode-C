/*
 * 880. Decoded String at Index
 * https://leetcode.com/problems/decoded-string-at-index/
 */

#include <iostream>
#include <vector>
#include <string>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Failed recursion
class Solution1 {
private:
    char recursion(const std::string& s, int startIndex, int k, int currentLen) {
        int currentIndex = startIndex;

        while ((currentIndex < s.size()) && (s[currentIndex] > '9')) {
            currentIndex += 1;
            currentLen += 1;
        }

        if (k > currentLen) {
            int currentDigit = static_cast<int>(s[currentIndex] - '0');
            currentLen *= currentDigit;

            if (k <= currentLen) {
                // Long enough after the repetition.
            } else {
                // Not long enough even after the repetition.
                startIndex += 1;
                return recursion(s, startIndex, k, currentLen);
            }
        }

        if (k <= currentLen) {
            int delta = (currentLen - k);
            int index = currentIndex - delta;

            return s[index];
        } else {

        }

        return '\0';    // Unfinished.
    }

public:
    std::string decodeAtIndex(const std::string& s, int k) {
        return std::string(1, recursion(s, 0, k-1, 0));
    }
};


#pragma mark - 2. Calculate lengths progressively (revisit)
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Decoded String at Index.
// Memory Usage: 6 MB, less than 67.49% of C++ online submissions for Decoded String at Index.
class Solution {
private:
    /**
     * @param s
     * @param k 0-indexed
     * @return
     */
    char recursion(const std::string& s, int k) {
        int length = 0;
        for (int i = 0; i < s.size(); i += 1) {
            const char& c = s[i];

            if (c > '9') {
                // Character.
                if (length == k) {    // `length` is 1-indexed, while `k` is 0-indexed. Thus, compare before increasing `length`.
                    return c;
                }

                length += 1;
            } else {
                // Digit.
                const int digit = static_cast<int>(c - '0');
                const long long newLength = static_cast<long long>(length) * digit;    // This step can overflow if using an `int`.

                if (k < newLength) {    // Cannot equal because k is 0-indexed.
                    // k is caught by the current "repeat" digit.
                    k %= length;

                    // Just re-calculate the previous part using a smaller `k`.
                    // This is inefficient, but I don't want to bother.
                    return recursion(s, k);
                } else {
                    // k is equal or larger: Increase length normally.
                    length = static_cast<int>(newLength);
                }
            }
        }

        return '\0';    // Should never reach here.
    }

public:
    std::string decodeAtIndex(const std::string& s, int k) {
        k -= 1;    // k is 1-indexed.

        return std::string(1, recursion(s, k));
    }
};


void test(const std::string& s, const std::string& decodedString) {
    auto solutionInstance = Solution();

    bool isCorrect = true;
    for (int k = 0; k < decodedString.size(); k += 1) {
        auto result = solutionInstance.decodeAtIndex(s, k + 1);    // Note that `k` is 1-indexed.
        if (result != std::string(1, decodedString[k])) {
            isCorrect = false;
            std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << ", " << k << ": " << result << " (should be " << decodedString[k] << ")" << std::endl;
        }
    }

    if (isCorrect) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << std::endl;
    }
}


int main() {
//    test("czjkk9elaqwiz7s6kgvl4gjixan3ky7jfdg3kyop3husw3fm289thisef8blt7a7zr5v5lhxqpntenvxnmlq7l34ay3jaayikjps", 768077956);
    test("leet2code3", "leetleetcodeleetleetcodeleetleetcode");
    test("leet2code3test", "leetleetcodeleetleetcodeleetleetcodetest");
    test("ha22", "hahahaha");
    test("a2345", std::string(2 * 3 * 4 * 5, 'a'));

    return 0;
}
