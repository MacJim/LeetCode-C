/*
 * 46. Permutations
 * https://leetcode.com/problems/permutations/
 */

#include <iostream>
#include <vector>


// Runtime: 4 ms, faster than 100.00% of C++ online submissions for Permutations.
// Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for Permutations.
class Solution {
private:
    void permuteRecursively(std::vector<int>& nums, const size_t numsSize, const size_t startID, std::vector<std::vector<int>>& result) {
        if (startID >= (numsSize - 1)) {
            // This is the final number.
            result.push_back(nums);
            return;
        }

        // Un-swapped.
        permuteRecursively(nums, numsSize, startID + 1, result);

        // Try to swap upcoming numbers with `startID`.
        for (size_t i = (startID + 1); i < numsSize; i += 1) {
            std::swap(nums.at(i), nums.at(startID));
            permuteRecursively(nums, numsSize, startID + 1, result);
            std::swap(nums.at(i), nums.at(startID));    // Restore the previous array.
        }
    }

public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        const auto len = nums.size();
        if (len == 0) {
            return {};
        }

        auto returnValue = std::vector<std::vector<int>>();
        permuteRecursively(nums, len, 0, returnValue);

        return returnValue;
    }
};


void test(std::vector<int> testCase) {
    static auto solutionInstance = Solution();
    auto results = solutionInstance.permute(testCase);
    for (const auto& aResult: results) {
        for (const auto& num: aResult) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<int> testCase1 = {1, 2, 3};
    test(testCase1);

    std::vector<int> testCase2 = {1, 2, 3, 4};
    test(testCase2);

    return 0;
}
