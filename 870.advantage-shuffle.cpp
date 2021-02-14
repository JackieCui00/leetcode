#include "leetcode.h"

/*
 * Given two arrays A and B of equal size, the advantage of A with respect to B is the number of indices i for which A[i] > B[i].
 * Return any permutation of A that maximizes its advantage with respect to B.
 *
 *
 * Example 1:
 * Input: A = [2,7,11,15], B = [1,10,4,11]
 * Output: [2,11,7,15]
 *
 *
 * Example 2:
 * Input: A = [12,24,8,32], B = [13,25,32,11]
 * Output: [24,32,8,12]
 *
 *
 * Note:
 *     1 <= A.length = B.length <= 10000
 *     0 <= A[i] <= 10^9
 *     0 <= B[i] <= 10^9
 *
 **/

class Solution {
public:
    std::vector<int> advantageCount(std::vector<int>& A, std::vector<int>& B) {
        if (A.empty()) {
            return A;
        }

        std::sort(A.begin(), A.end());

        std::vector<std::pair<int, std::size_t>> sorted_B;
        {
            for (std::size_t i = 0; i < B.size(); ++i) {
                sorted_B.emplace_back(B.at(i), i);
            }
            auto compare_func = [] (const std::pair<int, std::size_t>& item1, const std::pair<int, std::size_t>& item2) {
                return item1.first < item2.first;
            };
            std::sort(sorted_B.begin(), sorted_B.end(), compare_func);
        }

        std::vector<int> result;
        result.resize(A.size());

        std::size_t upper = sorted_B.size();
        std::size_t lower = 0;
        for (const auto n : A) {
            assert(lower < upper);
            auto expect = sorted_B.at(lower);
            if (n <= expect.first) {
                --upper;
                expect = sorted_B.at(upper);
            } else {
                ++lower;
            }

            const std::size_t index = expect.second;
            assert(index < result.size());
            result.at(index) = n;
        }
        assert(lower == upper);

        return result;
    }
};

TEST(AdvantageShuffle, simple) {
    Solution solution;

    {
        std::vector<int> A = {2, 7, 11, 15};
        std::vector<int> B = {1, 10, 4, 11};
        const std::vector<int> output = solution.advantageCount(A, B);
        const std::vector<int> expect_output = {2, 11, 7, 15};

        print(std::make_tuple(A, B), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<int> A = {12, 24, 8, 32};
        std::vector<int> B = {35, 25, 32, 11};
        const std::vector<int> output = solution.advantageCount(A, B);
        const std::vector<int> expect_output = {8, 32, 24, 12};

        print(std::make_tuple(A, B), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }

    {
        std::vector<int> A = {2, 0, 4, 1, 2};
        std::vector<int> B = {1, 3, 0, 0, 2};
        const std::vector<int> output = solution.advantageCount(A, B);
        const std::vector<int> expect_output = {2, 0, 1, 2, 4};

        print(std::make_tuple(A, B), output, expect_output);
        EXPECT_EQ(output, expect_output);
    }
}

DEFINE_MAIN
