/*
 * 322. Coin Change
 * https://leetcode.com/problems/coin-change/
 */


#include <iostream>
#include <vector>
#include <stack>
#include <memory>

using namespace std;


class Solution {
public:
    //MARK: 1. Recursion
    //Result: Time Limit Exceeded 😭😭😭... Perhaps there's a bug...
//    /**
//     * @param coins Must be sorted in ascending order.
//     */
//    int coinChangeRecursively(const vector<int>& coins, int amount) {
//        if (amount <= 0) {
//            return -1;
//        }
//
//        int returnValue = -1;
//
//        //Start from the biggest coin value.
//        for (auto currentCoinValueIterator = coins.rbegin(); currentCoinValueIterator != coins.rend(); currentCoinValueIterator += 1) {
//            int currentCoinValue = *currentCoinValueIterator;
//            if (currentCoinValue > amount) {
//                //We shall try a smaller coin value.
//                continue;
//            } else if (currentCoinValue == amount) {
//                //1 is already the smallest result.
//                return 1;
//            } else {
//                //The current coin value is smaller than `amount`. We shall try split the remaining with other coins.
//                int remainingResult = coinChangeRecursively(coins, amount - currentCoinValue);
//
//                if (remainingResult == -1) {
//                    //The remaining value cannot be divided.
//                    continue;
//                } else {
//                    int currentResult = remainingResult + 1;
//                    if ((returnValue == -1) || (currentResult < returnValue)) {
//                        returnValue = currentResult;
//                    }
//                }
//            }
//        }
//
//        return returnValue;
//    }
//
//    int coinChange(vector<int> coins, int amount) {
//        if (amount < 0) {
//            return -1;
//        }
//
//        if (coins.size() <= 0) {
//            return -1;
//        }
//
//        if (amount == 0) {
//            //Using 0 coins 😂.
//            return 0;
//        }
//
//        sort(coins.begin(), coins.end());
//        int smallestCoinValue = coins.front();
//        if (smallestCoinValue > amount) {
//            return -1;
//        }
//
//        return coinChangeRecursively(coins, amount);
//    }
    
    
    //MARK: 2. Another recursion algorithm.
    //Result: Wrong answer. The greedy algorithm might not produce correct answers...
//    int coinChangeRecursively(const vector<int>& coinValues, stack<int>& previouslyUsedCoinsIndexes, int remainingAmount) {
//        if (remainingAmount == 0) {
//            return 0;
//        }
//
//        int coinIndexToStartWith = coinValues.size() - 1;
//        if (!previouslyUsedCoinsIndexes.empty()) {
//            coinIndexToStartWith = previouslyUsedCoinsIndexes.top();
//        }
//
//        for (int i = coinIndexToStartWith; i >= 0; i -= 1) {
//            int currentCoinValue = coinValues.at(i);
//            if (currentCoinValue > remainingAmount) {
//                continue;
//            }
//
//            previouslyUsedCoinsIndexes.push(i);
//
//            int remainingResults = coinChangeRecursively(coinValues, previouslyUsedCoinsIndexes, remainingAmount - currentCoinValue);
//
//            if (remainingResults == -1) {
//                //Cannot find a remaining result. Try a smaller number.
//                previouslyUsedCoinsIndexes.pop();
//                continue;
//            } else {
//                return (remainingResults + 1);
//            }
//        }
//
//        //If no feasible numbers can be found.
//        return -1;
//    }
//
//    int coinChange(vector<int> coins, int amount) {
//        if (amount < 0) {
//            return -1;
//        }
//
//        if (coins.size() <= 0) {
//            return -1;
//        }
//
//        if (amount == 0) {
//            //Using 0 coins 😂.
//            return 0;
//        }
//
//        sort(coins.begin(), coins.end());
//        int smallestCoinValue = coins.front();
//        if (smallestCoinValue > amount) {
//            return -1;
//        }
//
//        // vector<int> coinUseTimes (coins.size(), 0);
//        stack<int> previouslyUsedCoinsIndexes;
//        // auto currentCoinValueIterator = coins.rbegin();
//
//        int returnValue = coinChangeRecursively(coins, previouslyUsedCoinsIndexes, amount);
//
//        while (!previouslyUsedCoinsIndexes.empty()) {
//            cout << previouslyUsedCoinsIndexes.top() << " ";
//            previouslyUsedCoinsIndexes.pop();
//        }
//
//        return returnValue;
//    }
    
    
    //MARK: 3. Step-by-step.
    //Runtime: 64 ms, faster than 27.59% of C++ online submissions for Coin Change.
    //Memory Usage: 19.1 MB, less than 21.57% of C++ online submissions for Coin Change.
    int coinChange(vector<int> coins, int amount) {
        if (amount < 0) {
            return -1;
        }

        if (coins.size() <= 0) {
            return -1;
        }

        if (amount == 0) {
            //Using 0 coins 😂.
            return 0;
        }

        sort(coins.begin(), coins.end());
        int smallestCoinValue = coins.front();
        int largestCoinValue = coins.back();

        if (smallestCoinValue > amount) {
            return -1;
        }

        vector<int> minimumCoinsRequired;

        int startCalculatingAmount = 0;
        if (!minimumCoinsRequired.empty()) {
            startCalculatingAmount = minimumCoinsRequired.size();
        }

        for (int currentAmount = startCalculatingAmount; currentAmount <= amount; currentAmount += 1) {
            if ((currentAmount <= largestCoinValue) && (std::find(coins.begin(), coins.end(), currentAmount) != coins.end())) {
                //The current amount equals a coin value.
                minimumCoinsRequired.push_back(1);
                continue;
            }
            
            minimumCoinsRequired.push_back(-1);
            
            for (int& aPossibleCoinValue: coins) {
                int correspondingPreviousAmount = currentAmount - aPossibleCoinValue;
                if (correspondingPreviousAmount <= 0) {
                    continue;
                }
                
                int previousCoinsCount = minimumCoinsRequired.at(correspondingPreviousAmount);
                if (previousCoinsCount == -1) {
                    //This previous position is not possible.
                    continue;
                }
                
                int currentCoinsCount = minimumCoinsRequired.at(currentAmount);
                if ((currentCoinsCount == -1) || (currentCoinsCount > (previousCoinsCount + 1))) {
                    minimumCoinsRequired.at(currentAmount) = previousCoinsCount + 1;
                }
            }
        }
        
        return minimumCoinsRequired.back();
    }
};

int main() {
    unique_ptr<Solution> solutionInstance (new Solution());

    cout << solutionInstance->coinChange({1, 2, 5}, 11) << endl;    // 3
    cout << solutionInstance->coinChange({2}, 3) << endl;    // -1
    cout << solutionInstance->coinChange({1, 2, 5}, 100) << endl;    // 20
    cout << solutionInstance->coinChange({1, 2, 5}, 103) << endl;    // 22
    cout << solutionInstance->coinChange({186, 419, 83, 408}, 6249) << endl;    // 20
    cout << solutionInstance->coinChange({1, 4, 5}, 8) << endl;    // 2

    return 0;
}
