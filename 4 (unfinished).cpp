/*
 * 4. Median of Two Sorted Arrays
 * https://leetcode.com/problems/median-of-two-sorted-arrays/
 */

#include <iostream>
#include <vector>


class Solution {
public:
    double findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2) {
        const auto len1 = nums1.size();
        const auto len2 = nums2.size();

        bool isEven = true;
        if ((len1 + len2) % 2 != 0) {
            isEven = false;    // Odd number: Let the second part have 1 more character than the first part.
        }

        int i1 = 0;    // Sadly I cannot use size_t here because it's unsigned.
        int i2 = len2 - 1;

        // Balance 2 part lengths.
        // Left: [0, i); right: [i, len)
        while (true) {
            int leftPartLength = i1 + i2;
            int rightPartLength = -i1 - i2 + len1 + len2;

            int delta = rightPartLength - leftPartLength;
            if (isEven) {
                if (delta > 0) {
                    // Right part is too long.
                    
                }
            }
        }
    }
};


void test(const std::vector<int>& nums1, const std::vector<int>& nums2) {
    static auto solutionInstance = Solution();
    auto result = solutionInstance.findMedianSortedArrays(nums1, nums2);
    std::cout << "Median: " << result << std::endl;
}

int main() {
    test({1, 2}, {3});    // 2
    test({1, 3}, {2});    // 2
    test({1, 2}, {3, 4});    // 2.5

    return 0;
}
