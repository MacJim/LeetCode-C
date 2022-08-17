/**
 * 151. Reverse Words in a String
 * https://leetcode.com/problems/reverse-words-in-a-string/
 */
#include <iostream>
#include <string>


#pragma mark - 1. Copy from back to front
// Runtime: 2 ms, faster than 94.88% of C++ online submissions for Reverse Words in a String.
// Memory Usage: 7.1 MB, less than 83.20% of C++ online submissions for Reverse Words in a String.
class Solution {
public:
    std::string reverseWords(const std::string& s) {
        auto returnValue = std::string(s.size(), '\0');
        auto writerCurrent = returnValue.begin();
        auto writerPreviousWord = returnValue.end();
        bool wasSpace = true;

        for (auto it = s.rbegin(); it < s.rend(); it += 1) {
            if (*it == ' ') {
                if (!wasSpace) {
                    // Reverse the previous word.
                    std::reverse(writerPreviousWord, writerCurrent);

                    *writerCurrent = ' ';
                    writerCurrent += 1;
                    wasSpace = true;
                }  // else ignore additional spaces
            } else {
                // Numbers or letters
                if (wasSpace) {
                    writerPreviousWord = writerCurrent;
                    wasSpace = false;
                }

                // Copy the (reversed) word.
                *writerCurrent = *it;
                writerCurrent += 1;
            }
        }

        if (wasSpace) {
            // Remove the beginning/trailing space.
            writerCurrent -= 1;
        } else {
            // Reverse the final word.
            std::reverse(writerPreviousWord, writerCurrent);
        }

        // Shrink to correct size.
        returnValue.erase(writerCurrent, returnValue.end());

        return returnValue;
    }
};


#pragma mark - 2. Modify in place (unfinished)
/**
 * Reverse whole string -> reverse individual words and spaces.
 * " abc  de fg " -> " gf ed  cba " -> "fg  ed  cba " -> "fg de   cba " -> "fg de cba   " -> "fg de cba"
 *
 * FIXME: Currently suffers from iterator out of bounds :(
 */
class Solution2 {
public:
    void reverseWords(std::string& s) {
        std::reverse(s.begin(), s.end());

        auto it1 = s.begin();
        auto it2 = it1;

        // 1st word: No space before.
        // Beginning spaces.
        while (*it2 == ' ') {
            it2 += 1;
        }
        auto beginningSpaces = it2 - it1;
        // Letters.
        while ((it2 != s.end()) && (*it2 != ' ')) {
            it2 += 1;
        }
        std::reverse(it1, it2);
        if (it2 == s.end()) {

        }

        // Upcoming words: A space before each word.
        while (it2 != s.end()) {
            it1 = it2 - beginningSpaces + 1;
            it2 = it1;

            // Beginning spaces.
            while ((it2 != s.end()) && (*it2 == ' ')) {
                it2 += 1;
            }
            if (it2 == s.end()) {
                // Everything from (it1 - 1) is a space.
                it1 -= 1;
                break;
            }
            beginningSpaces = it2 - it1;

            // Letters.
            while ((it2 != s.end()) && (*it2 != ' ')) {
                it2 += 1;
            }
            std::reverse(it1, it2);
        }

        s.erase(it1, s.end());
    }
};


#pragma mark - 3. Stack


void test(const std::string& s, const std::string& expectedResult) {
    static auto solutionInstance = Solution();

    auto sCopy = s;
    auto result = solutionInstance.reverseWords(sCopy);
//    solutionInstance.reverseWords(sCopy);
//    auto result = sCopy;
    if (result == expectedResult) {
        std::cout << "[Correct] " << s << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("abc", "abc");
    test("   a1", "a1");
    test("   a2 ", "a2");
    test("a3 ", "a3");
    test("a good   example", "example good a");
    test(" a good   example   ", "example good a");
    test("the sky is blue", "blue is sky the");
    test("  hello world  ", "world hello");

    return 0;
}
