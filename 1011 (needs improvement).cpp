/*
 * 1011. Capacity To Ship Packages Within D Days
 * https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
 */

/*
 * A conveyor belt has packages that must be shipped from one port to another within D days.
 *
 * The i-th package on the conveyor belt has a weight of weights[i]. Each day, we load the ship with packages on the conveyor belt (in the order given by weights). We may not load more weight than the maximum weight capacity of the ship.
 *
 * Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within D days.
 */

#include <iostream>
#include <vector>
#include <numeric>    // std::accumulate


#pragma mark - 1. Binary Search
// Runtime: 136 ms, faster than 6.79% of C++ online submissions for Capacity To Ship Packages Within D Days.
// Memory Usage: 25.9 MB, less than 11.11% of C++ online submissions for Capacity To Ship Packages Within D Days.
// Why is this one so slow???
class Solution1 {
public:
    int shipWithinDays(std::vector<int>& weights, int days) {
        // One day only.
        auto totalWeight = std::accumulate(weights.begin(), weights.end(), 0);
        if (days == 1) {
            return totalWeight;
        }

        // One package per day.
        auto maxWeight = *std::max_element(weights.begin(), weights.end());

        const auto packagesCount = weights.size();
        if (packagesCount == days) {
            return maxWeight;
        }

        // Binary search.
        int max = totalWeight;
        int min = maxWeight;
        int returnValue = -1;

        while (max >= min) {
            int mid = (max + min) / 2;    // -1 / 2 = 0

            int sum = 0;

            for (auto it = weights.begin(); it <= weights.end(); it += 1) {
                if (*it > mid) {
                    // Ship capacity is too low.
                    sum = INT_MAX;
                    break;
                }

                int currentWeight = 0;

                currentWeight += *it;

                auto it2 = it + 1;
                for (; it2 != weights.end(); it2 += 1) {
                    auto nextWeight = currentWeight + *it2;
                    if (nextWeight > mid) {
//                        it = it2 + 1;
                        it2 -= 1;
                        break;
                    } else {
                        currentWeight = nextWeight;
                    }
                }

                it = it2;
                sum += 1;
            }

            if (sum <= days) {
                returnValue = mid;
                max = mid - 1;
            } else {
                min = mid + 1;
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Optimized 1
// Runtime: 96 ms, faster than 11.16% of C++ online submissions for Capacity To Ship Packages Within D Days.
// Memory Usage: 26.2 MB, less than 11.11% of C++ online submissions for Capacity To Ship Packages Within D Days.
class Solution {
public:
    int shipWithinDays(std::vector<int>& weights, int days) {
        // One day only.
        auto totalWeight = std::accumulate(weights.begin(), weights.end(), 0);
        if (days == 1) {
            return totalWeight;
        }

        // One package per day.
        auto maxWeight = *std::max_element(weights.begin(), weights.end());

        const auto packagesCount = weights.size();
        if (packagesCount == days) {
            return maxWeight;
        }

        // Binary search.
        int max = totalWeight;
        int min = maxWeight;
        int returnValue = -1;

        while (max > min) {
            int mid = (max + min) / 2;
            int sum = 0;
            int currentWeight = 0;
            for (const auto& w: weights) {
                int nextWeight = currentWeight + w;
                if (nextWeight > mid) {
                    sum += 1;
                    currentWeight = w;
                } else {
                    currentWeight = nextWeight;
                }
            }

            sum += 1;

            if (sum <= days) {
                returnValue = mid;
                max = mid;
            } else {
                min = mid + 1;
            }
        }

        return returnValue;
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<int> w1 = {3,2,2,4,1,4};
    int d1 = 3;
    int result1 = solutionInstance.shipWithinDays(w1, d1);    // 6
    std::cout << result1 << std::endl;

    std::vector<int> w2 = {1,2,3,4,5,6,7,8,9,10};
    int d2 = 5;
    int result2 = solutionInstance.shipWithinDays(w2, d2);    // 15
    std::cout << result2 << std::endl;

    std::vector<int> w3 = {1,2,3,1,1};
    int d3 = 4;
    int result3 = solutionInstance.shipWithinDays(w3, d3);    // 3
    std::cout << result3 << std::endl;
    return 0;
}
