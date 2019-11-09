/*
 * 1. Two Sum
 * https://leetcode.com/problems/two-sum/
 */

/*
 * The input `nums` array is NOT sorted.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>

using namespace std;


class Solution {
public:
    // MARK: 1. This only works with sorted numbers
    vector<int> twoSum1(vector<int>& nums, int target) {
        auto numbersCount = nums.size();
        if (numbersCount <= 2) {
            return {0, 1};
        }

        // For the moment we think that the numbers are already sorted.
        vector<int> sortedNumbers = nums;
        // std::sort(sortedNumbers.begin(), sortedNumbers.end());

        // Find the largest number that is smaller than `target`.
        int initialBackIndex = numbersCount - 1;
        for (; initialBackIndex > 0; initialBackIndex -= 1) {    // Note that the back index must be larger than 0.
            int currentNumber = sortedNumbers.at(initialBackIndex);
            if (currentNumber < target) {
                // Choose this index as the initial backIndex.
                break;
            }
        }

        for (int backIndex = initialBackIndex; backIndex > 0; backIndex -= 1) {
            int backNumber = sortedNumbers.at(backIndex);
            for (int frontIndex = 0; frontIndex < backIndex; frontIndex += 1) {
                int frontNumber = sortedNumbers.at(frontIndex);

                int sum = frontNumber + backNumber;
                
                if (sum == target) {
                    return {frontIndex, backIndex};
                } else if (sum < target) {
                    // Try the enxt `frontNumber`.
                    continue;
                } else {
                    // The current `backNumber` does not work. Use the next one instead.
                    break;
                }
            }
        }

        return {0, 1};
    }


    // MARK: 2. Using a compliment map
    // Runtime: 8 ms, faster than 92.81% of C++ online submissions for Two Sum.
    // Memory Usage: 10.2 MB, less than 45.50% of C++ online submissions for Two Sum.
    vector<int> twoSum(vector<int>& nums, int target) {
        auto numbersCount = nums.size();
        if (numbersCount <= 2) {
            return {0, 1};
        }

        /// (value, index).
        unordered_map<int, int> complimentMap;

        for (int i = 0; i < numbersCount; i += 1) {
            const int currentNumber = nums[i];
            const int complimentNumber = target - currentNumber;

            const auto existingComplimentNumberInMap = complimentMap.find(complimentNumber);
            if (existingComplimentNumberInMap == complimentMap.end()) {
                // Its compliment number was not found.
                complimentMap.insert(make_pair(currentNumber, i));
            } else {
                // Its compliment number was found.
                return {existingComplimentNumberInMap->second, i};
            }
        }

        return {0, 1};
    }
};


int main(int argc, const char * argv[]) {
    unique_ptr<Solution> solutionInstance (new Solution());
    
    vector<int> testCase1 = {2, 7, 11, 15};
    for (const int& aValue: solutionInstance->twoSum(testCase1, 9)) {
        cout << aValue << " ";
    }
    cout << endl;
    
    vector<int> testCase2 = {3, 2, 4};
    for (const int& aValue: solutionInstance->twoSum(testCase2, 6)) {
        cout << aValue << " ";
    }
    cout << endl;

    return 0;
}
