/*
 * 31. Next Permutation
 * https://leetcode.com/problems/next-permutation/
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;


class Solution {
public:
    // MARK: This implementation was not finished.
    void nextPermutation1(vector<int>& nums) {
        auto numbersCount = nums.size();
        if (numbersCount <= 1) {
            return;
        }

        // Scan from right to left.
        bool nextPermutationFound = false;
        int smallestNumber = -1;
        int smallestNumberIndex = -1;
        for (int i = (numbersCount - 1); i >= 0; i -= 1) {
            int currentNumber = nums.at(i);
            if (currentNumber < smallestNumber) {
                // Numbers are increasing.
                smallestNumber = currentNumber;
                smallestNumberIndex = i;
            } else if (currentNumber > smallestNumber) {
                // Next permutation found.
                nextPermutationFound = true;
                std::swap(nums[i], nums[smallestNumberIndex]);
                
                // easySort(nums, i + 1);
                std::sort(nums.begin() + i + 1, nums.end(), [](const int& left, const int& right) {
                    return left < right;
                });
            }
        }

        if (!nextPermutationFound) {
            // Sort from largest to smallest.
            std::sort(nums.begin(), nums.end(), [](const int& left, const int& right) {
                return left > right;
            });
        }
    }

    /// `startIndex` is inclusive.
    // void easySort(vector<int>& nums, int startIndex) {
    //     auto numbersCount = nums.size();
    //     auto validNumbersCount = numbersCount - startIndex;
    //     if (validNumbersCount <= 1) {
    //         return;
    //     }

    //     for (int i = startIndex; i < (numbersCount - 1); i += 1) {
    //         if (nums.at(i) > nums.at(i + 1)) {
    //             std::swap(nums[i], nums[i + 1]);
    //         } else {
    //             break;
    //         }
    //     }
    // }


    // MARK: 2. Start from the back.
    // Runtime: 8 ms, faster than 76.13% of C++ online submissions for Next Permutation.
    // Memory Usage: 8.7 MB, less than 81.72% of C++ online submissions for Next Permutation.
    void nextPermutation(vector<int>& nums) {
        auto numbersCount = nums.size();
        if (numbersCount <= 1) {
            return;
        }

        /// Positions of numbers.
        unordered_map<int, int> numbersAppearances;

        // Start from the back.
        int i = numbersCount - 1;
        for (; i > 0; i -= 1) {
            int currentNumber = nums.at(i);
            // Save the index of the current number if it has not appearred.
            // Note that we only save the first (backmost) occurrance because we will reverse this part in the final step.
            if (numbersAppearances.find(currentNumber) == numbersAppearances.end()) {
                numbersAppearances.insert(make_pair(currentNumber, i));
            }

            int previousNumber = nums.at(i - 1);

            if (previousNumber < currentNumber) {
                // Find the number which is just larger than `previousNumber`.
                for (int j = previousNumber + 1; ; j += 1) {
                    auto possibleIterator = numbersAppearances.find(j);
                    if (possibleIterator == numbersAppearances.end()) {
                        // `j` doesn't exist in the previous streak.
                        continue;
                    } else {
                        // Found that number. Swap them.
                        std::swap(nums[possibleIterator->second], nums[i - 1]);
                        break;
                    }
                }

                std::reverse(nums.begin() + i, nums.end());

                return;
            }
        }

        // The given permutation is the largest permutation.
        std::sort(nums.begin(), nums.end());
    }
};

void test(vector<int> testCase) {
    static Solution* solutionInstance = new Solution();

    solutionInstance->nextPermutation(testCase);    // In place.
    for (const auto& anElement: testCase) {
        cout << anElement << " ";
    }
    cout << endl;
}

int main() {
    unique_ptr<Solution> solutionInstance (new Solution());

    test({1, 2, 3});    // 1,3,2
    test({3, 2, 1});    // 1,2,3
    test({1, 1, 5});    // 1,5,1
    test({1, 2, 3, 5, 4, 3});    // 1,2,4,3,3,5
    test({2,3,1,3,3});    // 2,3,3,1,3
    test({16,27,25,23,25,16,12,9,1,2,7,20,19,23,16,0,6,22,16,11,8,27,9,2,20,2,13,7,25,29,12,12,18,29,27,13,16,1,22,9,3,21,29,14,7,8,14,5,0,23,16,1,20});

    return 0;
}
