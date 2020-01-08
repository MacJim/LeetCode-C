/*
 * 70. Climbing Stairs
 * https://leetcode.com/problems/climbing-stairs/
 */

#include <iostream>
#include <vector>


// MARK: - 1. Standard recursion
// Time limit exceeded.
class Solution1 {
public:
    int climbStairs(int n) {
        if (n <= 1) {
            return 1;
        }
        if (n == 2) {
            return 2;
        }
        
        return (climbStairs(n - 1) + climbStairs(n - 2));
    }
};


// MARK: - 2. Cache
// Runtime: 4 ms, faster than 53.13% of C++ online submissions for Climbing Stairs.
// Memory Usage: 8.3 MB, less than 83.82% of C++ online submissions for Climbing Stairs.
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 1) {
            return 1;
        }
        if (n == 2) {
            return 2;
        }
        
        static std::vector<int> cache = {1, 2};
        
        auto currentChacheSize = cache.size();
        if (n >= currentChacheSize) {
            // Calculate all the way up to `n`.
            cache.resize(n);
            for (size_t i = currentChacheSize; i < n; i += 1) {
                cache.at(i) = cache.at(i - 2) + cache.at(i - 1);
            }
        }
        
        return cache.at(n - 1);
    }
};


int main() {
    auto solutionInstance = Solution();
    std::cout << solutionInstance.climbStairs(3) << std::endl;    // 3
    std::cout << solutionInstance.climbStairs(2) << std::endl;    // 2
    std::cout << solutionInstance.climbStairs(4) << std::endl;    // 5
    std::cout << solutionInstance.climbStairs(34) << std::endl;    // 9227465
    
    return 0;
}
