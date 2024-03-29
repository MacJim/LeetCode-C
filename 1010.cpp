/*
 * 1010. Pairs of Songs With Total Durations Divisible by 60
 * https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/
 *
 * Dec 8, 2020 daily challenge.
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1
// Wrong answer
// What was I thinking? Did I think that all numbers are multiples of 10?
class Solution1 {
private:
    static int factorial(int num) {
        static std::vector<int> factorialCache = {1, 1, 2};

        if (factorialCache.size() > num) {
            return factorialCache[num];
        }

        while (factorialCache.size() <= num) {
            factorialCache.push_back((factorialCache.size()) * factorialCache.back());
        }

        return factorialCache.back();
    }

public:
    int numPairsDivisibleBy60(std::vector<int>& time) {
        if (time.size() < 2) {
            return 0;
        }

        /// * 10
        auto occurrences = std::vector<int>(6, 0);

        for (const auto& t: time) {
            const auto remainder = t % 60;
            occurrences[remainder / 10] += 1;
        }

        int returnValue = 0;

        // 0 matches 0
        // choose(n, k) = n! / (k! * (n - k)!)
        if (occurrences[0] > 1) {
            returnValue += factorial(occurrences[0]) / factorial(2) / factorial(occurrences[0] - 2);
        }

        // 1 matches 5
        returnValue += occurrences[1] * occurrences[5];
        
        // 2 matches 4
        returnValue += occurrences[2] * occurrences[4];
        
        // 3 matches 3
        if (occurrences[3] > 1) {
            returnValue += factorial(occurrences[3]) / factorial(2) / factorial(occurrences[3] - 2);
        }

        return returnValue;
    }
};


#pragma mark - 2
// Overflow
class Solution2 {
public:
    static int factorial(int num) {
        static std::vector<int> factorialCache = {1, 1, 2};

        if (factorialCache.size() > num) {
            return factorialCache[num];
        }

        while (factorialCache.size() <= num) {
            factorialCache.push_back((factorialCache.size()) * factorialCache.back());
        }

        return factorialCache.back();
    }

    /// Choose `k` from `n`
    static int choose(int n, int k) {
        return factorial(n) / factorial(k) / factorial(n - k);    // NOTE: This overflows with big test cases.
    }

public:
    int numPairsDivisibleBy60(std::vector<int>& time) {
        if (time.size() < 2) {
            return 0;
        }

        /// % 60
        auto occurrences = std::vector<int>(60, 0);

        for (const auto& t: time) {
            occurrences[t % 60] += 1;
        }

        int returnValue = 0;

        // Special: 0 matches 0
        // choose(n, k) = n! / (k! * (n - k)!)
        if (occurrences[0] > 1) {
            returnValue += choose(occurrences[0], 2);
        }

        // Special: 30 matches 30
        if (occurrences[30] > 1) {
            returnValue += choose(occurrences[30], 2);
        }

        // Other cases: 1 ~ 29
        for (int i = 1; i <= 29; i += 1) {
            const int j = 60 - i;
            returnValue += occurrences[i] * occurrences[j];
        }

        return returnValue;
    }
};


#pragma mark - 3. Optimized C(n, 2)
// Runtime: 56 ms, faster than 67.06% of C++ online submissions for Pairs of Songs With Total Durations Divisible by 60.
// Memory Usage: 23.5 MB, less than 43.61% of C++ online submissions for Pairs of Songs With Total Durations Divisible by 60.
class Solution {
public:
    /// Choose 2 from `n`
    static int choose2(int n) {
        return n * (n - 1) / 2;    // NOTE: This overflows with big test cases.
    }

public:
    int numPairsDivisibleBy60(std::vector<int>& time) {
        if (time.size() < 2) {
            return 0;
        }

        /// % 60
        auto occurrences = std::vector<int>(60, 0);

        for (const auto& t: time) {
            occurrences[t % 60] += 1;
        }

        int returnValue = 0;

        // Special: 0 matches 0
        // choose(n, k) = n! / (k! * (n - k)!)
        if (occurrences[0] > 1) {
            returnValue += choose2(occurrences[0]);
        }

        // Special: 30 matches 30
        if (occurrences[30] > 1) {
            returnValue += choose2(occurrences[30]);
        }

        // Other cases: 1 ~ 29
        for (int i = 1; i <= 29; i += 1) {
            const int j = 60 - i;
            returnValue += occurrences[i] * occurrences[j];
        }

        return returnValue;
    }
};


void test(const std::vector<int>& time, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto timeCopy = time;
    auto result = solutionInstance.numPairsDivisibleBy60(timeCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << timeCopy << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << timeCopy << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
//    std::cout << Solution::factorial(10) << " " << Solution::factorial(5) << " " << Solution::factorial(3) << " " << Solution::factorial(7) << std::endl;
//    std::cout << Solution::choose(24, 2) << std::endl;

    test({95,51,462,476,245,271,481,257,130,314,244,215,397,60,21,60,168,213,107,394,209,223,410,220,444,337,264,417,356,409,467,23,273,236,281,478,227,69,207,255,18,133,362,161,329,66,233,487,23,315,296,60,424,370,331,305,333,218,145,379,212,413,486,111,45,239,57,395,140,405,266,212,356,28,346,358,309,263,101,46,167,352,359,381,205,308,213,390,211,142,287,476,189,164,9,5,58,206,39,248,409,189,139,128,107,342,466,143,267,372,119,172,416,5,31,77,167,133,192,182,323,238,219,140,327,275,361,435,452,489,185,468,252,144,233,7,243,83,72,35,446,188,259,185,499,141,457,33,267,238,224,121,164,436,375,259,247,136,207,391,255,182,237,451,184,407,156,386,249,351,336,110,262,119,375,302,95,236,279,172,199,346,14,291,338,102,101,182,28,321,446,384,191,71,259,410,113,160,372,260,452,246,132,416,20,113,257,113,300,222,295,10,461,449,233,73,273,91,464,452,362,477,2,435,373,139,165,20,455,361,62,253,412,281,362,94,246,475,224,176,22,388,100,255,180,340,93,245,442,420,353,25,329,232,216,2,120,450,57,133,47,309,460,354,93,259,485,339,490,56,488,311,250,217,247,420,376,329,491,165,488,251,430,470,122,111,359,343,200,480,162,353,344,349,301,145,388,456,17,455,487,324,493,248,151,53,414,396,194,170,290,349,287,242,53,77,219,280,267,384,118,314,12,189,118,379,254,160,179,29,87,274,346,228,488,481,481,56,67,3,256,463,150,399,340,464,9,28,479,250,256,21,209,87,59,7,433,189,433,22,76,45,217,301,34,98,248,265,496,319,157,69,216,46,299,233,153,310,151,299,283,206,335,220,65,195,76,213,10,150,104,488,139,360,426,14,115,136,409,36,165,488,440,111,462,369,341,234,372,226,369,136,424,125,418,215,178,291,54,183,140,82,326,92,50,82,311,12,1,9,99,106,195,153,77,108,60,211,69,194,253,246,353,273,483,452,488,229,412,333,441,39,255,190,480,280,419,19,337,252,312,154,247,380,94,70,55,320,448,328,230,18,322,309,79,477,239,314,426,19,408,151,62,495,183,401,431,396,93,336,205,423,113,369,376,217,158,389,250,271,465,5,108,221,309,148,57,500,209,259,149,479,321,368,347,358,109,23,152,114,476,428,314,78,95,16,58,317,84,108,338,386,495,128,172,459,29,385,181,102,3,8,198,359,115,149,82,88,340,416,450,472,353,495,432,404,370,74,426,121,423,406,260,84,23,459,384,156,310,66,493,108,43,248,408,134,323,416,202,110,20,425,38,257,19,334,300,362,319,12,82,200,95,316,447,221,372,285,490,245,84,386,188,109,244,411,232,473,56,351,44,278,294,145,198,65,242,340,237,242,308,385,204,2,344,220,63,250,174,79,186,289,288,82,159,285,495,129,8,478,202,74,263,474,184,212,160,476,374,345,103,106,307,436,291,435,363,332,292,425,429,184,290,332,189,20,316,317,458,287,202,79,301,431,387,178,88,94,335,295,52,53,170,305,155,268,380,395,211,379,347,284,417,32,264,318,47,318,265,191,131,331,301,399,309,476,484,348,277,136,204,1,447,124,226,100,109,106,177,43,328,33,418,410,127,3,171,75,198,307,289,73,89,95,353,483,7,412,90,254,24,253,265,162,439,283,352,169,184,272,200,234,38,495,83,212,314,341,175,368,143,380,329,391,4,255,399,13,182,3,198,251,159,417,4,410,492,149,243,22,148,229,300,112,458,228,350,36,479,83,361,276,9,11,51,111,45,345,342,47,50,465,467,219,368,92,268,390,487,450,107,282,189,409,310,70,227,212,449,380,48,148,275,452,48,274,102,415,191,391,38,324,460,31,429,171,202,383,162,245,42,179,341,281,283,4,225,259,461,307,294,167,67,408,271,154,393,396,366,354,230,60,323,9,122,28,389,26,266,417,352,459,423,495,148,28,223,231,144,179,380,2,480,26,151,304,469,88,94,382,131,284,458,452,241,72,438,296,225,172,150,130,40,273,402,122,96,374,492,377,238,262,261,179,24,251,252,190,63,169,481,114,226,93,440,320,49,7,248,124,283,425,448,206,133,257,257,204,209,235,474,426,284,272,123,133,140,100,263,484,59,397,25,362,334,86,195,43,266,117,174,62,430,281,307,122,184,133,170,121,419,103,490,458,48,314,46,201,2,128,254,166,416,181,399,201,191,262,251,81,225,311,174,216,155,285,324,325,111,272,152,246,35,167,422,398,401,55,314,84,337,300,440,494,18,124,86,472,57,433,128,246,392,227,499,409,421,180,362,147,152,415,39,170,136,2,132,477,463,195,56,491,217,398,302,54,365,254,338,465,141,252,359,319,53,187,17,426,183,50,240,196,70,488,240,121,223,484,204,151,134,367,131,281,243,96,357,77,322,79,67,250,142,405,215,82,23,58,297,346,400,352,453,133,173,145,234,152,318,469,36,292,471,314,91,7,446,1,298,287,76,196,109,434,136,262,288,461,114,385,317,284,333,441,406,464,14,442,481,78,467,138,446,265,441,175,232,419,478,78,216,61,455,243,345,106,427,435,274,136,431,66,71,135,436,209,457,7,392,437,65,59,157,141,269,257,384,197,235,63,203,426,71,29,304,402,318,384,312,490,78,121,305,139,19,340,368,24,409,218,31,356,475,59,476,465,245,316,340,69,195,34,346,292,464,261,38,373,484,82,2,413,159,106,320,39,387,281,421,251,114,99,495,330,202,362,233,71,370,319,74,289,68,420,10,467,370,328,53,110,299,203,273,223,205,214,300,419,213,41,59,200,20,172,381,263,98,309,154,368,333,484,313,240,78,106,355,244,265,475,473,411,244,268,185,468,308,9,365,129,240,464,323,249,212,496,364,119,119,195,153,17,377,181,81,326,334,395,145,13,461,57,26,163,314,71,27,248,289,148,336,339,188,202,96,310,297,200,312,235,181,61,410,169,326,445,111,464,415,199,177}, 14804);
    test({10, 10, 20, 20, 30, 150, 170, 180}, 3);
    test({15,63,451,213,37,209,343,319}, 1);
    test({60, 60, 60}, 3);
    test({30,20,150,100,40}, 3);

    return 0;
}
