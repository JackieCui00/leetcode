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
    }

    {
        std::vector<int> A = {12, 24, 8, 32};
        std::vector<int> B = {35, 25, 32, 11};
        const std::vector<int> output = solution.advantageCount(A, B);
        const std::vector<int> expect_output = {24, 32, 8, 12};

        print(std::make_tuple(A, B), output, expect_output);
    }
}

DEFINE_MAIN
