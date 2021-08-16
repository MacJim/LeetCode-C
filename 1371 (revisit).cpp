/*
 * 1371. Find the Longest Substring Containing Vowels in Even Counts
 * https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/
 */

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <unordered_map>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Test each length in a rolling fashion (my own solution, hard to implement the indices)
/*
 * Assume a string of length 6: "abcdef"
 *
 * - Pass 1: Test length 6: Forward: "abcdef"
 * - Pass 2: Test length 5: Backward: "bcdef", "abcde"
 * - Pass 3: Test length 4: Forward: "abcd", "bcde", "cdef"
 * - Pass 4: Test length 3: Backward: "fed", "cde", "bcd" (found, return)
 *
 * Inter- and intra-passes are done similarly to rolling hashes.
 */
// Runtime: 44 ms, faster than 98.09% of C++ online submissions for Find the Longest Substring Containing Vowels in Even Counts.
// Memory Usage: 14.1 MB, less than 99.90% of C++ online submissions for Find the Longest Substring Containing Vowels in Even Counts.
class Solution1 {
private:
    inline int getOccurrenceIndex(const char& c) {
        switch (c) {
            case 'a':
                return 0;

            case 'e':
                return 1;

            case 'i':
                return 2;

            case 'o':
                return 3;

            case 'u':
                return 4;

            default:
                return -1;
        }
    }

private:
    static constexpr std::array<int, 5> expectedOccurrences = {true, true, true, true, true};

public:
    int findTheLongestSubstring(const std::string& s) {
        /// `true` for even occurrences.
        auto occurrences = std::array<int, 5>({true, true, true, true, true});
        for (const auto& c: s) {
            const int occurrenceIndex = getOccurrenceIndex(c);
            if (occurrenceIndex != -1) {
                occurrences[occurrenceIndex] = !occurrences[occurrenceIndex];
            }
        }

        if (occurrences == expectedOccurrences) {
            return s.size();
        }

        for (int length = (s.size() - 1); length > 0; length -= 1) {
            if (length % 2) {
                // MARK: Backward pass
                // Remove the front element.
                int frontIndex = s.size() - length - 1;
                const int frontOccurrenceIndex = getOccurrenceIndex(s[frontIndex]);
                if (frontOccurrenceIndex != -1) {
                    occurrences[frontOccurrenceIndex] = !occurrences[frontOccurrenceIndex];
                }

                if (occurrences == expectedOccurrences) {
                    return length;
                }

                // Go backward.
                for (; frontIndex >= 0; frontIndex -= 1) {
                    const int backIndex = frontIndex + length;

                    const int frontOccurrenceIndex = getOccurrenceIndex(s[frontIndex]);
                    if (frontOccurrenceIndex != -1) {
                        occurrences[frontOccurrenceIndex] = !occurrences[frontOccurrenceIndex];
                    }

                    const int backOccurrenceIndex = getOccurrenceIndex(s[backIndex]);
                    if (backOccurrenceIndex != -1) {
                        occurrences[backOccurrenceIndex] = !occurrences[backOccurrenceIndex];
                    }

                    if (occurrences == expectedOccurrences) {
                        return length;
                    }
                }
            } else {
                // MARK: Forward pass
                // Remove from back.
                int backIndex = length;
                const int backOccurrenceIndex = getOccurrenceIndex(s[backIndex]);
                if (backOccurrenceIndex != -1) {
                    occurrences[backOccurrenceIndex] = !occurrences[backOccurrenceIndex];
                }

                if (occurrences == expectedOccurrences) {
                    return length;
                }

                // Go forward.
                for (; backIndex < s.size(); backIndex += 1) {
                    const int frontIndex = backIndex - length;

                    const int frontOccurrenceIndex = getOccurrenceIndex(s[frontIndex]);
                    if (frontOccurrenceIndex != -1) {
                        occurrences[frontOccurrenceIndex] = !occurrences[frontOccurrenceIndex];
                    }

                    const int backOccurrenceIndex = getOccurrenceIndex(s[backIndex]);
                    if (backOccurrenceIndex != -1) {
                        occurrences[backOccurrenceIndex] = !occurrences[backOccurrenceIndex];
                    }

                    if (occurrences == expectedOccurrences) {
                        return length;
                    }
                }
            }
        }

        return 0;
    }
};


#pragma mark - 2. Find the first occurrence of each character
// WRONG ANSWER because I didn't log all combinations of even/odd numbers.
class Solution2 {
private:
    inline int getOccurrenceIndex(const char& c) {
        switch (c) {
            case 'a':
                return 0;

            case 'e':
                return 1;

            case 'i':
                return 2;

            case 'o':
                return 3;

            case 'u':
                return 4;

            default:
                return -1;
        }
    }

private:
//    static constexpr std::array<int, 5> expectedOccurrences = {true, true, true, true, true};

public:
    int findTheLongestSubstring(const std::string& s) {
        auto firstOccurrences = std::array<int, 5>({-1, -1, -1, -1, -1});
        auto isEven = std::array<bool, 5>({true, true, true, true, true});

        int returnValue = 0;
        for (int i = 0; i < s.size(); i += 1) {
            const int occurrenceIndex = getOccurrenceIndex(s[i]);
            if (occurrenceIndex != -1) {
                isEven[occurrenceIndex] = !isEven[occurrenceIndex];
                if (firstOccurrences[occurrenceIndex] == -1) {
                    firstOccurrences[occurrenceIndex] = i;
                }
            }

            int start = 0;
            for (int j = 0; j < 5; j += 1) {
                if (!isEven[j]) {
                    // Will need to find the first matching occurrence.
                    start = std::max(start, firstOccurrences[j] + 1);
                }
            }

            const int currentDistance = i - start + 1;
            returnValue = std::max(returnValue, currentDistance);
        }

        return returnValue;
    }
};


#pragma mark - 3. Find the first occurrence of each even/odd combination (revisit)
// Runtime: 80 ms, faster than 67.87% of C++ online submissions for Find the Longest Substring Containing Vowels in Even Counts.
// Memory Usage: 14.4 MB, less than 99.10% of C++ online submissions for Find the Longest Substring Containing Vowels in Even Counts.
class Solution {
private:
    inline int getOccurrenceIndex(const char& c) {
        switch (c) {
            case 'a':
                return 0;

            case 'e':
                return 1;

            case 'i':
                return 2;

            case 'o':
                return 3;

            case 'u':
                return 4;

            default:
                return -1;
        }
    }

public:
    int findTheLongestSubstring(const std::string& s) {
        /// The first occurrence of all even/odd **permutations**.
        auto firstOccurrences = std::unordered_map<int, int>({{0, -1}});
        /// Use a single integer to log the even/odd occurrences of all vowels.
        int isOdd = 0;

        int returnValue = 0;
        for (int i = 0; i < s.size(); i += 1) {
            const int occurrenceIndex = getOccurrenceIndex(s[i]);
            if (occurrenceIndex != -1) {
                isOdd ^= (1 << occurrenceIndex);    // XOR
                if (!firstOccurrences.count(isOdd)) {
                    firstOccurrences[isOdd] = i;    // Log first position of this permutation.
                }
            }

            const int currentDistance = i - firstOccurrences[isOdd];
            returnValue = std::max(returnValue, currentDistance);
        }

        return returnValue;
    }
};



void test(const std::string& s, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.findTheLongestSubstring(s);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("eleetminicoworoep", 13);
    test("leetcodeisgreat", 5);
    test("bcbcbc", 6);
    test("abcdef", 3);
    test("bcbcbcbcbcabcd", 10);
    test("tyrwpvlifrgjghlcicyocusukhmjbkfkzsjhkdrtsztchhazhmcircxcauajyzlppedqyzkcqvffyeekjdwqtjegerxbyktzvrxwgfjnrfbwvhiycvoznriroroamkfipazunsabwlseseeiimsmftchpafqkquovuxhhkpvphwnkrtxuiuhbcyqulfqyzgjjwjrlfwwxotcdtqsmfeingsxyzbpvmwulmqfrxbqcziudixceytvvwcohmznmfkoetpgdntrndvjihmxragqosaauthigfjergijsyivozzfrlpndygsmgjzdzadsxarjvyxuecqlszjnqvlyqkadowoljrmkzxvspdummgraiutxxxqgotqnxwjwfotvqglqavmsnmktsxwxcpxhuujuanxueuymzifycytalizwnvrjeoipfoqbiqdxsnclcvoafqwfwcmuwitjgqghkiccwqvloqrxbfjuxwriltxhmrmfpzitkwhitwhvatmknyhzigcuxfsosxetioqfeyewoljymhdwgwvjcdhmkpdfbbztaygvbpwqxtokvidtwfdhmhpomyfhhjorsmgowikpsdgcbazapkmsjgmfyuezaamevrbsmiecoujabrbqebiydncgapuexivgvomkuiiuuhhbszsflntwruqblrnrgwrnvcwixtxycifdebgnbbucqpqldkberbovemywoaxqicizkcjbmbxikxeizmzdvjdnhqrgkkqzmspdeuoqrxswqrajxfglmqkdnlescbjzurknjklikxxqqaqdekxkzkscoipolxmcszbebqpsizhwsxklzulmjotkrqfaeivhsedfynxtbzdrviwdgicusqucczgufqnaslpwzjhgtphnovlrgz", 831);

    return 0;
}
