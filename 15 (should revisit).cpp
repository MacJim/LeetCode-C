/*
 * 15. 3Sum
 * https://leetcode.com/problems/3sum/
 */

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <tuple>
#include <set>
#include <unordered_set>

using namespace std;


class Solution {
public:
    // MARK: 1
    // Wrong answer.
    vector<vector<int>> threeSum1(vector<int>& nums) {
        vector<vector<int>> zeroSumTriplets = {};
        
        //1. Separate positive and negative numbers.
        int numberOfZeros = 0;
        ///Key: number; value: occurrence count.
        map<int, int> positiveNumbers = {};
        map<int, int> negativeNumbers = {};
        
        for (const int aNumber: nums) {
            if (aNumber > 0) {
                if (positiveNumbers.find(aNumber) == positiveNumbers.end()) {
                    positiveNumbers.insert(pair<int, int>(aNumber, 1));
                } else {
                    positiveNumbers.at(aNumber) += 1;
                }
            } else if (aNumber < 0) {
                if (negativeNumbers.find(aNumber) == negativeNumbers.end()) {
                    negativeNumbers.insert(pair<int, int>(aNumber, 1));
                } else {
                    negativeNumbers.at(aNumber) += 1;
                }
            } else {
                numberOfZeros += 1;
            }
        }
        
        //2. Find (0, 0, 0).
        if (numberOfZeros >= 3) {
            zeroSumTriplets.push_back({0, 0, 0});
        }
        
        //3. Find (-a, 0, a).
        if (numberOfZeros > 0) {
            for (const auto& aPositiveNumberOccurrence: positiveNumbers) {
                int currentPositiveNumber = aPositiveNumberOccurrence.first;
                for (const auto& aNegativeNumberOccurrence: negativeNumbers) {
                    int currentNegativeNumber = aNegativeNumberOccurrence.first;
                    if ((currentPositiveNumber + currentNegativeNumber) == 0) {
                        zeroSumTriplets.push_back({currentPositiveNumber, 0, currentNegativeNumber});
                    }
                }
            }
        }
        
        //4. Find (-a, -b, c).
        //TODO: Currently this map is erroneous! I should have used tuples!
        map<int, tuple<int, int>> positiveNumbersToSearch = {};
        
        for (const auto& aNegativeNumberOccurrence: negativeNumbers) {
            int negativeNumber1 = aNegativeNumberOccurrence.first;
            int negativeNumberOccurrenceCount1 = aNegativeNumberOccurrence.second;
            
            for (const auto& anotherNegativeNumberOccurrence: negativeNumbers) {
                int negativeNumber2 = anotherNegativeNumberOccurrence.first;
                
                if ((negativeNumber1 == negativeNumber2) && (negativeNumberOccurrenceCount1 <= 1)) {
                    //If `negativeNumber1` and `negativeNumber2` are the same number, but this number only occured once.
                    continue;
                }
                
                int positiveNumberToSearch = -negativeNumber1 - negativeNumber2;
                if (positiveNumbersToSearch.find(positiveNumberToSearch) == positiveNumbersToSearch.end()) {
                    positiveNumbersToSearch.insert(pair<int, tuple<int, int>>(positiveNumberToSearch, make_tuple(negativeNumber1, negativeNumber2)));
                }
            }
        }
        
        for (const auto& positiveNumberInformation: positiveNumbersToSearch) {
            int positiveNumberToSearch = positiveNumberInformation.first;
            if (positiveNumbers.find(positiveNumberToSearch) != positiveNumbers.end()) {
                int positiveNumber1 = get<0>(positiveNumberInformation.second);
                int positiveNumber2 = get<1>(positiveNumberInformation.second);
                zeroSumTriplets.push_back({positiveNumberToSearch, positiveNumber1, positiveNumber2});
            }
        }
        
        //5. Find (-a, b, c).
        map<int, tuple<int, int>> negativeNumbersToSearch = {};
        
        for (const auto& aPositiveNumberOccurrence: positiveNumbers) {
            int positiveNumber1 = aPositiveNumberOccurrence.first;
            int positiveNumberOccurrenceCount1 = aPositiveNumberOccurrence.second;
            
            for (const auto& anotherPositiveNumberOccurrence: positiveNumbers) {
                int positiveNumber2 = anotherPositiveNumberOccurrence.first;
                
                if ((positiveNumber1 == positiveNumber2) && (positiveNumberOccurrenceCount1 <= 1)) {
                    //If `positiveNumber1` and `positiveNumber2` are the same number, but this number only occured once.
                    continue;
                }
                
                int negativeNumberToSearch = -positiveNumber1 - positiveNumber2;
                if (negativeNumbersToSearch.find(negativeNumberToSearch) == negativeNumbersToSearch.end()) {
                    negativeNumbersToSearch.insert(pair<int, tuple<int, int>>(negativeNumberToSearch, make_tuple(positiveNumber1, positiveNumber2)));
                }
            }
        }
        
        for (const auto& negativeNumberInformation: negativeNumbersToSearch) {
            int negativeNumberToSearch = negativeNumberInformation.first;
            if (negativeNumbers.find(negativeNumberToSearch) != negativeNumbers.end()) {
                int positiveNumber1 = get<0>(negativeNumberInformation.second);
                int positiveNumber2 = get<1>(negativeNumberInformation.second);
                zeroSumTriplets.push_back({negativeNumberToSearch, positiveNumber1, positiveNumber2});
            }
        }
        
        return zeroSumTriplets;
    }


    // MARK: 2. Use map cache
    // Runtime: 616 ms, faster than 5.01% of C++ online submissions for 3Sum.
    // Memory Usage: 24.5 MB, less than 7.06% of C++ online submissions for 3Sum.
    // Why is this so slow on the OJ? It's indeed very fast on my computer!!!
    std::vector<std::vector<int>> threeSum2(std::vector<int>& numbers) {
        auto numbersCount = numbers.size();

        // 1. Build the numbers appearances cache.
        /// number, count
        auto numbersAppearances = std::unordered_map<int, int>();
        for (const int& aNumber: numbers) {
            auto iterator = numbersAppearances.find(aNumber);
            if (iterator == numbersAppearances.end()) {
                // Not found.
                numbersAppearances.emplace(make_pair(aNumber, 1));
            } else {
                iterator->second += 1;
            }
        }

        // 2. Find triplets.
        std::set<std::vector<int>> returnValueCache;    // We can only use `set` rather than `unordered_set` here.
        for (auto& appearance1: numbersAppearances) {
            int targetValue = -appearance1.first;
            appearance1.second -= 1;

            for (auto& appearance2: numbersAppearances) {
                if (appearance2.second == 0) {
                    // This is the first value reduced to 0 occurrances.
                    continue;
                }

                appearance2.second -= 1;

                int remainingValue = targetValue - appearance2.first;
                auto possibleAppearance3Iterator = numbersAppearances.find(remainingValue);
                if (possibleAppearance3Iterator != numbersAppearances.end()) {
                    if (possibleAppearance3Iterator->second > 0) {    // This value's occurrance is not reduced to 0.
                        // Found a triplet.
                        std::vector<int> currentTriplet = {appearance1.first, appearance2.first, possibleAppearance3Iterator->first};
                        std::sort(currentTriplet.begin(), currentTriplet.end());
                        returnValueCache.insert(std::move(currentTriplet));
                    }
                }

                appearance2.second += 1;
            }

            appearance1.second += 1;
        }

        std::vector<std::vector<int>> returnValue = std::vector<std::vector<int>>(returnValueCache.begin(), returnValueCache.end());
        return returnValue;
    }


    // MARK: 3
    // In this solution we first sort the input and make sure that number1 < number2 < number3.
    // This solution is wrong in that it contains duplicate numbers.
    std::vector<std::vector<int>> threeSum3(std::vector<int>& numbers) {
        auto numbersCount = numbers.size();
        if (numbersCount < 3) {
            return {};
        }

        std::vector<std::vector<int>> returnValue;

        std::sort(numbers.begin(), numbers.end());

        for (int index1 = 0; index1 < (numbersCount - 2); index1 += 1) {
            int number1 = numbers.at(index1);
            for (int index2 = index1 + 1; index2 < (numbersCount - 1); index2 += 1) {
                int number2 = numbers.at(index2);
                int remainingNumber = -number1 - number2;
                for (int index3 = index2 + 1; index3 < numbersCount; index3 += 1) {
                    int number3 = numbers.at(index3);
                    if (number3 == remainingNumber) {
                        // Triplet found.
                        returnValue.push_back({number1, number2, number3});
                    } else if (number3 > remainingNumber) {
                        break;
                    }
                }
            }
        }

        return returnValue;
    }


    // MARK: 4. Optimized 3
    // Runtime: 96 ms, faster than 85.72% of C++ online submissions for 3Sum.
    // Memory Usage: 14.7 MB, less than 95.88% of C++ online submissions for 3Sum.
    std::vector<std::vector<int>> threeSum(std::vector<int>& numbers) {
        auto numbersCount = numbers.size();
        if (numbersCount < 3) {
            return {};
        }

        std::vector<std::vector<int>> returnValue;

        std::sort(numbers.begin(), numbers.end());

        for (int index1 = 0; index1 < (numbersCount - 2); index1 += 1) {
            int number1 = numbers.at(index1);
            int targetNumber = -number1;

            int index2 = index1 + 1;
            int index3 = numbersCount - 1;

            while (index2 < index3) {
                int number2 = numbers.at(index2);
                int number3 = numbers.at(index3);

                int currentSum = number2 + number3;
                if (currentSum > targetNumber) {
                    index3 -= 1;
                } else if (currentSum < targetNumber) {
                    index2 += 1;
                } else {
                    // A triplet has been found.
                    returnValue.push_back({number1, number2, number3});
                    
                    // Resolving duplicates of numbers 2 and 3.
                    do {
                        index2 += 1;
                    } while ((number2 == numbers.at(index2)) && (index2 < index3));
                    do {
                        index3 -= 1;
                    } while ((number3 == numbers.at(index3)) && (index2 < index3));
                }
            }

            // Resolving duplicates of number 1.
            while ((numbers.at(index1) == numbers.at(index1 + 1)) && (index1 < (numbersCount - 2))) {
                index1 += 1;
            }
        }

        return returnValue;
    }
};


int main() {
    auto solutionInstance = Solution();

//    vector<int> testCase1 = {-1, 0, 1, 2, -1, -4, 0, 0};
    vector<int> testCase1 = {-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6};    // Expected: [[-4,-2,6],[-4,0,4],[-4,1,3],[-4,2,2],[-2,-2,4],[-2,0,2]]
    auto testResult1 = solutionInstance.threeSum(testCase1);
    for (const auto& currentTriplet: testResult1) {
        cout << "Current triplet: ";
        for (const int& currentNumber: currentTriplet) {
            cout << currentNumber << " ";
        }
        cout << endl;
    }
    
    return 0;
}
