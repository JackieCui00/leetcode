#include "leetcode.h"

/*
 *
 * Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
 * The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
 * It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.
 *
 *
 * Example 1:
 *
 * Input: candidates = [2,3,6,7], target = 7
 * Output: [[2,2,3],[7]]
 * Explanation:
 * 2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
 * 7 is a candidate, and 7 = 7.
 * These are the only two combinations.
 *
 *
 * Example 2:
 *
 * Input: candidates = [2,3,5], target = 8
 * Output: [[2,2,2,2],[2,3,3],[3,5]]
 *
 *
 * Example 3:
 *
 * Input: candidates = [2], target = 1
 * Output: []
 *
 *
 * Example 4:
 *
 * Input: candidates = [1], target = 1
 * Output: [[1]]
 *
 *
 * Example 5:
 *
 * Input: candidates = [1], target = 2
 * Output: [[1,1]]
 *
 * Constraints:
 *     1 <= candidates.length <= 30
 *     1 <= candidates[i] <= 200
 *     All elements of candidates are distinct.
 *     1 <= target <= 500
 **/

class Solution {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        std::sort(candidates.begin(), candidates.end());

        std::vector<std::vector<int>> answer;
        combination_sum_inner(candidates, 0, target, &answer, {});

        return answer;
    }

    void combination_sum_inner(const std::vector<int>& candidates, const std::size_t begin,
                                const int target, std::vector<std::vector<int>>* answer,
                                const std::vector<int>& combine_old) {
        if (target < candidates.at(begin)) {
            return;
        }

        std::vector<int> combine = combine_old;

        for (std::size_t i = begin; i < candidates.size(); ++i) {
            if (target < candidates.at(i)) {
                break;
            }
            if (target == candidates.at(i)) {
                combine.push_back(candidates.at(i));
                answer->push_back(combine);
                combine.pop_back();
                break;
            }

            assert(target > candidates.at(i));
            combine.push_back(candidates.at(i));
            combination_sum_inner(candidates, i, target - candidates.at(i), answer, combine);
            combine.pop_back();
        }
    }
};

TEST(CombinationSum, simple) {
    Solution solution;

    {
        std::vector<int> candidates = {2, 3, 6, 7};
        const int target = 7;
        auto output = solution.combinationSum(candidates, target);
        decltype(output) expect_output = {{2, 2, 3}, {7}};

        print(std::make_tuple(candidates, target), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<int> candidates = {2, 3, 5};
        const int target = 8;
        auto output = solution.combinationSum(candidates, target);
        decltype(output) expect_output = {{2, 2, 2, 2}, {2, 3, 3}, {3, 5}};

        print(std::make_tuple(candidates, target), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<int> candidates = {2};
        const int target = 1;
        auto output = solution.combinationSum(candidates, target);
        decltype(output) expect_output = {};

        print(std::make_tuple(candidates, target), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<int> candidates = {1};
        const int target = 2;
        auto output = solution.combinationSum(candidates, target);
        decltype(output) expect_output = {{1, 1}};

        print(std::make_tuple(candidates, target), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
