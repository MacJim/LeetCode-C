/*
 * 179. Largest Number
 * https://leetcode.com/problems/largest-number/
 */

/*
 * I over-complicated things :(
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. Sort string
// WRONG ANSWER on test case `test({432,43243}, "43243432");`
class Solution1 {
public:
    std::string largestNumber(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return std::to_string(nums[0]);
        }

        auto numStrings = std::vector<std::string>();
        for (const auto& num: nums) {
            numStrings.push_back(std::to_string(num));
        }

        std::sort(numStrings.begin(), numStrings.end(), [](const std::string& lhs, const std::string& rhs) {
            auto& l0 = lhs[0];
            auto& r0 = rhs[0];
            if (l0 == r0) {
                const auto minLen = std::min(lhs.size(), rhs.size());

                // Compare with each other.
                for (size_t i = 1; i < minLen; i += 1) {
                    if (lhs[i] == rhs[i]) {
                        continue;
                    } else {
                        return lhs[i] > rhs[i];
                    }
                }

                if (lhs.size() == rhs.size()) {
                    // The 2 strings equal.
                    return false;
                } else if (lhs.size() > rhs.size()) {
                    // Compare with `l0` (or `r0`).
                    return lhs[minLen] > l0;
                } else {
                    // Compare with `l0` (or `r0`).
                    return rhs[minLen] < l0;
                }
            } else {
                return l0 > r0;
            }
        });

        auto returnValue = std::string();
        for (const auto& numStr: numStrings) {
            returnValue += numStr;
        }

        return returnValue;
    }
};


#pragma mark - 2. Fixes 1
// WRONG ANSWER with `test({111311, 1113}, "1113111311");`.
class Solution2 {
public:
    std::string largestNumber(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return std::to_string(nums[0]);
        }

        auto numStrings = std::vector<std::string>();
        for (const auto& num: nums) {
            numStrings.push_back(std::to_string(num));
        }

        std::sort(numStrings.begin(), numStrings.end(), [](const std::string& lhs, const std::string& rhs) {
            auto& l0 = lhs[0];
            auto& r0 = rhs[0];
            if (l0 == r0) {
                const auto minLen = std::min(lhs.size(), rhs.size());

                // Compare with each other.
                for (size_t i = 1; i < minLen; i += 1) {
                    if (lhs[i] == rhs[i]) {
                        continue;
                    } else {
                        return lhs[i] > rhs[i];
                    }
                }

                if (lhs.size() == rhs.size()) {
                    // The 2 strings equal.
                    return false;
                } else if (lhs.size() > rhs.size()) {
                    // `lhs` is longer than `rhs`.
                    // Compare starting with `r0`.
                    size_t lIndex = minLen;
                    while (true) {
                        size_t rIndex = 0;

                        for (; (lIndex < lhs.size()) && (rIndex < rhs.size()); lIndex += 1, rIndex += 1) {
                            if (lhs[lIndex] == rhs[rIndex]) {
                                continue;
                            } else {
                                return lhs[lIndex] > rhs[rIndex];
                            }
                        }

                        if ((lIndex == lhs.size()) && (rIndex == rhs.size())) {
                            // `lhs` contains duplicates of `rhs`.
                            return false;
                        } else if (lIndex == lhs.size()) {
                            return lhs.back() > rhs[rIndex];
                        }
                    }
                } else {
                    // `rhs` is longer than `lhs`.
                    // Compare starting with `l0`.
                    size_t rIndex = minLen;
                    while (true) {
                        size_t lIndex = 0;

                        for (; (lIndex < lhs.size()) && (rIndex < rhs.size()); lIndex += 1, rIndex += 1) {
                            if (lhs[lIndex] == rhs[rIndex]) {
                                continue;
                            } else {
                                return lhs[lIndex] > rhs[rIndex];
                            }
                        }

                        if ((lIndex == lhs.size()) && (rIndex == rhs.size())) {
                            // `rhs` contains duplicates of `lhs`.
                            return false;
                        } else if (rIndex == rhs.size()) {
                            return lhs[lIndex] > rhs.back();
                        }
                    }
                }
            } else {
                return l0 > r0;
            }
        });

        auto returnValue = std::string();
        for (const auto& numStr: numStrings) {
            returnValue += numStr;
        }

        return returnValue;
    }
};


#pragma mark - 3. Fixes 2 (unfinished)
class Solution3 {
public:
    std::string largestNumber(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return std::to_string(nums[0]);
        }

        auto numStrings = std::vector<std::string>();
        for (const auto& num: nums) {
            numStrings.push_back(std::to_string(num));
        }

        std::sort(numStrings.begin(), numStrings.end(), [](const std::string& lhs, const std::string& rhs) {
            auto& l0 = lhs[0];
            auto& r0 = rhs[0];
            if (l0 == r0) {
                const auto minLen = std::min(lhs.size(), rhs.size());

                // Compare with each other.
                for (size_t i = 1; i < minLen; i += 1) {
                    if (lhs[i] == rhs[i]) {
                        continue;
                    } else {
                        return lhs[i] > rhs[i];
                    }
                }

                if (lhs.size() == rhs.size()) {
                    // The 2 strings equal.
                    return false;
                } else if (lhs.size() > rhs.size()) {
                    // `lhs` is longer than `rhs`.
                    // Compare starting with `r0`.
                    size_t lIndex = minLen;
                    while (true) {
                        size_t rIndex = 0;

                        for (; (lIndex < lhs.size()) && (rIndex < rhs.size()); lIndex += 1, rIndex += 1) {
                            if (lhs[lIndex] == rhs[rIndex]) {
                                continue;
                            } else {
                                return lhs[lIndex] > rhs[rIndex];
                            }
                        }

                        if ((lIndex == lhs.size()) && (rIndex == rhs.size())) {
                            // `lhs` contains duplicates of `rhs`.
                            return false;
                        } else if (lIndex == lhs.size()) {
                            // Compare `lhs.back()` with the remaining characters in `rhs`.
                            for (; rIndex < rhs.size(); rIndex += 1) {
                                if (lhs.back() == rhs[rIndex]) {
                                    continue;
                                } else {
                                    return lhs.back() > rhs[rIndex];
                                }
                            }

                            return false;
                        }
                    }
                } else {
                    // `rhs` is longer than `lhs`.
                    // Compare starting with `l0`.
                    size_t rIndex = minLen;
                    while (true) {
                        size_t lIndex = 0;

                        for (; (lIndex < lhs.size()) && (rIndex < rhs.size()); lIndex += 1, rIndex += 1) {
                            if (lhs[lIndex] == rhs[rIndex]) {
                                continue;
                            } else {
                                return lhs[lIndex] > rhs[rIndex];
                            }
                        }

                        if ((lIndex == lhs.size()) && (rIndex == rhs.size())) {
                            // `rhs` contains duplicates of `lhs`.
                            return false;
                        } else if (rIndex == rhs.size()) {
                            // Compare `rhs.back()` with the remaining characters in `lhs`.
                            for (; lIndex < lhs.size(); lIndex += 1) {
                                if (lhs[lIndex] > rhs.back()) {
                                    continue;
                                } else {
                                    return lhs[lIndex] > rhs.back();
                                }
                            }
                            return false;
                        }
                    }
                }
            } else {
                return l0 > r0;
            }
        });

        auto returnValue = std::string();
        for (const auto& numStr: numStrings) {
            returnValue += numStr;
        }

        return returnValue;
    }
};


#pragma mark - 4. Just add the 2 strings together and compare (revisit)
// It was I who devised this solution. But it's worth re-visiting because of the time and effort wasted in previous solutions.
// Runtime: 8 ms, faster than 69.72% of C++ online submissions for Largest Number.
// Memory Usage: 11.5 MB, less than 16.66% of C++ online submissions for Largest Number.
class Solution {
public:
    std::string largestNumber(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return std::to_string(nums[0]);
        }

        auto numStrings = std::vector<std::string>();
        for (const auto& num: nums) {
            numStrings.push_back(std::to_string(num));
        }

        std::sort(numStrings.begin(), numStrings.end(), [](const std::string& lhs, const std::string& rhs) {
            const auto s1 = lhs + rhs;
            const auto s2 = rhs + lhs;

            for (size_t i = 0; i < s1.size(); i += 1) {
                if (s1[i] == s2[i]) {
                    continue;
                } else {
                    return s1[i] > s2[i];
                }
            }

            return false;
        });

        auto returnValue = std::string();
        for (const auto& numStr: numStrings) {
            // We don't want leading 0s.
            if ((!returnValue.empty()) || (numStr != "0")) {
                returnValue += numStr;
            }
        }

        if (returnValue.empty()) {
            returnValue = "0";
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const std::string& expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.largestNumber(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({0,0}, "0");
    test({111311, 1113}, "1113111311");
    test({113111, 11311}, "11311113111");
    test({432,43243}, "43243432");
    test({432,43241}, "43243241");
    test({432,43243243}, "43243243432");
    test({432,43243241}, "43243243241");
    test({444, 444333555}, "444444333555");
    test({1,2,3,4,5,6,7,8}, "87654321");
    test({10,2}, "210");
    test({3,30,34,5,9}, "9534330");
    test({1}, "1");
    test({10}, "10");

    return 0;
}
