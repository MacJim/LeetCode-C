/*
 * 714. Best Time to Buy and Sell Stock with Transaction Fee
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
 */

#include <iostream>
#include <vector>
#include <tuple>

#include "helpers/Operators.hpp"


#pragma mark - 1. Official hint: State Machine (like 309. Best Time to Buy and Sell Stock with Cooldown)
/*
 * Hint:
 *
 * Consider the first K stock prices.
 * At the end, the only legal states are that you don't own a share of stock, or that you do.
 * Calculate the most profit you could have under each of these two cases.
 *
 * States and actions:
 *
 * - own:
 *   - wait -> own
 *   - sell -> not own
 * - not own:
 *   - wait -> not own
 *   - buy -> own
 */
// Runtime: 196 ms, faster than 38.02% of C++ online submissions for Best Time to Buy and Sell Stock with Transaction Fee.
// Memory Usage: 55.3 MB, less than 88.63% of C++ online submissions for Best Time to Buy and Sell Stock with Transaction Fee.
class Solution {
public:
    int maxProfit(std::vector<int>& prices, int fee) {
        if (prices.size() < 2) {
            return 0;
        }

        // Index 0.
        int ownRevenue = -prices[0] - fee;
        int notOwnRevenue = 0;

        for (size_t i = 1; i < prices.size(); i += 1) {
            const auto currentPrice = prices[i];
            std::tie(ownRevenue, notOwnRevenue) = std::make_tuple(
                std::max(ownRevenue, notOwnRevenue - currentPrice - fee),
                std::max(notOwnRevenue, ownRevenue + currentPrice)
            );
        }

        return notOwnRevenue;
    }
};


void test(const std::vector<int>& prices, const int fee, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto pricesCopy = prices;
    auto result = solutionInstance.maxProfit(pricesCopy, fee);
    if (result == expectedResult) {
        std::cout << "[Correct] " << prices << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << prices << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,3,2,8,4,9}, 2, 8);
    test({1,3,2,8,7,9,8,10}, 2, 7);

    return 0;
}
