/*
 * 115. Distinct Subsequences
 * https://leetcode.com/problems/distinct-subsequences/
 */

#include <iostream>
#include <vector>
#include <string>


#pragma mark - 1. DP
// 61 / 62 test cases passed.
// Runtime error: signed integer overflow: 2073949853 + 592325108 cannot be represented in type 'int' (solution.cpp)
class Solution1 {
public:
    int numDistinct(std::string s, std::string t) {
        if (s.empty() || t.empty()) {
            return 0;
        }

        auto previousPossibilities = std::vector<int>(s.size(), 0);

        // 0th char in `t`.
        const char& c0 = t[0];
        if (s[0] == c0) {
            previousPossibilities[0] = 1;
        }
        for (size_t j = 1; j < s.size(); j += 1) {
            if (s[j] == c0) {
                previousPossibilities[j] = previousPossibilities[j - 1] + 1;
            } else {
                previousPossibilities[j] = previousPossibilities[j - 1];
            }
        }

        // Upcoming chars in `t`.
        for (size_t i = 1; i < t.size(); i += 1) {
            const char& currentChar = t[i];

            auto currentPossibilities = std::vector<int>(s.size(), 0);

            for (size_t j = i; j < s.size(); j += 1) {
                if (s[j] == currentChar) {
                    currentPossibilities[j] = currentPossibilities[j - 1] + previousPossibilities[j - 1];    // Doesn't count current character, and count current character.
                } else {
                    currentPossibilities[j] = currentPossibilities[j - 1];
                }
            }

            previousPossibilities = std::move(currentPossibilities);
        }

        return previousPossibilities.back();
    }
};


#pragma mark - 2. 1 in another direction
// 61 / 62 test cases passed.
// Runtime error: signed integer overflow: 1474397256 + 891953512 cannot be represented in type 'int' (solution.cpp)
class Solution2 {
public:
    int numDistinct(std::string s, std::string t) {
        if (s.empty() || t.empty()) {
            return 0;
        }

        auto previousPossibilities = std::vector<int>(t.size(), 0);

        // 0th char in `s`.
        if (s[0] == t[0]) {
            previousPossibilities[0] = 1;
        }
        // Upcoming possibilities in the first column are all 0, because the `t` substrings are longer than `s` substrings.

        // Upcoming chars in `s`.
        for (size_t j = 1; j < s.size(); j += 1) {
            const char& currentChar = s[j];

            auto currentPossibilities = std::vector<int>(t.size(), 0);

            // 0th char in `t`.
            if (t[0] == currentChar) {
                currentPossibilities[0] = previousPossibilities[0] + 1;
            } else {
                currentPossibilities[0] = previousPossibilities[0];
            }

            // Upcoming chars in `t`.
            for (size_t i = 1; i < t.size(); i += 1) {
                if (t[i] == currentChar) {
                    currentPossibilities[i] = previousPossibilities[i - 1] + previousPossibilities[i];
                } else {
                    currentPossibilities[i] = previousPossibilities[i];
                }
            }

            previousPossibilities = std::move(currentPossibilities);
        }

        return previousPossibilities.back();
    }
};


#pragma mark - 3. Change `int` in 1 to `long`
// I always forget this because I use Python so much :(
// Runtime: 8 ms, faster than 47.82% of C++ online submissions for Distinct Subsequences.
// Memory Usage: 7.5 MB, less than 73.97% of C++ online submissions for Distinct Subsequences.
class Solution {
public:
    int numDistinct(std::string s, std::string t) {
        if (s.empty() || t.empty()) {
            return 0;
        }

        auto previousPossibilities = std::vector<long>(s.size(), 0);

        // 0th char in `t`.
        const char& c0 = t[0];
        if (s[0] == c0) {
            previousPossibilities[0] = 1;
        }
        for (size_t j = 1; j < s.size(); j += 1) {
            if (s[j] == c0) {
                previousPossibilities[j] = previousPossibilities[j - 1] + 1;
            } else {
                previousPossibilities[j] = previousPossibilities[j - 1];
            }
        }

        // Upcoming chars in `t`.
        for (size_t i = 1; i < t.size(); i += 1) {
            const char& currentChar = t[i];

            auto currentPossibilities = std::vector<long>(s.size(), 0);

            for (size_t j = i; j < s.size(); j += 1) {
                if (s[j] == currentChar) {
                    currentPossibilities[j] = currentPossibilities[j - 1] + previousPossibilities[j - 1];    // Doesn't count current character, and count current character.
                } else {
                    currentPossibilities[j] = currentPossibilities[j - 1];
                }
            }

            previousPossibilities = std::move(currentPossibilities);
        }

        return previousPossibilities.back();
    }
};


void test(const std::string& s, const std::string& t, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto sCopy = s;
    auto tCopy = t;
    auto result = solutionInstance.numDistinct(sCopy, tCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << s << ", " << t << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << s << ", " << t << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    std::cout << sizeof(int) << " " << sizeof(long) << " " << sizeof(long long) << std::endl;    // 4 8 8

    test("xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxzwieeuqnjozrfwmzsylcwvsthnxujvrkszqwtglewkycikdaiocglwzukwovsghkhyidevhbgffoqkpabthmqihcfxxzdejletqjoxmwftlxfcxgxgvpperwbqvhxgsbbkmphyomtbjzdjhcrcsggleiczpbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfjafmsrfdghnatexyanldrdpxvvgujsztuffoymrfteholgonuaqndinadtumnuhkboyzaqguwqijwxxszngextfcozpetyownmyneehdwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhryvqsqogpnlqfulurexdtovqpqkfxxnqykgscxaskmksivoazlducanrqxynxlgvwonalpsyddqmaemcrrwvrjmjjnygyebwtqxehrclwsxzylbqexnxjcgspeynlbmetlkacnnbhmaizbadynajpibepbuacggxrqavfnwpcwxbzxfymhjcslghmajrirqzjqxpgtgisfjreqrqabssobbadmtmdknmakdigjqyqcruujlwmfoagrckdwyiglviyyrekjealvvigiesnvuumxgsveadrxlpwetioxibtdjblowblqvzpbrmhupyrdophjxvhgzclidzybajuxllacyhyphssvhcffxonysahvzhzbttyeeyiefhunbokiqrpqfcoxdxvefugapeevdoakxwzykmhbdytjbhigffkmbqmqxsoaiomgmmgwapzdosorcxxhejvgajyzdmzlcntqbapbpofdjtulstuzdrffafedufqwsknumcxbschdybosxkrabyfdejgyozwillcxpcaiehlelczioskqtptzaczobvyojdlyflilvwqgyrqmjaeepydrcchfyftjighntqzoo", "rwmimatmhydhbujebqehjprrwfkoebcxxqfktayaaeheys", 0);
    test("bbbit", "bb", 3);
    test("bbcce", "c", 2);
    test("abcde", "ace", 1);
    test("bbbit", "bbit", 3);
    test("rabbbit", "rabbit", 3);
    test("babgbag", "bag", 5);

    return 0;
}
