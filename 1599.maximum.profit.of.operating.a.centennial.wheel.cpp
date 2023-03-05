#include "leetcode.h"

/*
 * You are the operator of a Centennial Wheel that has four gondolas, and each gondola has room for up to four people. You have the ability to rotate the gondolas counterclockwise, which costs you runningCost dollars.
 *
 *You are given an array customers of length n where customers[i] is the number of new customers arriving just before the ith rotation (0-indexed). This means you must rotate the wheel i times before the customers[i] customers arrive. You cannot make customers wait if there is room in the gondola. Each customer pays boardingCost dollars when they board on the gondola closest to the ground and will exit once that gondola reaches the ground again.
 *
 *You can stop the wheel at any time, including before serving all customers. If you decide to stop serving customers, all subsequent rotations are free in order to get all the customers down safely. Note that if there are currently more than four customers waiting at the wheel, only four will board the gondola, and the rest will wait for the next rotation.
 *
 *Return the minimum number of rotations you need to perform to maximize your profit. If there is no scenario where the profit is positive, return -1.

 * Example 1
 * Input: customers = [8,3], boardingCost = 5, runningCost = 6
 * Output: 3
 * Explanation: The numbers written on the gondolas are the number of people currently there.
 * 1. 8 customers arrive, 4 board and 4 wait for the next gondola, the wheel rotates. Current profit is 4 * $5 - 1 * $6 = $14.
 * 2. 3 customers arrive, the 4 waiting board the wheel and the other 3 wait, the wheel rotates. Current profit is 8 * $5 - 2 * $6 = $28.
 * 3. The final 3 customers board the gondola, the wheel rotates. Current profit is 11 * $5 - 3 * $6 = $37.
 * The highest profit was $37 after rotating the wheel 3 times.

 * Example 2:
 * Input: customers = [10,9,6], boardingCost = 6, runningCost = 4
 * Output: 7
 * Explanation:
 * 1. 10 customers arrive, 4 board and 6 wait for the next gondola, the wheel rotates. Current profit is 4 * $6 - 1 * $4 = $20.
 * 2. 9 customers arrive, 4 board and 11 wait (2 originally waiting, 9 newly waiting), the wheel rotates. Current profit is 8 * $6 - 2 * $4 = $40.
 * 3. The final 6 customers arrive, 4 board and 13 wait, the wheel rotates. Current profit is 12 * $6 - 3 * $4 = $60.
 * 4. 4 board and 9 wait, the wheel rotates. Current profit is 16 * $6 - 4 * $4 = $80.
 * 5. 4 board and 5 wait, the wheel rotates. Current profit is 20 * $6 - 5 * $4 = $100.
 * 6. 4 board and 1 waits, the wheel rotates. Current profit is 24 * $6 - 6 * $4 = $120.
 * 7. 1 boards, the wheel rotates. Current profit is 25 * $6 - 7 * $4 = $122.
 * The highest profit was $122 after rotating the wheel 7 times.

 * Example 3:
 * Input: customers = [3,4,0,5,1], boardingCost = 1, runningCost = 92
 * Output: -1
 * Explanation:
 * 1. 3 customers arrive, 3 board and 0 wait, the wheel rotates. Current profit is 3 * $1 - 1 * $92 = -$89.
 * 2. 4 customers arrive, 4 board and 0 wait, the wheel rotates. Current profit is 7 * $1 - 2 * $92 = -$177.
 * 3. 0 customers arrive, 0 board and 0 wait, the wheel rotates. Current profit is 7 * $1 - 3 * $92 = -$269.
 * 4. 5 customers arrive, 4 board and 1 waits, the wheel rotates. Current profit is 11 * $1 - 4 * $92 = -$357.
 * 5. 1 customer arrives, 2 board and 0 wait, the wheel rotates. Current profit is 13 * $1 - 5 * $92 = -$447.
 * The profit was never positive, so return -1.
 */

class Solution {
public:
    static constexpr int64_t MAX_PERSON_PER_ROUND = 4;

    int minOperationsMaxProfit(const std::vector<int>& customers, const int boardingCost,
            const int runningCost) {
        if (boardingCost * MAX_PERSON_PER_ROUND <= runningCost)
        {
            return -1;
        }

        int64_t maxProfit = 0;
        int64_t maxRound = 0;

        int64_t currentProfit = 0;
        int64_t currentRound = 0;
        int64_t currentPerson = 0;
        for (const auto person : customers)
        {
            currentPerson += person;
            if (currentPerson >= MAX_PERSON_PER_ROUND)
            {
                currentProfit += boardingCost * MAX_PERSON_PER_ROUND;
                currentPerson -= MAX_PERSON_PER_ROUND;
            }
            else
            {
                currentProfit += boardingCost * currentPerson;
                currentPerson = 0;
            }
            currentProfit -= runningCost;
            currentRound += 1;

            if (maxProfit < currentProfit)
            {
                maxRound = currentRound;
                maxProfit = currentProfit;
            }
        }

        // std::cout << "CurrentPerson:" << currentPerson
        //     << ", MaxRound:" << maxRound << std::endl;
        currentRound += currentPerson / MAX_PERSON_PER_ROUND;
        currentProfit += (currentPerson / MAX_PERSON_PER_ROUND) *
            (boardingCost * MAX_PERSON_PER_ROUND - runningCost);
        currentPerson %= MAX_PERSON_PER_ROUND;

        if (maxProfit < currentProfit)
        {
            maxRound = currentRound;
            maxProfit = currentProfit;
        }

        if (boardingCost * currentPerson > runningCost)
        {
            maxRound += 1;
        }

        assert(maxProfit >= 0);
        if (maxProfit == 0)
        {
            return -1;
        }
        return maxRound;
    }
};

TEST(MaximumProfit, simple)
{
    Solution solution;

    EXPECT_EQ(3, solution.minOperationsMaxProfit(std::vector<int>({8, 3}), 5, 6));
    EXPECT_EQ(7, solution.minOperationsMaxProfit(std::vector<int>({10, 9, 6}), 6, 4));
    EXPECT_EQ(-1, solution.minOperationsMaxProfit(std::vector<int>({3, 4, 0, 5, 1}), 1, 92));
    EXPECT_EQ(13, solution.minOperationsMaxProfit(std::vector<int>({5, 0, 0, 0, 0, 30}), 5, 5));
}

DEFINE_MAIN
