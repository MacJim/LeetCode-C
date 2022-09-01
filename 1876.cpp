/*
 * 1876. Substrings of Size Three with Distinct Characters
 * https://leetcode.com/problems/substrings-of-size-three-with-distinct-characters/
 */

#include <iostream>
#include <array>
#include <unordered_map>
#include <string>

#include "helpers/terminal_format.h"


#pragma mark - 1. Brute force
// Runtime: 2 ms, faster than 70.97% of C++ online submissions for Substrings of Size Three with Distinct Characters.
// Memory Usage: 6.1 MB, less than 95.75% of C++ online submissions for Substrings of Size Three with Distinct Characters.
class Solution {
public:
    int countGoodSubstrings(const std::string& s) {
        if (s.size() < 3) {
            return 0;
        }

        int returnValue = 0;
        for (int j = 2; j < s.size(); j += 1) {
            if ((s[j - 2] != s[j]) && (s[j - 1] != s[j]) && (s[j - 2] != s[j - 1])) {
                returnValue += 1;
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Length 26 array (somewhat like rolling hash) (unfinished, won't finish)
/*
 * This solution isn't worth it because the "rolling hash" region just contains 3 characters.
 * It would perform much better if that region of interest has like 1,000 characters.
 *
 * - Only lowercase letters -> Use length 26 array
 * - String length up to 100 (hmm can I justify using an array for this; IMO this might be overkill)
 */
class Solution2 {
private:
    inline bool addAndFindDuplicate(std::array<int, 26>& occurrences, const char& c) {
//        occurrences[]
        return (occurrences[c - 'a'] == 1);
    }

public:
    int countGoodSubstrings(const std::string& s) {
        // String too short.
        if (s.size() < 3) {
            return 0;
        }

        auto occurrences = std::array<int, 26>();
        int returnValue = 0;
        bool hadDuplicate = false;

        // Initial characters.
        occurrences[s[0] - 'a'] += 1;
        occurrences[s[1] - 'a'] += 1;
        occurrences[s[2] - 'a'] += 1;
        if ((occurrences[s[1] - 'a'] == 1) && (occurrences[s[2] - 'a'] == 1)) {
            returnValue += 1;
        } else {
            hadDuplicate = true;
        }

        // Upcoming characters.
        for (int j = 3; j < s.size(); j += 1) {
            const int i = j - 3;
//            occurrences[]
        }

        return returnValue;
    }
};


void test(const std::string& s, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.countGoodSubstrings(s);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("ab", 0);
    test("abc", 1);
    test("aaabb", 0);
    test("xyzzaz", 1);
    test("aababcabc", 4);

    return 0;
}
