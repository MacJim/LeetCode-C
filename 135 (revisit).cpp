/*
 * 135. Candy
 * https://leetcode.com/problems/candy/
 */

#include <iostream>
#include <vector>
#include <numeric>    // std::accumulate
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. Two passes
// WRONG ANSWER because elements larger than both its previous and next are counted twice.
class Solution1 {
public:
    int candy(std::vector<int>& ratings) {
        if (ratings.empty()) {
            return 0;
        } else if (ratings.size() == 1) {
            return 1;
        }

        int returnValue = ratings.size();    // At least 1 candy for every person.

        // Forward pass.
        int currentBonus = 0;    // Bonus means "additional candies for this person", and is 0 for minimum/equally rated persons.
        for (int i = 1; i < ratings.size(); i += 1) {
            const auto& currentRating = ratings[i];
            const auto& previousRating = ratings[i - 1];
            if (previousRating < currentRating) {
                currentBonus += 1;
                returnValue += currentBonus;
            } else {
                currentBonus = 0;
            }
        }

        // Backward pass.
        currentBonus = 0;
        for (int i = (ratings.size() - 2); i >= 0; i -= 1) {
            const auto& currentRating = ratings[i];
            const auto& previousRating = ratings[i + 1];
            if (previousRating < currentRating) {
                currentBonus += 1;
                returnValue += currentBonus;
            } else {
                currentBonus = 0;
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Fixed 1 using 2 arrays
// Runtime: 32 ms, faster than 94.35% of C++ online submissions for Candy.
// Memory Usage: 18.6 MB, less than 23.89% of C++ online submissions for Candy.
class Solution2 {
public:
    int candy(std::vector<int>& ratings) {
        if (ratings.empty()) {
            return 0;
        } else if (ratings.size() == 1) {
            return 1;
        }

        int returnValue = ratings.size();    // At least 1 candy for every person.

        // Forward pass.
        int currentBonus = 0;    // Bonus means "additional candies for this person", and is 0 for minimum/equally rated persons.
        auto forwardBonuses = std::vector<int>(ratings.size(), 0);
        for (int i = 1; i < ratings.size(); i += 1) {
            const auto& currentRating = ratings[i];
            const auto& previousRating = ratings[i - 1];
            if (previousRating < currentRating) {
                currentBonus += 1;
                forwardBonuses[i] = currentBonus;
            } else {
                currentBonus = 0;
            }
        }

        // Backward pass.
        currentBonus = 0;
        auto backwardBonuses = std::vector<int>(ratings.size(), 0);
        for (int i = (ratings.size() - 2); i >= 0; i -= 1) {
            const auto& currentRating = ratings[i];
            const auto& previousRating = ratings[i + 1];
            if (previousRating < currentRating) {
                currentBonus += 1;
                backwardBonuses[i] = currentBonus;
            } else {
                currentBonus = 0;
            }
        }

        // Calculate max between the 2 passes.
        for (size_t i = 0; i < ratings.size(); i += 1) {
            if (forwardBonuses[i] > backwardBonuses[i]) {
                returnValue += forwardBonuses[i];
            } else {
                returnValue += backwardBonuses[i];
            }
        }

        return returnValue;
    }
};


#pragma mark - 3. Optimized 2 using a single array
// Runtime: 44 ms, faster than 20.69% of C++ online submissions for Candy.
// Memory Usage: 18 MB, less than 63.13% of C++ online submissions for Candy.
class Solution3 {
public:
    int candy(std::vector<int>& ratings) {
        if (ratings.empty()) {
            return 0;
        } else if (ratings.size() == 1) {
            return 1;
        }

        auto candies = std::vector<int>(ratings.size(), 1);    // At least 1 candy for every person.

        // Forward pass.
        for (int i = 1; i < ratings.size(); i += 1) {
            const auto& currentRating = ratings[i];
            const auto& previousRating = ratings[i - 1];
            if (previousRating < currentRating) {
                candies[i] = candies[i - 1] + 1;
            }
        }

        // Backward pass.
        for (int i = (ratings.size() - 2); i >= 0; i -= 1) {
            const auto& currentRating = ratings[i];
            const auto& previousRating = ratings[i + 1];
            if (previousRating < currentRating) {
                candies[i] = std::max(candies[i], candies[i + 1] + 1);
            }
        }

        return std::accumulate(candies.begin(), candies.end(), 0);
    }
};


#pragma mark - 4. Mocking the LeetCode official O(n) solution
/*
 * Note that:
 *
 * - "Valley" children always get 1 candy
 * - Distances between the 2 valleys and the peak determines the peak value
 * - Total candies between valley and peak: n * (n + 1) / 2
 */
// WRONG ANSWER.
// Do not just set the current candy count to 1 if (rating == previousRating) because the next child may have even less candy.
class Solution4 {
public:
    int candy(std::vector<int>& ratings) {
        if (ratings.empty()) {
            return 0;
        } else if (ratings.size() == 1) {
            return 1;
        }

        int returnValue = 0;

        int previousRating = -1;
        /// Includes the peak.
        int upHillLength = 0;
        /// Includes the peak.
        int downHillLength = 0;

        /// `true` if going up hill; `false` if going down hill.
        bool isClimbing = true;

        // Main loop.
        for (const auto& rating: ratings) {
            if (isClimbing) {
                // Currently going uphill.
                if (rating < previousRating) {
                    // Go downhill.
                    isClimbing = false;
                    downHillLength = 2;    // Include the peak point.
                } else if (rating == previousRating) {
                    // Regard the current rating as a valley.
                    const int upHillCandies = upHillLength * (upHillLength + 1) / 2;
                    const int downHillCandies = 1;
                    const int totalCandies = upHillCandies + downHillCandies - 1;    // The latter valley will also be counted in the next mountain.
                    returnValue += totalCandies;

                    upHillLength = 1;
                } else {
                    upHillLength += 1;
                }
            } else {
                // Currently going downhill.
                if (rating > previousRating) {
                    // Calculate the previous mountain size.
                    if (upHillLength > downHillLength) {
                        const int upHillCandies = upHillLength * (upHillLength + 1) / 2;
                        const int downHillCandies = (downHillLength - 1) * downHillLength / 2;
                        const int totalCandies = upHillCandies + downHillCandies - 1;    // The latter valley will also be counted in the next mountain.
                        returnValue += totalCandies;
                    } else {
                        const int upHillCandies = (upHillLength - 1) * upHillLength / 2;
                        const int downHillCandies = downHillLength * (downHillLength + 1) / 2;
                        const int totalCandies = upHillCandies + downHillCandies - 1;    // The latter valley will also be counted in the next mountain.
                        returnValue += totalCandies;
                    }

                    // Switch to the next climbing session.
                    isClimbing = true;
                    upHillLength = 2;
                } else if (rating == previousRating) {
                    // Regard the current rating as a valley.
                    downHillLength += 1;

                    if (upHillLength > downHillLength) {
                        const int upHillCandies = upHillLength * (upHillLength + 1) / 2;
                        const int downHillCandies = (downHillLength - 1) * downHillLength / 2;
                        const int totalCandies = upHillCandies + downHillCandies - 1;    // The latter valley will also be counted in the next mountain.
                        returnValue += totalCandies;
                    } else {
                        const int upHillCandies = (upHillLength - 1) * upHillLength / 2;
                        const int downHillCandies = downHillLength * (downHillLength + 1) / 2;
                        const int totalCandies = upHillCandies + downHillCandies - 1;    // The latter valley will also be counted in the next mountain.
                        returnValue += totalCandies;
                    }

                    isClimbing = true;
                    upHillLength = 1;
                } else {
                    downHillLength += 1;
                }
            }

            previousRating = rating;
        }

        // The final climb or descent.
        if (isClimbing) {
            const int finalUpHillCandies = upHillLength * (upHillLength + 1) / 2;
            returnValue += finalUpHillCandies;
        } else {
            if (upHillLength > downHillLength) {
                const int upHillCandies = upHillLength * (upHillLength + 1) / 2;
                const int downHillCandies = (downHillLength - 1) * downHillLength / 2;
                const int totalCandies = upHillCandies + downHillCandies;    // Unlike the main loop, this time we count the final candy.
                returnValue += totalCandies;
            } else {
                const int upHillCandies = (upHillLength - 1) * upHillLength / 2;
                const int downHillCandies = downHillLength * (downHillLength + 1) / 2;
                const int totalCandies = upHillCandies + downHillCandies;    // Unlike the main loop, this time we count the final candy.
                returnValue += totalCandies;
            }
        }

        return returnValue;    // The final valley is not counted.
    }
};


#pragma mark - 5. Mocking the LeetCode official O(n) solution (revisit)
/*
 * - Levelling children are considered separately: in this problem, we try to give them 1 candy if they're equal to or smaller than its adjacent children.
 * - All valleys except for the first one and the last one are counted twice. So we need to subtract the final value with (number of mountains - 1).
 */
// Runtime: 40 ms, faster than 43.73% of C++ online submissions for Candy.
// Memory Usage: 17.5 MB, less than 91.45% of C++ online submissions for Candy.
class Solution {
protected:
    static inline int count(int length) {
        return (length * (length + 1) / 2);
    }

public:
    int candy(std::vector<int>& ratings) {
        if (ratings.empty()) {
            return 0;
        } else if (ratings.size() == 1) {
            return 1;
        }

        int returnValue = 0;

        /// Not including the peak.
        int upCount = 0;
        /// Not including the peak.
        int downCount = 0;

        /// 1: up, 0: level, -1: down.
        int oldSlope = 0;

        for (size_t i = 1; i < ratings.size(); i += 1) {
            const int newSlope = (ratings[i] > ratings[i - 1]) ? 1 : ((ratings[i] < ratings[i - 1]) ? -1 : 0);

            if (((oldSlope > 0) && (newSlope == 0)) || ((oldSlope < 0) && (newSlope >= 0))) {
                /*
                 * A new mountain is formed when:
                 *
                 * - Go level from up or down
                 * - Go up from down
                 */
                returnValue += count(upCount);    // Uphill total (not counting the peak).
                returnValue += count(downCount);    // Downhill total (not counting the peak).
                returnValue += std::max(upCount, downCount);    // The peak's value minus 1. The -1 here compensates for the valley being counted again in another mountain.

                upCount = 0;
                downCount = 0;
            }

            if (newSlope > 0) {
                upCount += 1;
            }
            if (newSlope < 0) {
                downCount += 1;
            }
            if (newSlope == 0) {
                returnValue += 1;    // Levelling children get 1 candy each.
            }

            oldSlope = newSlope;
        }

        returnValue += count(upCount);
        returnValue += count(downCount);
        returnValue += std::max(upCount, downCount);
        returnValue += 1;    // The smallest point won't be added again, so there's no need to compensate for that.

        return returnValue;
    }
};


void test(const std::vector<int>& ratings, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto ratingsCopy = ratings;
    auto result = solutionInstance.candy(ratingsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << ratings << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << ratings << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,4,5,3,2,1,2,6,5,4,3,3,2,1,1,3,3,3,4,2}, 47);
    test({2, 1, 1, 1, 2}, 7);
    test({1, 1, 1, 1, 1}, 5);
    test({29,51,87,87,72,12}, 12);
    test({1,0,2}, 5);
    test({1,2,2}, 4);
    test({1,3,2,2,1}, 7);
    test({5,4,3,2,1}, 15);
    test({1,2,3,4,5}, 15);
    test({1,2,3,3,2}, 9);

    return 0;
}
