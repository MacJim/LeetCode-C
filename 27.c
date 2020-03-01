/*
 * 27. Remove Element
 * https://leetcode.com/problems/remove-element/
 */

#include <stdio.h>


// Runtime: 4 ms, faster than 67.60% of C online submissions for Remove Element.
// Memory Usage: 5.7 MB, less than 100.00% of C online submissions for Remove Element.
int removeElement(int* nums, int numsSize, int val) {
    if (numsSize == 0) {
        return 0;
    } else if (numsSize == 1) {
        // 1 element is a special case for this program.
        if (*nums == val) {
            return 0;
        } else {
            return 1;
        }
    }

    int i = 0;
    int j = numsSize - 1;    // j must be signed because we may have j = -1 values to help judge i <= j.

    // Preprocess. Move j back.
    while ((i <= j) && (*(nums + j) == val)) {
        j -= 1;
    }

    // Start. Move i forward.
    while (i <= j) {
        if (*(nums + i) == val) {
            *(nums + i) = *(nums + j);
            j -= 1;

            while ((i <= j) && (*(nums + j) == val)) {
                j -= 1;
            }
        }

        i += 1;
    }

    return (j + 1);
}


void test(int* nums, int numsSize, int val) {
    printf("Result: ");
    int result = removeElement(nums, numsSize, val);
    for (size_t i = 0; i < result; i += 1) {
        printf("%d ", *(nums + i));
    }
    printf("\n");
}

int main() {
    int nums1[] = {1, 2, 3, 4, 5};
    int len1 = 5;
    int val1 = 4;
    test(nums1, len1, val1);

    int nums2[] = {1, 2, 3, 4, 5};
    int len2 = 5;
    int val2 = 6;
    test(nums2, len2, val2);

    int nums3[] = {1};
    int len3 = 1;
    int val3 = 1;
    test(nums3, len3, val3);

    int nums4[] = {1, 2, 3, 4, 4, 4, 4, 5};
    int len4 = 8;
    int val4 = 4;
    test(nums4, len4, val4);

    int nums5[] = {4, 4, 4, 4};
    int len5 = 4;
    int val5 = 4;
    test(nums5, len5, val5);

    return 0;
}