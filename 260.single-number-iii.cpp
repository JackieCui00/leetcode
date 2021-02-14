#include "leetcode.h"
#include <tuple>

/*
 * [260] Single Number III
 *
 * https://leetcode.com/problems/single-number-iii/description/
 *
 * algorithms
 * Medium (53.53%)
 * Total Accepted:    83.2K
 * Total Submissions: 155.5K
 * Testcase Example:  '[1,2,1,3,2,5]'
 *
 * Given an array of numbers nums, in which exactly two elements appear only
 * once and all the other elements appear exactly twice. Find the two elements
 * that appear only once.
 *
 * Example:
 *
 *
 * Input:  [1,2,1,3,2,5]
 * Output: [3,5]
 *
 * Note:
 *
 * The order of the result is not important. So in the above example, [5, 3] is
 * also correct.
 * Your algorithm should run in linear runtime complexity. Could you implement
 * it using only constant space complexity?
 *
 *
 */

class Solution {
public:
    std::vector<int> singleNumber(std::vector<int>& nums) {
	    int flag_bit = 0;

        {
            int xor1 = 0;
            for(std::size_t i = 0; i < nums.size(); ++i) {
                xor1 ^= nums.at(i);
            }

            flag_bit = xor1 & (-xor1);
        }
        // so every number in nums can be catagorized int two classes
        // - num & flag_bit == 0
        // - num & flag_bit != 0

        std::vector<int> result = {0, 0};

	    for (std::size_t i = 0; i < nums.size(); ++i) {
	    	if((flag_bit & nums.at(i)) == 0) {
	    		result.at(0) ^= nums.at(i);
	    	} else {
                result.at(1) ^= nums.at(i);
	    	}
	    }

        if (result.at(0) > result.at(1)) {
            const int tmp = result.at(0);
            result.at(0) = result.at(1);
            result.at(1) = tmp;
        }

	    return result;
    }
};

TEST(SingleNumberIII, simple) {
    Solution solution;

    {
        std::vector<int> numbers = {1, 2, 1, 3, 2, 5};
        auto output = solution.singleNumber(numbers);
        decltype(output) expect_output = {3, 5};

        print(std::make_tuple(numbers), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<int> numbers = {-1, 0};
        auto output = solution.singleNumber(numbers);
        decltype(output) expect_output = {-1, 0};

        print(std::make_tuple(numbers), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<int> numbers = {0, 1};
        auto output = solution.singleNumber(numbers);
        decltype(output) expect_output = {0, 1};

        print(std::make_tuple(numbers), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
