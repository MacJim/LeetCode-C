/*
 * 15. 3Sum
 * https://leetcode.com/problems/3sum/
 */

#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

//MARK: 1
vector<vector<int>> threeSum(vector<int>& nums) {
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

int main() {
//    vector<int> testCase1 = {-1, 0, 1, 2, -1, -4, 0, 0};
    vector<int> testCase1 = {-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6};
    auto testResult1 = threeSum(testCase1);
    for (const auto& currentTriplet: testResult1) {
        cout << "Current triplet: ";
        for (const int& currentNumber: currentTriplet) {
            cout << currentNumber << " ";
        }
        cout << endl;
    }
    
    return 0;
}
