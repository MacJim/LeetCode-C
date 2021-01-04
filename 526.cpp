/*
 * 526. Beautiful Arrangement
 * https://leetcode.com/problems/beautiful-arrangement/
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>    // std::find


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
class Solution {
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

    return 0;
}
