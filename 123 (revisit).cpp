/*
 * 123. Best Time to Buy and Sell Stock III
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
 */

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <climits>    // `INT_MAX` AND `INT_MIN`


#pragma mark - 1. Combine segments
// Wrong solution
class Solution1 {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        } else if (prices.size() == 2) {
            if (prices[1] > prices[0]) {
                return (prices[1] - prices[0]);
            }
        }

        int start1 = -1;
        int end1 = -1;
        int profit1 = 0;
        int start2 = -1;
        int end2 = -1;
        int profit2 = 0;

        int start3 = -1;
        int end3 = -1;
        int profit3 = 0;

        for (size_t i = 0; i < prices.size(); i += 1) {
            if (start3 == -1) {
                start3 = i;
                continue;
            }

            const auto& startPrice = prices[start3];
            const auto& currentPrice = prices[i];

            const int profit = currentPrice - startPrice;
            if ((profit <= 0) && (profit3 == 0)) {
                // Loss
                // Just started and not profitable.
                // Start again.
                start3 = i;
            } else if (profit3 < profit) {
                // Profit
                // This profit is larger.
                profit3 = profit;
                end3 = i;
            } else {
                // Not enough profit.
                // Check if both 1 and 2 are filled.
                if (start1 == -1) {
                    // 1 is not initialized.
                    start1 = start3;
                    end1 = end3;
                    profit1 = profit3;
                } else if (start2 == -1) {
                    // 2 is not initialized.
                    start2 = start3;
                    end2 = end3;
                    profit2 = profit3;
                } else {
                    // Combine 3 segments using the previous profit.
                    // We may either combine or not combine.
                    int combinedProfit12 = prices[end2] - prices[start1];
                    int combinedProfit23 = prices[end3] - prices[start2];

                    int totalProfit1 = combinedProfit12 + profit3;
                    int totalProfit2 = combinedProfit23 + profit1;
                    int totalProfit3 = profit1 + profit2;
                    int totalProfit4 = profit1 + profit3;
                    int totalProfit5 = profit2 + profit3;

                    int maxTotalProfit = std::max({totalProfit1, totalProfit2, totalProfit3, totalProfit4, totalProfit5});

                    if (maxTotalProfit == totalProfit1) {
                        // Combine 1 and 2.
                        end1 = end2;
                        profit1 = combinedProfit12;

                        start2 = start3;
                        end2 = end3;
                        profit2 = profit3;
                    } else if (maxTotalProfit == totalProfit2) {
                        // Combine 2 and 3.
                        end2 = end3;
                        profit2 = combinedProfit23;
                    } else if (maxTotalProfit == totalProfit4) {
                        // Replace 2 with 3.
                        start2 = start3;
                        end2 = end3;
                        profit2 = profit3;
                    } else if (maxTotalProfit == totalProfit5) {
                        // Replace 1 with 2 and 2 with 3.
                        start1 = start2;
                        end1 = end2;
                        profit1 = profit2;

                        start2 = start3;
                        end2 = end3;
                        profit2 = profit3;
                    }
                }

                // Reset current stats.
//                    start3 = -1;
                end3 = -1;
                profit3 = 0;

                // Reset start.
                start3 = i;
            }
        }

        if (profit3 > 0) {
            if (start1 == -1) {
                // 1 is not initialized.
                return profit3;
            } else if (start2 == -1) {
                // 2 is not initialized.
                start2 = start3;
                end2 = end3;
                profit2 = profit3;
            } else {
                // Combine 3 segments using the previous profit.
                // We may either combine or not combine.
                int combinedProfit12 = prices[end2] - prices[start1];
                int combinedProfit23 = prices[end3] - prices[start2];

                int totalProfit1 = combinedProfit12 + profit3;
                int totalProfit2 = combinedProfit23 + profit1;
                int totalProfit3 = profit1 + profit2;
                int totalProfit4 = profit1 + profit3;
                int totalProfit5 = profit2 + profit3;

                int maxTotalProfit = std::max({totalProfit1, totalProfit2, totalProfit3, totalProfit4, totalProfit5});

                if (maxTotalProfit == totalProfit1) {
                    // Combine 1 and 2.
                    end1 = end2;
                    profit1 = combinedProfit12;

                    start2 = start3;
                    end2 = end3;
                    profit2 = profit3;
                } else if (maxTotalProfit == totalProfit2) {
                    // Combine 2 and 3.
                    end2 = end3;
                    profit2 = combinedProfit23;
                } else if (maxTotalProfit == totalProfit4) {
                    // Replace 2 with 3.
                    start2 = start3;
                    end2 = end3;
                    profit2 = profit3;
                } else if (maxTotalProfit == totalProfit5) {
                    // Replace 1 with 2 and 2 with 3.
                    start1 = start2;
                    end1 = end2;
                    profit1 = profit2;

                    start2 = start3;
                    end2 = end3;
                    profit2 = profit3;
                }
            }
        }

        return (profit1 + profit2);
    }
};


#pragma mark - 2. Use buy once profit to calculate buy twice cost and profit
// Runtime: 396 ms, faster than 5.02% of C++ online submissions for Best Time to Buy and Sell Stock III.
// Memory Usage: 75.2 MB, less than 9.58% of C++ online submissions for Best Time to Buy and Sell Stock III.
class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }

        /// Always negative.
        int buyOnceCost = INT_MIN;
        int buyOnceProfit = 0;
        int buyTwiceCost = INT_MIN;
        int buyTwiceProfit = 0;

        for (const auto& price: prices) {
            // NOTE: Order different with 3
            buyOnceProfit = std::max(buyOnceProfit, price + buyOnceCost);
            buyOnceCost = std::max(buyOnceCost, 0 - price);

            buyTwiceProfit = std::max(buyTwiceProfit, price + buyTwiceCost);
            buyTwiceCost = std::max(buyTwiceCost, buyOnceProfit - price);
        }

        return std::max(buyOnceProfit, buyTwiceProfit);
    }
};


#pragma mark - 3. More intuitive 2
// Runtime: 252 ms, faster than 87.63% of C++ online submissions for Best Time to Buy and Sell Stock III.
// Memory Usage: 75.6 MB, less than 5.27% of C++ online submissions for Best Time to Buy and Sell Stock III.
class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }

        /// Always negative.
        int buyOnceCost = INT_MIN;
        int buyOnceProfit = 0;
        int buyTwiceCost = INT_MIN;
        int buyTwiceProfit = 0;

        for (const auto& price: prices) {
            // NOTE: Order difference with 2
            // I think letting the "twice" ones go first is more intuitive: `buyTwiceCost` only uses the previous `buyOnceProfit` (it's not possible to buy and sell at the same time).
            buyTwiceProfit = std::max(buyTwiceProfit, price + buyTwiceCost);    // Profit relies on the previous cost and the current price.
            buyTwiceCost = std::max(buyTwiceCost, buyOnceProfit - price);    // Cost relies on the previous "buy once" profit and the current price.

            buyOnceProfit = std::max(buyOnceProfit, price + buyOnceCost);
            buyOnceCost = std::max(buyOnceCost, 0 - price);
        }

        return std::max(buyOnceProfit, buyTwiceProfit);
    }
};


#pragma mark - 4. Optimized 1
// WRONG ANSWER
// We might need to obtain 4 segments. 3 segments are not enough: some important segments are ignored halfway.
#define VALUE_PLACEHOLDER -1
enum class Status {
    zero,

    /// Purchased once, but not sold.
    s1,
    /// Purchased and sold once.
    e1,

    /// Purchased twice, sold once.
    s2,
    /// Purchased and sold twice.
    e2,

    /// Purchased three times, sold twice.
    s3,
    /// Purchased and sold three times.
    e3,
};

class Solution4 {
public:
    inline std::array<int, 4> combineSegments(int start1, int end1, int start2, int end2, int start3, int end3) {
        const int profit1 = end1 - start1;
        const int profit2 = end2 - start2;
        const int profit3 = end3 - start3;

        const int profit12 = end2 - start1;
        const int profit23 = end3 - start2;

        const auto totalProfits = {
            profit1 + profit2,    // 0
            profit1 + profit3,    // 1
            profit2 + profit3,    // 2
            profit12 + profit3,    // 3
            profit1 + profit23,    // 4
        };
        const size_t maxI = std::distance(std::begin(totalProfits), std::max_element(std::begin(totalProfits), std::end(totalProfits)));
        switch (maxI) {
            case 0:
                return {start1, end1, start2, end2};
            case 1:
                return {start1, end1, start3, end3};
            case 2:
                return {start2, end2, start3, end3};
            case 3:
                return {start1, end2, start3, end3};
            case 4:
                return {start1, end1, start2, end3};
            default:
                std::cout << "Invalid max index: " << maxI << std::endl;
                return {start1, end1, start2, end3};
        }
    }

    int maxProfit(std::vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }

        // Index: 3 > 2 > 1
        Status currentStatus = Status::zero;

        // -1 is a placeholder: no price is negative.
        int start1 = VALUE_PLACEHOLDER;
        int end1 = VALUE_PLACEHOLDER;
        int start2 = VALUE_PLACEHOLDER;
        int end2 = VALUE_PLACEHOLDER;

        int start3 = VALUE_PLACEHOLDER;
        int end3 = VALUE_PLACEHOLDER;

        for (const auto& price: prices) {
            switch (currentStatus) {
                case Status::zero:
                    start1 = price;
                    currentStatus = Status::s1;
                    break;

                case Status::s1:
                    if (price <= start1) {
                        start1 = price;
                    } else {
                        if (price >= end1) {
                            end1 = price;
                            currentStatus = Status::e1;
                        }
                    }
                    break;

                case Status::e1:
                    if (price > end1) {
                        end1 = price;
                    } else {
                        start2 = price;
                        currentStatus = Status::s2;
                    }
                    break;

                case Status::s2:
                    if (price <= start2) {
                        start2 = price;
                    } else {
                        if (price >= end2) {
                            end2 = price;
                            currentStatus = Status::e2;
                        }
                    }
                    break;

                case Status::e2:
                    if (price > end2) {
                        end2 = price;
                    } else {
                        start3 = price;
                        currentStatus = Status::s3;
                    }
                    break;

                case Status::s3:
                    if (price <= start3) {
                        start3 = price;
                    } else {
                        if (price >= end3) {
                            end3 = price;
                            currentStatus = Status::e3;
                        }
                    }
                    break;

                case Status::e3:
                    if (price > end3) {
                        end3 = price;
                    } else if (price < start3) {
                        // Combine segments.
                        const auto combinedSegments = combineSegments(start1, end1, start2, end2, start3, end3);
                        start1 = combinedSegments[0];
                        end1 = combinedSegments[1];
                        start2 = combinedSegments[2];
                        end2 = combinedSegments[3];

                        start3 = price;
                        end3 = VALUE_PLACEHOLDER;
                        currentStatus = Status::s3;
                    }
            }
        }

        // Final status.
        switch (currentStatus) {
            case Status::s1:
                // No transaction made.
                return 0;

            case Status::s2:
                // Unfinished transaction.
                return (end1 - start1);

            case Status::e3:
                // Combine segments.
                const auto combinedSegments = combineSegments(start1, end1, start2, end2, start3, end3);
                start1 = combinedSegments[0];
                end1 = combinedSegments[1];
                start2 = combinedSegments[2];
                end2 = combinedSegments[3];

                return (end1 - start1 + end2 - start2);
        }

        return (end1 - start1 + end2 - start2);
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<std::vector<int>> testCases = {
        {397,6621,4997,7506,8918,1662,9187,3278,3890,514,18,9305,93,5508,3031,2692,6019,1134,1691,4949,5071,799,8953,7882,4273,302,6753,4657,8368,3942,1982,5117,563,3332,2623,9482,4994,8163,9112,5236,5029,5483,4542,1474,991,3925,4166,3362,5059,5857,4663,6482,3008,3616,4365,3634,270,1118,8291,4990,1413,273,107,1976,9957,9083,7810,4952,7246,3275,6540,2275,8758,7434,3750,6101,1359,4268,5815,2771,126,478,9253,9486,446,3618,3120,7068,1089,1411,2058,2502,8037,2165,830,7994,1248,4993,9298,4846,8268,2191,3474,3378,9625,7224,9479,985,1492,1646,3756,7970,8476,3009,7457,8922,2980,577,2342,4069,8341,4400,2923,2730,2917,105,724,518,5098,6375,5364,3366,8566,8838,3096,8191,2414,2575,5528,259,573,5636,4581,9049,4998,2038,4323,7978,8968,6665,8399,7309,7417,1322,6391,335,1427,7115,853,2878,9842,2569,2596,4760,7760,5693,9304,6526,8268,4832,6785,5194,6821,1367,4243,1819,9757,4919,6149,8725,7936,4548,2386,5354,2222,8777,2041,1,2245,9246,2879,8439,1815,5476,3200,5927,7521,2504,2454,5789,3688,9239,7335,6861,6958,7931,8680,3068,2850,1181,1793,7138,2081,532,2492,4303,5661,885,657,4258,131,9888,9050,1947,1716,2250,4226,9237,1106,6680,1379,1146,2272,8714,8008,9230,6645,3040,2298,5847,4222,444,2986,2655,7328,1830,6959,9341,2716,3968,9952,2847,3856,9002,1146,5573,1252,5373,1162,8710,2053,2541,9856,677,1256,4216,9908,4253,3609,8558,6453,4183,5354,9439,6838,2682,7621,149,8376,337,4117,8328,9537,4326,7330,683,9899,4934,2408,7413,9996,814,9955,9852,1491,7563,421,7751,1816,4030,2662,8269,8213,8016,4060,5051,7051,1682,5201,5427,8371,5670,3755,7908,9996,7437,4944,9895,2371,7352,3661,2367,4518,3616,8571,6010,1179,5344,113,9347,9374,2775,3969,3939,792,4381,8991,7843,2415,544,3270,787,6214,3377,8695,6211,814,9991,2458,9537,7344,6119,1904,8214,6087,6827,4224,7266,2172,690,2966,7898,3465,3287,1838,609,7668,829,8452,84,7725,8074,871,3939,7803,5918,6502,4969,5910,5313,4506,9606,1432,2762,7820,3872,9590,8397,1138,8114,9087,456,6012,8904,3743,7850,9514,7764,5031,4318,7848,9108,8745,5071,9400,2900,7341,5902,7870,3251,7567,2376,9209,9000,1491,7030,2872,7433,1779,362,5547,7218,7171,7911,2474,914,2114,8340,8678,3497,2659,2878,2606,7756,7949,2006,656,5291,4260,8526,4894,1828,7255,456,7180,8746,3838,6404,6179,5617,3118,8078,9187,289,5989,1661,1204,8103,2,6234,7953,9013,5465,559,6769,9766,2565,7425,1409,3177,2304,6304,5005,9559,6760,2185,4657,598,8589,836,2567,1708,5266,1754,8349,1255,9767,5905,5711,9769,8492,3664,5134,3957,575,1903,3723,3140,5681,5133,6317,4337,7789,7675,3896,4549,6212,8553,1499,1154,5741,418,9214,1007,2172,7563,8614,8291,3469,677,4413,1961,4341,9547,5918,4916,7803,9641,4408,3484,1126,7078,7821,8915,1105,8069,9816,7317,2974,1315,8471,8715,1733,7685,6074,257,5249,4688,8549,5070,5366,2962,7031,6059,8861,9301,7328,6664,5294,8088,6500,6421,1518,4321,5336,2623,8742,1505,9941,1716,2820,4764,6783,906,2450,2857,7515,4051,7546,2416,9121,9264,1730,6152,1675,592,1805,9003,7256,7099,3444,3757,9872,4962,4430,1561,7586,3173,3066,3879,1241,2238,8643,8025,3144,7445,882,7012,1496,4780,9428,617,396,1159,3121,2072,1751,4926,7427,5359,8378,871,5468,8250,5834,9899,9811,9772,9424,2877,3651,7017,5116,8646,5042,4612,6092,2277,1624,7588,3409,1053,8206,3806,8564,7679,2230,6667,8958,6009,2026,7336,6881,3847,5586,9067,98,1750,8839,9522,4627,8842,2891,6095,7488,7934,708,3580,6563,8684,7521,9972,6089,2079,130,4653,9758,2360,1320,8716,8370,9699,6052,1603,3546,7991,670,3644,6093,9509,9518,7072,4703,2409,3168,2191,6695,228,2124,3258,5264,9645,9583,1354,1724,9713,2359,1482,8426,3680,6551,3148,9731,8955,4751,9629,6946,5421,9625,9391,1282,5495,6464,5985,4256,5984,4528,952,6212,6652,562,1476,6297,145,9182,8021,6211,1542,5856,4637,1574,2407,7785,1305,1362,2536,934,4661,4309,559,4052,1943,2406,516,4280,6662,2852,8808,7614,9064,1813,4529,6893,8110,4674,2427,2484,7237,3969,8340,1874,5543,7099,6011,3200,8461,8547,486,9474,9208,7397,9879,7503,9803,6747,1783,6466,9600,6944,432,8664,8757,4961,1909,6867,5988,4337,5703,3225,4658,4043,1452,6554,1142,7463,9754,5956,2363,241,1782,7923,7638,1661,5427,3794,8409,7210,260,8009,4154,692,3025,9263,2006,4935,2483,7994,5624,8186,7571,282,8582,9023,6836,6076,6487,6591,2032,8850,3184,3815,3125,7174,5476,8552,968,3885,2115,7580,8246,2621,4625,1272,1885,6631,6207,4368,4625,8183,2554,8548,8465,1136,7572,1654,7213,411,4597,5597,5613,7781,5764,8738,1307,7593,7291,8628,7830,9406,6208,6077,2027,833,7349,3912,7464,9908,4632,8441,8091,7187,6990,2908,4675,914,4562,8240,1325,9159,190,6938,3292,5954,2028,4600,9899,9319,3228,7730,5077,9436,159,7105,6622,7508,7369,4086,3768,2002,8880,8211,5541,2222,1119,216,3136,5682,4809,813,1193,4999,4103,4486,7305,6131,9086,7205,5451,2314,1287,528,8102,1446,3985,4724,5306,1355,5163,9074,9709,4043,7285,5250,2617,4756,1818,2105,6790,6627,2918,7984,7978,7021,2470,1636,3152,7908,8841,4955,222,6480,5484,4676,7926,5821,9401,3232,7176,916,8658,3237,1311,5943,8487,3928,7051,306,6033,3842,3285,8951,1826,7616,2324,648,9252,5476,8556,4445,6784},    // 19965
        {3,5,3,4,1,4,5,0,7,8,5,6,9,4,1},    // 13
        {14,9,10,12,4,8,1,16},    // 19
        {0,3,0,4,5,0,7,8},    // 13
        {0,3,1,4,5,0,7,8},    // 13
        {3,3,5,0,0,3,1,4},    // 6
        {1,2,3,4,5},    // 4
        {7,6,4,3,1},    // 0
        {1},    // 0
        {1,1,1,1,1,1,1},    // 0
    };
    for (auto& testCase: testCases) {
        std::cout << solutionInstance.maxProfit(testCase) << std::endl;
    }

    return 0;
}
