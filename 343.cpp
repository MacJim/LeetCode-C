/*
 * 343. Integer Break
 */

#include <iostream>
#include <vector>


#pragma mark - 1. DP
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Integer Break.
// Memory Usage: 6.4 MB, less than 43.35% of C++ online submissions for Integer Break.
class Solution1 {
public:
    int integerBreak(int n) {
        static auto resultsCache = std::vector<int>({0, 0, 1, 2});
        if (n < resultsCache.size()) {
            return resultsCache[n];
        }

        for (int num = resultsCache.size(); num <= n; num += 1) {
            int result = 0;
            for (int num1 = 1; num1 <= (num / 2); num1 += 1) {
                const int num2 = num - num1;

                const int newResult = std::max(resultsCache[num1], num1) * std::max(resultsCache[num2], num2);
                result = std::max(result, newResult);
            }

            resultsCache.push_back(result);
        }

        return resultsCache.back();
    }
};


#pragma mark - 2. Math solution
/*
由于正整数的拆分是有限的，所以一定有上界
对于N = n1+n2+n3+...+nk
1、如果N>3，nk当中一定不会有1
2、对于ni>=5，可以分为3+(ni-3), 3*(ni-3) = 3ni-9 > ni，所以ni不会大于等于5
3、如果ni == 4，则一定分为2+2，所以ni可以认为不可能是4，否则可以分为2+2
4、对于3个以上的2，有3*3 > 2*2*2, 所以尽可能多选3
==>如果有3就拆成3，至少剩下2或4，拆成2
*/

class Solution {
public:
    int integerBreak(int n) {
        if(n <= 3) return n-1;
        int res = 1;
        if(n % 3 == 1) res *= 4, n -= 4;   //会多出一个4
        else if(n % 3 == 2) res *= 2, n -= 2;   //会多出一个2
        //剩下的是3的倍数
        while(n) res *= 3, n -= 3;
        return res;
    }
};


void test(int n, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.integerBreak(n);

    if (result == expectedResult) {
        std::cout << "[Correct] " << n << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << n << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(2, 1);
    test(10, 36);

    return 0;
}
