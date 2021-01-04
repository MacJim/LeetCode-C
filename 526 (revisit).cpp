/*
 * 526. Beautiful Arrangement
 * https://leetcode.com/problems/beautiful-arrangement/
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>    // std::find
#include <numeric>    // std::iota


#pragma mark - 1. Recursion
// Runtime: 480 ms, faster than 25.03% of C++ online submissions for Beautiful Arrangement.
// Memory Usage: 6.5 MB, less than 30.78% of C++ online submissions for Beautiful Arrangement.
class Solution1 {
private:
    void count(const int& numsCount, std::vector<bool>& visited, std::stack<int, std::vector<int>>& currentNums, int& returnValue) {
        const int nextBaseNum = currentNums.size() + 1;

        if (nextBaseNum > numsCount) {
            returnValue += 1;
            return;
        }

        // Add more numbers.
        for (int num = 1; num <= numsCount; num += 1) {
            if (visited[num - 1]) {
                // This number was used in previous iterations.
                continue;
            }

            if ((num % nextBaseNum == 0) || (nextBaseNum % num == 0)) {
                visited[num - 1] = true;
                currentNums.push(num);

                count(numsCount, visited, currentNums, returnValue);

                visited[num - 1] = false;
                currentNums.pop();
            }
        }
    }

public:
    int countArrangement(int n) {
        if (n <= 3) {
            return n;
        }

        int returnValue = 0;

        /// Indices start with 0.
        auto visited = std::vector<bool>(n, false);
        /// Numbers start with 1.
        auto currentNums = std::stack<int, std::vector<int>>();

        count(n, visited, currentNums, returnValue);

        return returnValue;
    }
};


#pragma mark - 2. Optimized 1
// Runtime: 420 ms, faster than 29.18% of C++ online submissions for Beautiful Arrangement.
// Memory Usage: 6.4 MB, less than 64.86% of C++ online submissions for Beautiful Arrangement.
class Solution2 {
private:
    void count(const int& numsCount, std::vector<bool>& visited, const int nextBaseNum, int& returnValue) {
        if (nextBaseNum > numsCount) {
            returnValue += 1;
            return;
        }

        // Add more numbers.
        for (int num = 1; num <= numsCount; num += 1) {
            if (visited[num - 1]) {
                // This number was used in previous iterations.
                continue;
            }

            if ((num % nextBaseNum == 0) || (nextBaseNum % num == 0)) {
                visited[num - 1] = true;

                count(numsCount, visited, nextBaseNum + 1, returnValue);

                visited[num - 1] = false;
            }
        }
    }

public:
    int countArrangement(int n) {
        if (n <= 3) {
            return n;
        }

        int returnValue = 0;

        /// Indices start with 0.
        auto visited = std::vector<bool>(n, false);
        /// Numbers start with 1.
        int nextBaseNum = 1;

        count(n, visited, nextBaseNum, returnValue);

        return returnValue;
    }
};


#pragma mark - 3. Swapping numbers (revisit)
// Runtime: 8 ms, faster than 96.59% of C++ online submissions for Beautiful Arrangement.
// Memory Usage: 6.3 MB, less than 88.92% of C++ online submissions for Beautiful Arrangement.
class Solution {
private:
    int count(const int endNum, std::vector<int>& currentNums) {
        if (endNum <= 0) {
            return 1;
        }

        int returnValue = 0;

        // Swap numbers.
        const auto endIndex = endNum - 1;
        for (int startIndex = endIndex; startIndex >= 0; startIndex -= 1) {
            // `startIndex` and `endIndex` may equal.
            // This handles the "unmodified" case.
            auto& startNum = currentNums[startIndex];

            if ((endNum % startNum == 0) || (startNum % endNum == 0)) {
                // They are swappable.
                std::swap(startNum, currentNums[endIndex]);
                returnValue += count(endNum - 1, currentNums);
                std::swap(startNum, currentNums[endIndex]);
            }
        }

        return returnValue;
    }

public:
    int countArrangement(int n) {
        if (n <= 3) {
            return n;
        }

        /// Numbers start with 1.
        auto currentNums = std::vector<int>(n, 0);
        // Initial value works.
        std::iota(currentNums.begin(), currentNums.end(), 1);

        return count(n, currentNums);
    }
};


void test(int n, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.countArrangement(n);

    if (result == expectedResult) {
        std::cout << "[Correct] " << n << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << n << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(1, 1);
    test(2, 2);
    test(3, 3);
    test(4, 8);
    test(5, 10);
    test(6, 36);

    return 0;
}
