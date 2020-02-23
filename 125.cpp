/*
 * 125. Valid Palindrome
 * https://leetcode.com/problems/valid-palindrome/
 */

#include <iostream>
#include <string>


// Runtime: 8 ms, faster than 85.71% of C++ online submissions for Valid Palindrome.
// Memory Usage: 9.3 MB, less than 97.96% of C++ online submissions for Valid Palindrome.
class Solution {
public:
    bool isPalindrome(const std::string& s) {
        const auto len = s.size();
        if (len < 2) {
            return true;
        }

        size_t i1 = 0;
        size_t i2 = len - 1;

        while (i1 < i2) {
            while (true) {
                if (!isAlphanumeric(s.at(i1))) {
                    i1 += 1;
                } else {
                    break;
                }

                if (i1 >= i2) {
                    // All useless characters.
                    return true;
                }
            }

            while (true) {
                if (!isAlphanumeric(s.at(i2))) {
                    i2 -= 1;
                } else {
                    break;
                }

                if (i1 >= i2) {
                    // All useless characters.
                    return true;
                }
            }

            if (!isTheSameLetter(s.at(i1), s.at(i2))) {
                return false;
            }

            i1 += 1;
            i2 -= 1;
        }

        return true;
    }

    bool isAlphanumeric(const char& c) {
        return (
            (((c - 'a') >= 0) && (c - 'z' <= 0)) || 
            (((c - 'A') >= 0) && (c - 'Z' <= 0)) ||
            (((c - '0') >= 0) && ((c - '9') <= 0))
            );
    }

    bool isNumeric(const char& c) {
        return (((c - '0') >= 0) && ((c - '9') <= 0));
    }

    bool isTheSameLetter(const char& c1, const char& c2) {
        if (c1 == c2) {
            return true;
        } else {
            if (isNumeric(c1) || isNumeric(c2)) {
                return false;
            } else {
                return (((c1 - c2) == ('a' - 'A')) || ((c1 - c2) == ('A' - 'a')));
            }
        }
    }
};


void test(const std::string& s) {
    static auto solutionInstance = Solution();

    std::cout << s;
    bool result = solutionInstance.isPalindrome(s);
    if (result) {
        std::cout << " -> YES" << std::endl;
    } else {
        std::cout << " -> NO" << std::endl;
    }
}

int main() {
    // std::string testCase1 = "A man, a plan, a canal: Panama";
    // test(testCase1);    // true

    // std::string testCase2 = "race a car";
    // test(testCase2);    // false

    std::string testCase3 = "ab";
    test(testCase3);    // false

    std::string testCase4 = "0b";
    test(testCase4);    // false

    return 0;
}
