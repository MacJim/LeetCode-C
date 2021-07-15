/*
 * 1814. Count Nice Pairs in an Array
 * https://leetcode.com/problems/count-nice-pairs-in-an-array/
 */


#include <iostream>
#include <vector>
#include <unordered_map>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Optimize brute force with hash table
/*
 * Note that `x - rev(x) = y - rev(y)`.
 * Pre-calculate that value for each number.
 */
// Runtime: 104 ms, faster than 90.27% of C++ online submissions for Count Nice Pairs in an Array.
// Memory Usage: 56.8 MB, less than 83.89% of C++ online submissions for Count Nice Pairs in an Array.
class Solution {
private:
    const int MOD = 1000000007;

private:
    /*
     * Don't use factorials to calculate `choose 2 from n` due to overflow issues.
     */
//    static std::vector<int> factorials;
//    static int getFactorial(int x) {
//        while (factorials.size() <= x) {
//            factorials.push_back(factorials.back() * factorials.size());
//        }
//
//        return factorials[x];
//    }

private:
    /**
     * x - rev(x)
     *
     * @param x
     * @return
     */
    inline int getDelta(const int x) {
        if (x == 0) {
            // This will cause an infinite loop.
            return 0;
        }

        int xCopy = x;

        // Ignore trailing 0s.
        while ((xCopy % 10) == 0) {
            xCopy = xCopy / 10;
        }

        int reverse = 0;
        while (xCopy) {
            reverse *= 10;

            const int lastDigit = xCopy % 10;
            reverse += lastDigit;

            xCopy /= 10;
        }

        return x - reverse;
    }

public:
    int countNicePairs(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }

        auto occurrences = std::unordered_map<int, int>();
        for (const int& num: nums) {
            const int delta = getDelta(num);
            occurrences[delta] += 1;
        }

        int returnValue = 0;

        for (const auto& [num, occurrence]: occurrences) {
            if (occurrence < 2) {
                continue;
            } else if (occurrence == 2) {
                returnValue += 1;
            } else {
                long long currentValue = static_cast<long long>(occurrence) * static_cast<long long>(occurrence - 1) / 2;
                currentValue %= MOD;
                returnValue += currentValue;
            }

            returnValue %= MOD;
        }

        return returnValue;
    }
};


//std::vector<int> Solution::factorials = std::vector<int>({0, 1, 2});


void test(const std::vector<int>& nums, const int expectedResult) {
    auto solutionInstance = Solution();

//    std::cout << solutionInstance.getDelta(12340) << std::endl;

    auto numsCopy = nums;
    auto result = solutionInstance.countNicePairs(numsCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({8047408,192867140,497837845,279787822,151999002,168514912,193424242,399636844,132424231,476736524,267958611,493350382,476382727,232939232,197000791,295291645,126313621,374645524,7956597,1376731,496463745,234481430,359130803,287625836,250572050,42311324,477434624,493231448,493231244,150494051,184645534,365252413,495764582,335976531,384564332,377151623,198736741,335161533,245552540,194897341,83911938,220562020,496645745,287151782,374635526,372483324,485101584,271797172,244949442,254333303,251635002,459181805,472392123,241350140,256121502,336895621,354635302,358909704,194525491,3606063,194150341,63477436,341936141,60299206,69811896,369928813,229926920,435310522,299542980,463777364,164534512,305885501,437181734,74288247,487281835,171161022,423966312,496989544,452633252,252433101,141565141,315895501,478897927,232532230,472451262,160504114,476666674,6179716,251483002,474777474,443532332,475808424,457514604,400936002,384878483,172616122,283292232,165645615,392000144,378636873}, 678);    // 29 occurrences.
    test({13,10,35,24,76}, 4);
    test({42,11,1,97}, 2);

    return 0;
}
