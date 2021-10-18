/*
 * 1528. Shuffle String
 * https://leetcode.com/problems/shuffle-string/
 */

/*
 * Don't know why it asks to return a copy, rather than shuffling in-place.
 */

#include <iostream>
#include <string>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Return a copy
// Runtime: 8 ms, faster than 73.71% of C++ online submissions for Shuffle String.
// Memory Usage: 15.2 MB, less than 42.89% of C++ online submissions for Shuffle String.
class Solution1 {
public:
    std::string restoreString(const std::string& s, const std::vector<int>& indices) {
        auto returnValue = std::string(s.size(), '\0');

        for (int i = 0; i < s.size(); i += 1) {
            returnValue[indices[i]] = s[i];
        }

        return returnValue;
    }
};


#pragma mark - 2. Modify the string and the `indices` array in-place by swapping
// WRONG ANSWER
// Cannot simply swap.
class Solution2 {
public:
    std::string restoreString(std::string& s, std::vector<int>& indices) {
        for (int i = 0; i < s.size(); i += 1) {
            int nextIndex = indices[i];
            if (nextIndex == -1) {
                // Visited.
                continue;
            }

            int currentIndex = i;
            std::swap(s[nextIndex], s[currentIndex]);
            currentIndex = indices[currentIndex];
            indices[currentIndex] = -1;    // -1: visited

            while (indices[currentIndex] != -1) {
                nextIndex = indices[currentIndex];
                std::swap(s[currentIndex], s[nextIndex]);
                indices[currentIndex] = -1;
                currentIndex = nextIndex;
            }
        }

        return std::move(s);
    }
};


#pragma mark - 3. Modify the string and the `indices` array in-place
// Runtime: 8 ms, faster than 73.71% of C++ online submissions for Shuffle String.
// Memory Usage: 15.1 MB, less than 76.20% of C++ online submissions for Shuffle String.
class Solution {
public:
    std::string restoreString(std::string& s, std::vector<int>& indices) {
        for (int i = 0; i < s.size(); i += 1) {
            int nextIndex = indices[i];
            if (nextIndex == -1) {
                // Visited.
                continue;
            }

            int currentIndex = i;
            char nextChar = s[nextIndex];
            s[nextIndex] = s[currentIndex];
            indices[currentIndex] = -1;
            currentIndex = nextIndex;
            nextIndex = indices[currentIndex];

            while (nextIndex != -1) {
                std::swap(s[nextIndex], nextChar);

                indices[currentIndex] = -1;
                currentIndex = nextIndex;
                nextIndex = indices[currentIndex];
            }
        }

        return std::move(s);
    }
};


void test(const std::string& s, const std::vector<int>& indices, const std::string& expectedResult) {
    auto solutionInstance = Solution();

    auto sCopy = s;
    auto indicesCopy = indices;
    auto result = solutionInstance.restoreString(sCopy, indicesCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << ", " << indices << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << ", " << indices << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("bca", {1,2,0}, "abc");
    test("aiohn", {3,1,4,2,0}, "nihao");
    test("codeleet", {4,5,6,7,0,2,1,3}, "leetcode");

    return 0;
}
