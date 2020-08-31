/*
 * 264. Ugly Number II
 * https://leetcode.com/problems/ugly-number-ii/
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


#pragma mark - 1. Wrong solution
// Wrong understanding of the question.
class Solution1 {
public:
    int nthUglyNumber(int n) {
        static std::vector<uint> cachedSolutions = {0, 1};
        if (cachedSolutions.size() > n) {
            return cachedSolutions.at(n);
        }

        for (size_t i = cachedSolutions.size(); i <= n; i += 1) {
            uint currentNum = cachedSolutions.back() + 1;
            while (true) {
                if ((currentNum & 1u) == 0) {
                    // Divide by 2.
                    cachedSolutions.push_back(currentNum);
                    break;
                } else if ((currentNum % 3) == 0) {
                    cachedSolutions.push_back(currentNum);
                    break;
                } else if ((currentNum % 5) == 0) {
                    cachedSolutions.push_back(currentNum);
                    break;
                } else {
                    currentNum += 1;
                }
            }
        }

        return cachedSolutions.at(n);
    }
};


#pragma mark - 2. Signed integer overflow
class Solution2 {
public:
    int nthUglyNumber(int n) {
        static auto currentNums = std::set<int>({1});
        static auto cachedNums = std::vector<int>({0});

        if (cachedNums.size() > n) {
            return cachedNums.at(n);
        }

        while (cachedNums.size() <= n) {
            auto firstIt = currentNums.begin();
            int firstNum = *firstIt;
            currentNums.erase(firstIt);

            while (firstNum < 0) {
                firstIt = currentNums.begin();
                firstNum = *firstIt;
                currentNums.erase(firstIt);
            }

            cachedNums.push_back(firstNum);

            currentNums.insert(firstNum * 2);
            currentNums.insert(firstNum * 3);
            currentNums.insert(firstNum * 5);    // Signed integer overflow here. Not allowed on LeetCode.
        }

        return cachedNums.at(n);
    }
};


#pragma mark - 3. Three indices.
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Ugly Number II.
// Memory Usage: 6.3 MB, less than 79.74% of C++ online submissions for Ugly Number II.
class Solution {
public:
    int nthUglyNumber(int n) {
        n -= 1;

        static auto cachedNums = std::vector<int>({1});
        static size_t i2 = 0;
        static size_t i3 = 0;
        static size_t i5 = 0;

        while (cachedNums.size() <= n) {
            const int num2 = cachedNums.at(i2) * 2;
            const int num3 = cachedNums.at(i3) * 3;
            const int num5 = cachedNums.at(i5) * 5;

            const int minNum = std::min(std::min(num2, num3), num5);
            cachedNums.push_back(minNum);

            // Deal with equals: decrease both indices.
            if (num2 == minNum) {
                i2 += 1;
            }
            if (num3 == minNum) {
                i3 += 1;
            }
            if (num5 == minNum) {
                i5 += 1;
            }
        }

        return cachedNums.at(n);
    }
};


int main() {
    auto solutionInstance = Solution();
//    std::cout << solutionInstance.nthUglyNumber(0) << std::endl;    // 0
    std::cout << solutionInstance.nthUglyNumber(1) << std::endl;    // 1
    std::cout << solutionInstance.nthUglyNumber(10) << std::endl;    // 12
    std::cout << solutionInstance.nthUglyNumber(11) << std::endl;    // 15
    std::cout << solutionInstance.nthUglyNumber(1690) << std::endl;
}
