/*
 * 646. Maximum Length of Pair Chain
 * https://leetcode.com/problems/maximum-length-of-pair-chain/
 */

/*
 * This problem is different from problem 300 because we can select pairs in any order.
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. Wrong. Used problem 300 solution.
class Solution1 {
public:
    int findLongestChain(std::vector<std::vector<int>>& pairs) {
        if (pairs.size() < 2) {
            return pairs.size();
        }

        auto minValues = std::vector<std::vector<int>>();
        for (const auto& pair: pairs) {
            if (minValues.empty()) {
                minValues.push_back(pair);
            } else if (pair[0] > minValues.back()[1]) {
                minValues.push_back(pair);
            } else {
                auto it = std::upper_bound(minValues.begin(), minValues.end(), pair, [](const std::vector<int>& a, const std::vector<int>& b) -> bool {
                    if (a[1] < b[0]) {
                        return true;
                    } else {
                        return false;
                    }
                });
                if (it != minValues.end()) {
                    *it = pair;
                }
            }
        }


        return minValues.size();
    }
};


#pragma mark - 2. Sort
// Wrong answer.
// Sort results might be wrong if the given ranges have overlaps.
class Solution2 {
public:
    int findLongestChain(std::vector<std::vector<int>>& pairs) {
        if (pairs.size() < 2) {
            return pairs.size();
        }

        std::sort(pairs.begin(), pairs.end(), [](const std::vector<int>& a, const std::vector<int>& b) -> bool {
            // Returns `true` if the first argument is less than (i.e. is ordered before) the second.
            if (a[1] <= b[0]) {
                return true;
            } else {
                return false;
            }
        });

//        std::cout << "Sorted pairs: " << pairs << std::endl;

        auto indices = std::vector<size_t>({0});
        for (size_t i = 1; i < pairs.size(); i += 1) {
            const auto& currentNum = pairs[i][0];
            const auto& previousNum = pairs[indices.back()][1];
            if (currentNum > previousNum) {
                indices.push_back(i);
            }
        }

        return indices.size();
    }
};


#pragma mark - 3. Sort using pair[0] and do further comparisons using pair[1]
// Runtime: 128 ms, faster than 89.38% of C++ online submissions for Maximum Length of Pair Chain.
// Memory Usage: 22.7 MB, less than 66.31% of C++ online submissions for Maximum Length of Pair Chain.
class Solution {
public:
    int findLongestChain(std::vector<std::vector<int>>& pairs) {
        if (pairs.size() < 2) {
            return pairs.size();
        }

        // Sort using pair[0]
//        std::sort(pairs.begin(), pairs.end(), [](const std::vector<int>& a, const std::vector<int>& b) -> bool {
//            if (a[0] < b[0]) {
//                return true;
//            } else {
//                return false;
//            }
//        });

        struct {
            bool operator()(const std::vector<int>& a, const std::vector<int>& b) const {
                /*
                 * https://en.cppreference.com/w/cpp/named_req/Compare
                 * 
                 * Custom sorting function requirements:
                 *
                 * - For all a, `comp(a,a)==false`
                 * - If `comp(a,b)==true` then `comp(b,a)==false`
                 * - If `comp(a,b)==true` and `comp(b,c)==true` then `comp(a,c)==true`
                 */

                // Do not use `<=` since comp(a, a) must be false.
                return (a[0] < b[0]);
            }
        } customOperator;
        std::sort(std::begin(pairs), std::end(pairs), customOperator);

//        std::cout << "Sorted pairs: " << pairs << std::endl;

        auto indices = std::vector<size_t>({0});
        for (size_t i = 1; i < pairs.size(); i += 1) {
            const auto& previousNums = pairs[indices.back()];
            const auto& currentNums = pairs[i];

            // Find out if they overlap
            if (previousNums[1] >= currentNums[0]) {
                // Overlap
                // Compare using pair[1]
                if (currentNums[1] < previousNums[1]) {
                    // Replace
                    indices.back() = i;
                }
            } else {
                // Don't overlap
                indices.push_back(i);
            }
        }

        return indices.size();
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<std::vector<std::vector<int>>> testCases = {
        {{1,2}, {2,3}, {3,4}},    // 2
        {{3,4}, {1,2}, {2,3}},    // 2
        {{-10,-8},{8,9},{-5,0},{6,10},{-6,-4},{1,7},{9,10},{-4,7}},    // 4
        {{-492,-223},{-731,332},{660,868},{977,992},{-213,869},{68,634},{889,903},{-609,971},{-931,-547},{330,600},{952,991},{-804,704},{-815,-812},{-63,80},{-285,845},{-513,150},{-376,-271},{737,820},{240,293},{1,214},{444,727},{303,830},{-468,-420},{-824,-650},{-923,-608},{786,911},{913,942},{-805,21},{72,210},{986,989},{176,660},{-717,918},{-966,-785},{-344,188},{483,500},{-548,932},{210,831},{209,466},{121,602},{263,278},{-377,602},{421,581},{-459,558},{58,740},{638,932},{-539,708},{-372,95},{-685,-10},{305,626},{597,773},{436,807},{905,915},{746,913},{948,958},{-855,-452},{-972,636},{889,987},{-527,681},{120,710},{-691,39},{105,385},{-204,311},{373,514},{-819,57},{-166,94},{-916,-742},{-36,795},{-269,118},{821,978},{419,906},{-371,-127},{50,579},{181,391},{912,977},{341,451},{153,253},{521,808},{-59,752},{891,987},{717,922},{-890,-38},{560,711},{-805,48},{-693,263},{479,720},{742,934},{342,403},{772,819},{720,731},{-185,17},{-562,500},{844,848},{-864,728},{866,914},{386,489},{195,752},{-290,-176},{611,718},{899,962},{563,731},{840,965},{-887,-170},{826,967},{659,895},{-814,-434},{-105,130},{202,208},{692,696},{897,979},{-29,960},{-298,564},{401,891},{-534,-492},{-973,-565},{601,749},{-974,148},{-457,-272},{-891,-773},{-903,718},{135,445},{-786,808},{-763,840},{-543,226},{216,846},{-234,849},{-91,516},{544,947},{-336,-243},{-649,-27},{-198,-49},{388,507},{109,545},{670,946},{-834,3},{-1,18},{-776,866},{494,740},{-395,-360},{-580,427},{876,897},{-533,607},{-553,770},{129,176},{85,906},{-224,930},{-97,333},{913,993},{526,542},{75,316},{29,267},{-344,74},{529,865},{477,547},{316,438},{-791,-746},{-420,-21},{728,751},{900,904},{611,691},{537,936},{520,554},{894,993},{-754,-54},{312,543},{132,574},{986,987},{-57,770},{-639,440},{9,636},{-225,-87},{-510,-224},{-61,116},{345,625},{363,932},{-115,934},{-674,526},{168,242},{-822,-368},{-194,624},{469,912},{722,768},{-262,685},{846,975},{865,880},{876,940},{700,997},{427,964},{789,988},{-104,-66},{-357,335},{-462,729},{-975,534},{289,851},{-744,-548},{-25,842},{595,900},{-730,235},{-1,433},{99,227},{-162,661},{-367,-99},{584,683},{-508,-105},{462,886},{-126,973},{925,980},{542,584},{409,907},{24,33},{-178,-122},{148,513},{-942,397},{771,827},{562,768},{282,999},{-947,-615},{565,995},{480,988},{171,666},{-82,-31},{-348,429},{-975,-851},{-991,580}},    // 28
    };
    for (auto testCase: testCases) {
        auto result = solutionInstance.findLongestChain(testCase);
        std::cout << testCase << ": " << result << std::endl;
    }

    return 0;
}
