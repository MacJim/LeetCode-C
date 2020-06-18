/*
 * 121. Best Time to Buy and Sell Stock
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 */

#include <iostream>
#include <vector>


#pragma mark - 1
// Runtime: 12 ms, faster than 63.14% of C++ online submissions for Best Time to Buy and Sell Stock.
// Memory Usage: 13.3 MB, less than 15.45% of C++ online submissions for Best Time to Buy and Sell Stock.
class Solution1 {
public:
    int maxProfit(std::vector<int>& prices) {
        const auto len = prices.size();
        if (len <= 1) {
            return 0;
        }

        int returnValue = 0;

        int purchasePrice = prices.front();

        for (size_t i = 1; i < len; i += 1) {
            const int& price = prices.at(i);
            if (price < purchasePrice) {
                purchasePrice = price;
            } else {
                const int profit = price - purchasePrice;
                returnValue = std::max(returnValue, profit);
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Optimized 1
// Runtime: 12 ms, faster than 63.14% of C++ online submissions for Best Time to Buy and Sell Stock.
// Memory Usage: 13.2 MB, less than 19.32% of C++ online submissions for Best Time to Buy and Sell Stock.
class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        const auto len = prices.size();
        if (len <= 1) {
            return 0;
        }

        int returnValue = 0;

        int purchasePrice = INT_MAX;

        for (const auto& price: prices) {
            if (price < purchasePrice) {
                purchasePrice = price;
            } else {
                const int profit = price - purchasePrice;
                returnValue = std::max(returnValue, profit);
            }
        }
        
        return returnValue;
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<int> testCase1 = {7,1,5,3,6,4};
    std::cout << solutionInstance.maxProfit(testCase1) << std::endl;    // 5

    std::vector<int> testCase2 = {7,6,4,3,1};
    std::cout << solutionInstance.maxProfit(testCase2) << std::endl;    // 0

    return 0;
}
