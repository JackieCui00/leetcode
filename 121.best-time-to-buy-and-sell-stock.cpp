#include "leetcode.h"

/*
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
 *
 *You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
 *
 *Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
 *
 *Example 1:
 *
 *Input: prices = [7,1,5,3,6,4]
 *Output: 5
 *Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
 *Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
 *
 *Example 2:
 *
 *Input: prices = [7,6,4,3,1]
 *Output: 0
 *Explanation: In this case, no transactions are done and the max profit = 0.
 *
 *Constraints:
 *
 *    1 <= prices.length <= 105
 *    0 <= prices[i] <= 104
 *
 */

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        int min_price = std::numeric_limits<int>::max();
        int max_profit = 0;

        for (const int price : prices) {
            if (price > min_price) {
                max_profit = std::max(max_profit, price - min_price);
            }
            min_price = std::min(min_price, price);
        }

        return max_profit;
    }
};

TEST(BestTimeToBuyAndSellStock, simple) {
    Solution solution;
    {
        std::vector<int> nums = {7,1,5,3,6,4};
        const int output = solution.maxProfit(nums);
        constexpr int expect_output = 5;
        print(std::make_tuple(nums), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
    {
        std::vector<int> nums = {7,6,4,3,1};
        const int output = solution.maxProfit(nums);
        constexpr int expect_output = 0;
        print(std::make_tuple(nums), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
