/*
 * 213. House Robber II
 * https://leetcode.com/problems/house-robber-ii/
 */

/*
 * 1 <= nums.length <= 100
 * 0 <= nums[i] <= 1000
 */

#include <vector>
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. compare them and replace the initial value with the last value if the last value is larger
// WRONG ANSWER because the last value can be robbed along with the 1st value, while the 0th and 1st values cannot be robbed together.
class Solution1 {
public:
    int rob(std::vector<int>& nums) {
        auto size = nums.size();
        if (size == 1) {
            // We already know that the `nums` vector is not empty.
            return nums[0];
        }

        // Since we cannot choose both the initial and last houses, we compare them and replace the initial value with the last value if the last value is larger.
        if (nums.back() > nums.front()) {
            nums.front() = nums.back();
        }
        size -= 1;    // I don't want to modify the `nums` vector.

        // 0th house.
        int moneyWithCurrentHouse = nums[0];
        int moneyWithoutCurrentHouse = 0;
//        bool firstHouseRobbedWithCurrentHouse = true;
//        bool firstHouseRobbedWithoutCurrentHouse = false;

        // 1 ~ (size - 1).
        for (size_t i = 1; i < size; i += 1) {
            const int& currentMoney = nums[i];

            int newMoneyWithCurrentHouse = moneyWithoutCurrentHouse + currentMoney;
            int newMoneyWithoutCurrentHouse = std::max(moneyWithCurrentHouse, moneyWithoutCurrentHouse);

            moneyWithCurrentHouse = newMoneyWithCurrentHouse;
            moneyWithoutCurrentHouse = newMoneyWithoutCurrentHouse;

//            if (moneyWithCurrentHouse > moneyWithoutCurrentHouse) {
//                int newMoneyWithoutCurrentHouse = moneyWithCurrentHouse + currentMoney;
//            } else if (moneyWithCurrentHouse < moneyWithoutCurrentHouse) {
//                int newMoneyWithoutCurrentHouse = moneyWithoutCurrentHouse + currentMoney;
//            } else {
//                // They equal.
//                int newMoneyWithoutCurrentHouse = moneyWithCurrentHouse + currentMoney;
//            }
        }

        return std::max(moneyWithCurrentHouse, moneyWithoutCurrentHouse);
    }
};


#pragma mark - 2. Log "with/without first house" state
// WRONG ANSWER with {2,2,4,3,2,5}, 10
class Solution2 {
public:
    int rob(std::vector<int>& nums) {
        auto size = nums.size();
        if (size == 1) {
            // We already know that the `nums` vector is not empty.
            return nums[0];
        }

        // 0th house.
        const auto& zerothMoney = nums[0];

        int moneyWithCurrentHouse = zerothMoney;
        int moneyWithoutCurrentHouse = 0;
        bool firstHouseRobbedWithCurrentHouse = true;
        bool firstHouseRobbedWithoutCurrentHouse = false;

        // 1 ~ (size - 2).
        for (size_t i = 1; i <= (size - 2); i += 1) {
            const int& currentMoney = nums[i];

            // With current house: calculate new values.
            int newMoneyWithCurrentHouse = moneyWithoutCurrentHouse + currentMoney;
            bool newFirstHouseRobbedWithCurrentHouse = firstHouseRobbedWithoutCurrentHouse;

            // Without current house: calculate & assign new values.
            if (moneyWithCurrentHouse > moneyWithoutCurrentHouse) {
                moneyWithoutCurrentHouse = moneyWithCurrentHouse;
                firstHouseRobbedWithoutCurrentHouse = firstHouseRobbedWithCurrentHouse;
            } else if (moneyWithCurrentHouse < moneyWithoutCurrentHouse) {
                moneyWithoutCurrentHouse = moneyWithoutCurrentHouse;
                firstHouseRobbedWithoutCurrentHouse = firstHouseRobbedWithoutCurrentHouse;
            } else {
                // They equal.
                moneyWithoutCurrentHouse = moneyWithCurrentHouse;
                firstHouseRobbedWithoutCurrentHouse = firstHouseRobbedWithCurrentHouse && firstHouseRobbedWithoutCurrentHouse;    // Prefer the one that does not rob the first house.
            }

            // With current house: assign new values.
            moneyWithCurrentHouse = newMoneyWithCurrentHouse;
            firstHouseRobbedWithCurrentHouse = newFirstHouseRobbedWithCurrentHouse;
        }

        // Last house.
        const auto& lastMoney = nums.back();

        int moneyWithoutLastHouse = moneyWithCurrentHouse;

        if (firstHouseRobbedWithoutCurrentHouse) {
            // Cannot rob the last house because the 0th house was robbed.
            if (lastMoney > zerothMoney) {
                // The last house contains more money than the 0th house.
                // Replace 0th money with last.
                moneyWithCurrentHouse = moneyWithoutCurrentHouse + lastMoney - zerothMoney;
            } else {
                // The last house contains less money than the 0th house.
                moneyWithCurrentHouse = moneyWithoutCurrentHouse;
            }
        } else {
            moneyWithCurrentHouse = moneyWithoutCurrentHouse + lastMoney;
        }

        return std::max(moneyWithCurrentHouse, moneyWithoutLastHouse);
    }
};


#pragma mark - 3. Store total money with/without the 0th value separately (store 3 values)
// Runtime: 4 ms, faster than 48.85% of C++ online submissions for House Robber II.
// Memory Usage: 8.2 MB, less than 5.58% of C++ online submissions for House Robber II.
class Solution3 {
public:
    int rob(std::vector<int>& nums) {
        const auto size = nums.size();
        if (size == 1) {
            // We already know that the `nums` vector is not empty.
            return nums[0];
        }

        // 0th house.
        const auto& zerothMoney = nums[0];

        int moneyWithCurrentWithZeroth = zerothMoney;    // Must select the 0th house.
        int moneyWithoutCurrentWithZeroth = 0;    // May select the 0th house.
        int moneyWithCurrentWithoutZeroth = 0;    // Do not select the 0th house.
        int moneyWithoutCurrentWithoutZeroth = 0;    // Do not select the 0th house.

        // 1 ~ (size - 2).
        for (size_t i = 1; i <= (size - 2); i += 1) {
            const int& currentMoney = nums[i];

            // With current house: calculate new values.
            const int newMoneyWithCurrentWithZeroth = moneyWithoutCurrentWithZeroth + currentMoney;
            const int newMoneyWithCurrentWithoutZeroth = moneyWithoutCurrentWithoutZeroth + currentMoney;

            // Without current house: calculate & assign new values.
            moneyWithoutCurrentWithZeroth = std::max(moneyWithCurrentWithZeroth, moneyWithoutCurrentWithZeroth);
            moneyWithoutCurrentWithoutZeroth = std::max(moneyWithCurrentWithoutZeroth, moneyWithoutCurrentWithoutZeroth);

            // With current house: assign new values.
            moneyWithCurrentWithZeroth = newMoneyWithCurrentWithZeroth;
            moneyWithCurrentWithoutZeroth = newMoneyWithCurrentWithoutZeroth;
        }

        // Last house.
        const auto& lastMoney = nums.back();

        const int moneyWithLastHouse = moneyWithoutCurrentWithoutZeroth + lastMoney;
        const int moneyWithoutZeroth = std::max(moneyWithLastHouse, moneyWithCurrentWithoutZeroth);

        const int moneyWithZeroth = std::max(moneyWithCurrentWithZeroth, moneyWithoutCurrentWithZeroth);

        return std::max(moneyWithZeroth, moneyWithoutZeroth);
    }
};


#pragma mark - 4. Optimized 3
// Runtime: 4 ms, faster than 48.85% of C++ online submissions for House Robber II.
// Memory Usage: 8.3 MB, less than 5.58% of C++ online submissions for House Robber II.
class Solution {
public:
    int rob(std::vector<int>& nums) {
        const auto size = nums.size();
        if (size == 1) {
            // We already know that the `nums` vector is not empty.
            return nums[0];
        }

        auto moneyWithZeroth = std::vector<int>(size, 0);    // Rob the 0th house.
        auto moneyWithoutZeroth = std::vector<int>(size, 0);    // Do not rob the 0th house.

        // 0th & 1st house.
        const auto& zerothMoney = nums[0];

        moneyWithZeroth[0] = nums[0];
        moneyWithZeroth[1] = nums[0];    // Note that this one is 0. When we rob the 0th house, we can no longer rob the 1st house.
        moneyWithoutZeroth[1] = nums[1];

        // 2 ~ (size - 1).
        for (size_t i = 2; i < size; i += 1) {    // Length of `nums` < 100. No overflowing here.
            const auto& currentMoney = nums[i];
            moneyWithZeroth[i] = std::max(moneyWithZeroth[i - 1], moneyWithZeroth[i - 2] + currentMoney);
            moneyWithoutZeroth[i] = std::max(moneyWithoutZeroth[i - 1], moneyWithoutZeroth[i - 2] + currentMoney);
        }

        return std::max(moneyWithZeroth[size - 2], moneyWithoutZeroth.back());
    }
};


void test(const std::vector<int>& nums, int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.rob(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}

int main() {
    test({4,1,2,7,5,3,1}, 14);
    test({2,2,4,3,2,5}, 10);
    test({200,3,140,20,10}, 340);
    test({1,2,1,1}, 3);
    test({2, 3, 2}, 3);
    test({1, 2, 3, 1}, 4);
    test({6}, 6);
    test({3, 0, 0, 4, 1}, 7);

    return 0;
}
