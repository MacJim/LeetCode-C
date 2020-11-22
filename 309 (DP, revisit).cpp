/*
 * 309. Best Time to Buy and Sell Stock with Cooldown
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
 */

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

#include "helpers/Operators.hpp"

#define UNDEFINED_INDEX -1


#pragma mark - 1
// WRONG ANSWER: wrong segmentation of the prices.
class Solution1 {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }

        int returnValue = 0;

        /**
         * Delta between [start, end] and [start, end).
         *
         * There's no need to compare when this value is 0.
         */
        int previousDelta = 0;

        int startIndex = 0;
        int endIndex = UNDEFINED_INDEX;

        for (size_t i = 1; i < prices.size(); i += 1) {
            const auto& price = prices[i];
            const auto& previousPrice = prices[i - 1];

            if (price >= previousPrice) {
                if ((previousDelta > 0) && ((i - startIndex) == 1)) {
                    const int currentDelta = price - previousPrice;
                    if (currentDelta >= previousDelta) {
                        returnValue -= previousDelta;
                    } else {
                        returnValue -= currentDelta;
                    }
                }

                previousDelta = price - previousPrice;
                endIndex = i;
            } else {
                if (endIndex != UNDEFINED_INDEX) {
                    const int previousProfit = prices[endIndex] - prices[startIndex];
                    returnValue += previousProfit;

                    endIndex = UNDEFINED_INDEX;
                }

                startIndex = i;
            }
        }
        if (endIndex != UNDEFINED_INDEX) {
            const int lastProfit = prices[endIndex] - prices[startIndex];
            returnValue += lastProfit;
        }

        return returnValue;
    }
};


#pragma mark - 2. Official Solution: 3 arrays: own, justSold, canBuyAgain
/*
 * Arrays:
 *
 * - own: profit if currently owning the stock
 *   - can be negative
 * - justSold/cooldown: profit if selling at current price
 *   - cannot buy
 * - canBuyAgain: profit if sold at the previous price
 *   - can buy
 *
 * States: see `309.png`
 *
 * State at index 0:
 *
 * - own[0] = -price
 * - justSold = 0
 * - canBuyAgain = 0
 *
 * Notes:
 *
 * - Use negative values for purchases
 */
// Runtime: 4 ms, faster than 87.75% of C++ online submissions for Best Time to Buy and Sell Stock with Cooldown.
// Memory Usage: 11.6 MB, less than 51.48% of C++ online submissions for Best Time to Buy and Sell Stock with Cooldown.
class Solution2 {
public:
    int maxProfit(std::vector<int> &prices) {
        if (prices.size() < 2) {
            return 0;
        }

        auto own = std::vector<int>(prices.size(), 0);
        auto justSold = std::vector<int>(prices.size(), 0);
        auto canBuyAgain = std::vector<int>(prices.size(), 0);

        // 0th price.
        own[0] = -prices[0];

        for (size_t i = 1; i < prices.size(); i += 1) {
            const auto& currentPrice = prices[i];
            own[i] = std::max(canBuyAgain[i - 1] - currentPrice, own[i - 1]);
            justSold[i] = own[i - 1] + currentPrice;
            canBuyAgain[i] = std::max(justSold[i - 1], canBuyAgain[i - 1]);
        }

        return std::max(justSold.back(), canBuyAgain.back());
    }
};


#pragma mark - 3. Optimized 2
// Runtime: 4 ms, faster than 87.75% of C++ online submissions for Best Time to Buy and Sell Stock with Cooldown.
// Memory Usage: 11.5 MB, less than 51.48% of C++ online submissions for Best Time to Buy and Sell Stock with Cooldown.
class Solution {
public:
    int maxProfit(std::vector<int> &prices) {
        if (prices.size() < 2) {
            return 0;
        }

        int ownPrice = -prices[0];
        int justSoldPrice = 0;
        int canBuyAgainPrice = 0;

        for (size_t i = 1; i < prices.size(); i += 1) {
            const auto& currentPrice = prices[i];

            const int newOwnPrice = std::max(canBuyAgainPrice - currentPrice, ownPrice);
            const int newJustSoldPrice = ownPrice + currentPrice;
            const int newCanBuyAgainPrice = std::max(justSoldPrice, canBuyAgainPrice);

            ownPrice = newOwnPrice;
            justSoldPrice = newJustSoldPrice;
            canBuyAgainPrice = newCanBuyAgainPrice;
        }

        return std::max(justSoldPrice, canBuyAgainPrice);
    }
};


void test(const std::vector<int>& prices, int expectedResult) {
    static auto solutionInstance = Solution();

    auto pricesCopy = prices;
    auto result = solutionInstance.maxProfit(pricesCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << prices << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << prices << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({6,1,3,2,4,7}, 6);    // 1 ~ 7
    test({6,1,3,2,2,4,7}, 7);
    test({6,1,3,2,4,7,6,8}, 7);    // 1 ~ 8
    test({1, 4, 2}, 3);
    test({1,2,3,0,2}, 3);

    return 0;
}
