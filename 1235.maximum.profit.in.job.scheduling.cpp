#include "leetcode.h"

/*
 *
 * We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i],
 * obtaining a profit of profit[i].
 *
 * You're given the startTime, endTime and profit arrays, return the maximum profit you
 * can take such that there are no two jobs in the subset with overlapping time range.
 *
 * If you choose a job that ends at time X you will be able to start another job
 * that starts at time X.
 *
 * Example 1:
 * Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
 * Output: 120
 * Explanation: The subset chosen is the first and fourth job. 
 * Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
 *
 * Example 2:
 * Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
 * Output: 150
 * Explanation: The subset chosen is the first, fourth and fifth job. 
 * Profit obtained 150 = 20 + 70 + 60.
 *
 * Example 3:
 * Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
 * Output: 6
 *
 * Constraints:
 * - 1 <= startTime.length == endTime.length == profit.length <= 5 * 104
 * - 1 <= startTime[i] < endTime[i] <= 109
 * - 1 <= profit[i] <= 104
 *
 */

class Solution
{
public:
    int jobScheduling(const std::vector<int>& startTime,
                      const std::vector<int>& endTime,
                      const std::vector<int>& profit)
    {
        struct Type
        {
            int start;
            int end;
            int profit;
        };
        std::vector<Type> jobs;
        jobs.reserve(startTime.size());
        for (uint64_t i = 0; i < startTime.size(); ++i)
        {
            jobs.emplace_back();
            jobs.back().start = startTime[i];
            jobs.back().end = endTime[i];
            jobs.back().profit = profit[i];
        }

        std::sort(jobs.begin(), jobs.end(), [] (const Type& a, const Type& b) { return a.end < b.end; });

        std::vector<int> dp;
        dp.reserve(jobs.size());

        dp.push_back(jobs[0].profit);
        for (uint64_t i = 1; i < jobs.size(); ++i)
        {
            int t = jobs[i].start;

            int lastProfit = 0;
            for (int l = 0, r = dp.size() - 1; l <= r; )
            {
                int mid = (l + r) / 2;
                if (jobs[mid].end > t)
                {
                    r = mid - 1;
                }
                else
                {
                    lastProfit = dp[mid];
                    l = mid + 1;
                }
            }

            dp.push_back(std::max(dp.back(), lastProfit + jobs[i].profit));
        }

        return dp.back();
    }
};

TEST(MaximumProfitInJobScheduling, simple)
{
    Solution solution;
    EXPECT_EQ(120, solution.jobScheduling({1, 2, 3, 3}, {3, 4, 5, 6}, {50, 10, 40, 70}));
    EXPECT_EQ(150, solution.jobScheduling({1, 2, 3, 4, 6}, {3, 5, 10, 6, 9}, {20, 20, 100, 70, 60}));
    EXPECT_EQ(6, solution.jobScheduling({1, 1, 1}, {2, 3, 4}, {5, 6, 4}));
    EXPECT_EQ(41, solution.jobScheduling({6,15,7,11,1,3,16,2}, {19,18,19,16,10,8,19,8}, {2,9,1,19,5,7,3,19}));
}

DEFINE_MAIN
