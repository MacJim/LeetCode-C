/*
 * 15. 3Sum
 * https://leetcode.com/problems/3sum/
 */

/*
 * - This problem is quite different from 2 sum because it asks you to find ALL available triplets instead of just one.
 * - The input array is no longer unique.
 * - Returns numbers instead of indices.
 */

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;


class Solution {
#pragma mark - 1. Categorize
private:
    
public:
    // MARK: Unfinished
    // vector<vector<int>> threeSum1(vector<int>& nums) {
    //     const auto numbersCount = nums.size();

    //     // 1. Categorize: 0, positive, negative.
    //     /// Stores only the indices of 0.
    //     vector<int> zeroIndices = {};
    //     /// number, index.
    //     unordered_map<int, vector<int>> positiveNumbers;
    //     unordered_map<int, vector<int>> negativeNumbers;

    //     for (int i = 0; i < numbersCount; i += 1) {
    //         const int currentNumber = nums[i];

    //         if (currentNumber == 0) {
    //             zeroIndices.push_back(i);
    //         } else if (currentNumber > 0) {
    //             auto existingNumbers = positiveNumbers.find(currentNumber);
    //             if (existingNumbers == positiveNumbers.end()) {
    //                 vector<int> indices = {i};
    //                 positiveNumbers.insert(make_pair(currentNumber, indices));
    //             } else {
    //                 existingNumbers->second.push_back(i);
    //             }
    //         } else {
    //             auto existingNumbers = negativeNumbers.find(currentNumber);
    //             if (existingNumbers == negativeNumbers.end()) {
    //                 vector<int> indices = {i};
    //                 negativeNumbers.insert(make_pair(currentNumber, indices));
    //             } else {
    //                 existingNumbers->second.push_back(i);
    //             }
    //         }
    //     }

    //     // 2. Compute.
    //     vector<vector<int>> returnValue = {};

    //     // 2-1. 1 zero, 1 positive, 1 negative.
    //     for (const int& aZeroIndex: zeroIndices) {
    //         for (const auto& aPositiveNumberPair: positiveNumbers) {
    //             const int currentPositiveNumber = aPositiveNumberPair.first;
                
    //             // Find corresponding number in negative map.
    //             auto negativeNumberPair = negativeNumbers.find(-currentPositiveNumber);
    //             if (negativeNumberPair == negativeNumbers.end()) {
    //                 continue;
    //             }

    //             returnValue.push_back({negativeNumberPair->first, 0, aPositiveNumberPair.first});
    //         }
    //     }

    //     // 2-2. 1 positive, 2 negatives.
    //     for (const auto& aPositiveNumberPair: positiveNumbers) {
    //         const int currentPositiveNumber = aPositiveNumberPair.first;
    //         const vector<int> currentPositiveNumberInd = aPositiveNumberPair.second;


    //     }

    //     // 2-3. 2 positives, 1 negative.
        
        
    //     return returnValue;
    // }


    // MARK: Not finished.
    vector<vector<int>> threeSum2(vector<int>& nums) {
        const auto numbersCount = nums.size();

        // 1. Categorize: 0, positive, negative.
        /// The amount of 0s.
        int zerosCount;

        unordered_set<int> positiveNumbers1;
        /// All positive numbers that have appeared for more than twice.
        unordered_set<int> positiveNumbers2;

        unordered_set<int> negativeNumbers1;
        /// All negative numbers that have appeared for more than twice.
        unordered_set<int> negativeNumbers2;

        for (const auto& aNumber: nums) {
            if (aNumber == 0) {
                zerosCount += 1;
            } else if (aNumber > 0) {
                // Positive number.
                if (positiveNumbers1.find(aNumber) == positiveNumbers1.end()) {
                    // Not found in `positiveNumbers1`.
                    positiveNumbers1.insert(aNumber);
                } else {
                    if (positiveNumbers2.find(aNumber) == positiveNumbers2.end()) {
                        // Not found in `positiveNumbers2`.
                        positiveNumbers2.insert(aNumber);
                    }
                }
            } else {
                // Negative number.
                if (negativeNumbers1.find(aNumber) == negativeNumbers1.end()) {
                    // Not found in `negativeNumbers1`.
                    negativeNumbers1.insert(aNumber);
                } else {
                    if (negativeNumbers2.find(aNumber) == negativeNumbers2.end()) {
                        // Not found in `negativeNumbers2`.
                        negativeNumbers2.insert(aNumber);
                    }
                }
            }
        }

        // 2. Compute
        vector<vector<int>> returnValue = {};

        // 2-1. 1 zero, 1 positive, 1 negative.
        if (zerosCount > 0) {
            if (zerosCount >= 3) {
                // The 3 zeros special case.
                returnValue.push_back({0, 0, 0});
            }

            for (const int& aPositiveNumber: positiveNumbers1) {
                // Find corresponding negative number.
                if (negativeNumbers1.find(-aPositiveNumber) != negativeNumbers1.end()) {
                    // Found a corresponding negative number.
                    returnValue.push_back({-aPositiveNumber, 0, aPositiveNumber});
                }
            }
        }

        // 2-2. 1 positive, 2 negatives.
        for (const int& aPositiveNumber: positiveNumbers1) {
            const int expectedNegativeAmount = -aPositiveNumber;

            for (const auto& negativeNumber1: negativeNumbers1) {
                if (negativeNumber1 < expectedNegativeAmount) {
                    continue;
                }

                const int remainingNegativeNumber = expectedNegativeAmount - negativeNumber1;

                // if (negativeNumbers2.find(remainingNegativeNumber) )
            }
        }


        return returnValue;
    }


    // MARK: Not finished.
    vector<vector<int>> threeSum(vector<int>& nums) {
        const auto numbersCount = nums.size();

        // 1. Categorize: 0, positive, negative.
        /// The amount of 0s.
        int zerosCount = 0;

        /// All positive numbers that have appeared exactly once.
        vector<int> positiveNumbers1;
        /// All positive numbers that have appeared for more than twice.
        vector<int> positiveNumbers2;

        /// All negative numbers that have appeared exactly once.
        vector<int> negativeNumbers1;
        /// All negative numbers that have appeared for more than twice.
        vector<int> negativeNumbers2;

        for (const auto& aNumber: nums) {
            if (aNumber == 0) {
                zerosCount += 1;
            } else if (aNumber > 0) {
                // Positive number.
                if (std::find(positiveNumbers2.begin(), positiveNumbers2.end(), aNumber) == positiveNumbers2.end()) {
                    // This number has appeared less than twice.
                    const auto existingNumberIterator = std::find(positiveNumbers1.begin(), positiveNumbers1.end(), aNumber);
                    if (existingNumberIterator != positiveNumbers1.end()) {
                        positiveNumbers2.push_back(aNumber);
                        positiveNumbers1.erase(existingNumberIterator);
                    } else {
                        positiveNumbers1.push_back(aNumber);
                    }
                }
            } else {
                // Negative number.
                if (std::find(negativeNumbers2.begin(), negativeNumbers2.end(), aNumber) == negativeNumbers2.end()) {
                    // This number has appeared less than twice.
                    const auto existingNumberIterator = std::find(negativeNumbers1.begin(), negativeNumbers1.end(), aNumber);
                    if (existingNumberIterator != negativeNumbers1.end()) {
                        negativeNumbers2.push_back(aNumber);
                        negativeNumbers1.erase(existingNumberIterator);
                    } else {
                        negativeNumbers1.push_back(aNumber);
                    }
                }
            }
        }

        // 2. Compute
        vector<vector<int>> returnValue = {};

        // 2-1. 1 zero, 1 positive, 1 negative.
        if (zerosCount > 0) {
            // The 3 zeros special case.
            if (zerosCount >= 3) {
                returnValue.push_back({0, 0, 0});
            }

            for (const int& aPositiveNumber: positiveNumbers1) {
                // Find corresponding negative number.
                if (std::find(negativeNumbers1.begin(), negativeNumbers1.end(), -aPositiveNumber) != negativeNumbers1.end()) {
                    // Found a corresponding negative number.
                    returnValue.push_back({-aPositiveNumber, 0, aPositiveNumber});
                }
            }
        }

        // 2-2. 1 positive, 2 negatives.
        for (const int& aPositiveNumber: positiveNumbers1) {
            const int expectedNegativeAmount = -aPositiveNumber;

            // `negativeNumbers1` and `negativeNumbers1`.
            for (int i = 0; i <= (negativeNumbers1.size() / 2); i += 1) {
                int negativeNumber1 = negativeNumbers1[i];
                if (negativeNumber1 < expectedNegativeAmount) {
                    continue;
                }

                const int remainingNegativeNumber = expectedNegativeAmount - negativeNumber1;
                if (remainingNegativeNumber == negativeNumber1) {
                    // This number has only appeared once. Thus there's no solution.
                    continue;
                }

                const auto negativeNumber2Iterator = std::find(negativeNumbers1.begin(), negativeNumbers1.end(), remainingNegativeNumber);
                if (negativeNumber2Iterator != negativeNumbers1.end()) {
                    // Found a solution.
                    returnValue.push_back({*negativeNumber2Iterator, negativeNumber1, aPositiveNumber});
                }
            }

            // `negativeNumbers1` and `negativeNumbers2`.
            for (const auto& negativeNumber1: negativeNumbers1) {
                if (negativeNumber1 < expectedNegativeAmount) {
                    continue;
                }

                const int remainingNegativeNumber = expectedNegativeAmount - negativeNumber1;
                
                const auto negativeNumber2Iterator = std::find(negativeNumbers2.begin(), negativeNumbers2.end(), remainingNegativeNumber);
                if (negativeNumber2Iterator != negativeNumbers2.end()) {
                    // Found a solution.
                    returnValue.push_back({*negativeNumber2Iterator, negativeNumber1, aPositiveNumber});
                }
            }

            // `negativeNumbers2` and `negativeNumbers2`.
            for (int i = 0; i <= (negativeNumbers2.size() / 2); i += 1) {
                int negativeNumber1 = negativeNumbers2[i];
                if (negativeNumber1 < expectedNegativeAmount) {
                    continue;
                }

                const int remainingNegativeNumber = expectedNegativeAmount - negativeNumber1;

                const auto negativeNumber2Iterator = std::find(negativeNumbers2.begin(), negativeNumbers2.end(), remainingNegativeNumber);
                if (negativeNumber2Iterator != negativeNumbers2.end()) {
                    // Found a solution.
                    returnValue.push_back({*negativeNumber2Iterator, negativeNumber1, aPositiveNumber});
                }
            }
        }

        // 2-3. 1 negative, 2 positives.
        // for (const int& aNegativeNumber: neg)
        


        return returnValue;
    }
};


int main() {
    unique_ptr<Solution> solutionInstance (new Solution());

    vector<int> testCase1 = {-1, 0, 1, 2, -1, -4};    // [-1, 0, 1], [-1, -1, 2]
    for (const auto& aTriplet: solutionInstance->threeSum(testCase1)) {
        for (const int& aValue: aTriplet) {
            cout << aValue << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}
