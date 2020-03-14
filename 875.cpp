/*
 * 875. Koko Eating Bananas
 * https://leetcode.com/problems/koko-eating-bananas/
 */

#include <iostream>
#include <vector>


// MARK: - 1. Binary search.
/* 
 * Special case: hours == piles count. Return biggest pile size.
 * 
 * Find min and max piles count.
 * Search from middle.
 * 
 * Divide each pile with val.
 */
// Runtime: 64 ms, faster than 77.08% of C++ online submissions for Koko Eating Bananas.
// Memory Usage: 9.6 MB, less than 100.00% of C++ online submissions for Koko Eating Bananas.
class Solution {
public:
    int minEatingSpeed(std::vector<int>& piles, int hours) {
        const auto pilesCount = piles.size();
        const auto maxCountIt = std::max_element(piles.begin(), piles.end());
        auto maxCount = *maxCountIt;

        if (hours == pilesCount) {
            return maxCount;
        }

        // const auto minCountIt = std::min_element(piles.begin(), piles.end());
        auto minCount = 1;

        int returnValue = maxCount;
        int midCount = 0;

        while (maxCount > minCount) {
            midCount = (maxCount + minCount) / 2;

            int totalHours = 0;
            for (const auto& aPile: piles) {
                totalHours += (aPile / midCount);

                int remainder = aPile % midCount;
                if (remainder != 0) {
                    totalHours += 1;
                }
            }

            if (totalHours <= hours) {
                // Even if `totalHours == hours`, we'll try to find smaller values.
                returnValue = midCount;
                maxCount = midCount;
            } else if (totalHours > hours) {
                if (minCount == midCount) {
                    break;
                }
                minCount = midCount;
            }
        }

        if (maxCount == minCount) {
            int totalHours = 0;
            for (const auto& aPile: piles) {
                totalHours += (aPile / minCount);

                int remainder = aPile % minCount;
                if (remainder != 0) {
                    totalHours += 1;
                }
            }

            if (totalHours <= hours) {
                returnValue = minCount;
            }
        }
        
        return returnValue;
    }
};


// MARK: - 2 (unfinished)
/*
 * int times = hours / piles count
 * int delta = hours - piles count
 */
class Solution2 {
public:
    int minEatingSpeed(std::vector<int>& piles, int hours) {
        const auto pilesCount = piles.size();
        int delta = hours - pilesCount;

        const auto maxCountIt = std::max_element(piles.begin(), piles.end());
        auto maxCount = *maxCountIt;

        return 0;
    }
};


void test(std::vector<int>& piles, int hours) {
    static auto solutionInstance = Solution();
    auto result = solutionInstance.minEatingSpeed(piles, hours);
    std::cout << "Result: " << result << std::endl;
}


int main() {
    std::vector<int> piles1 = {3,6,7,11};
    int hour1 = 8;
    test(piles1, hour1);    // 4

    std::vector<int> piles2 = {30,11,23,4,20};
    int hour2 = 5;
    test(piles2, hour2);    // 30

    std::vector<int> piles3 = {30,11,23,4,20};
    int hour3 = 6;
    test(piles3, hour3);    // 23

    std::vector<int> piles4 = {332484035, 524908576, 855865114, 632922376, 222257295, 690155293, 112677673, 679580077, 337406589, 290818316, 877337160, 901728858, 679284947, 688210097, 692137887, 718203285, 629455728, 941802184};
    int hour4 = 823855818;
    test(piles4, hour4);    // 14

    return 0;
}
