/*
 * 88. Merge Sorted Array
 * https://leetcode.com/problems/merge-sorted-array/
 */

#include <stdio.h>


// Runtime: 4 ms, faster than 75.82% of C online submissions for Merge Sorted Array.
// Memory Usage: 7.1 MB, less than 100.00% of C online submissions for Merge Sorted Array.
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    if (n == 0) {
        return;
    }
    if (m == 0) {
        memcpy(nums1, nums2, n * sizeof(int));
        return;
    }
    
    m -= 1;
    n -= 1;
    
    for (size_t i = (m + n + 1); i >= 0; i -= 1) {
        int num1 = nums1[m];
        int num2 = nums2[n];
        if (num1 <= num2) {
            nums1[i] = num2;
            n -= 1;
        } else {
            nums1[i] = num1;
            m -= 1;
        }
        
        if (n < 0) {
            break;
        }
        if (m < 0) {
            memcpy(nums1, nums2, (n + 1) * sizeof(int));
            break;
        }
    }
}


void test1() {
    int array1[] = {1, 2, 3, 0, 0, 0};
    int array2[] = {2, 5, 6};
    
    merge(array1, 6, 3, array2, 3, 3);
    
    for (int i = 0; i < 6; i += 1) {
        printf("%d ", *(array1 + i));
    }
    printf("\n");
}


void test2() {
    int array1[] = {0};
    int array2[] = {1};
    
    merge(array1, 1, 0, array2, 1, 1);
    
    for (int i = 0; i < 1; i += 1) {
        printf("%d ", *(array1 + i));
    }
    printf("\n");
}

void test3() {
    int array1[] = {2, 0};
    int array2[] = {1};
    
    merge(array1, 2, 1, array2, 1, 1);
    
    for (int i = 0; i < 2; i += 1) {
        printf("%d ", *(array1 + i));
    }
    printf("\n");
}


int main() {
    test1();
    test2();
    test3();
    
    return 0;
}
