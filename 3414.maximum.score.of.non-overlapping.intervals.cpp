#include "leetcode.h"

/*
 * You are given a 2D integer array intervals, where intervals[i] = [l_i, r_i, weight_i].
 * Interval i starts at position l_i and ends at r_i, and has a weight of weight_i.
 * You can choose up to 4 non-overlapping intervals.
 * The score of the chosen intervals is defined as the total sum of their weights.
 *
 * Return the lexicographically smallest array of at most 4 indices from intervals with
 * maximum score, representing your choice of non-overlapping intervals.
 *
 * Two intervals are said to be non-overlapping if they do not share any points.
 * In particular, intervals sharing a left or right boundary are considered overlapping.
 *
 * Example 1:
 * Input: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]
 * Output: [2,3]
 * Explanation:
 * You can choose the intervals with indices 2, and 3 with respective weights of 5, and 3.
 *
 * Example 2:
 * Input: intervals = [[5,8,1],[6,7,7],[4,7,3],[9,10,6],[7,8,2],[11,14,3],[3,5,5]]
 * Output: [1,3,5,6]
 * Explanation:
 * You can choose the intervals with indices 1, 3, 5, and 6 with respective weights of 7, 6, 3, and 5.
 *
 * Constraints:
 * - 1 <= intevals.length <= 5 * 10^4
 * - intervals[i].length == 3
 * - intervals[i] = [li, ri, weighti]
 * - 1 <= li <= ri <= 10^9
 * - 1 <= weighti <= 10^9
 *
 */

struct Answer
{
    uint64_t weight = 0;
    std::vector<int> path;

    Answer() : weight(0)
    {
        path.reserve(4);
    }
};

struct Element
{
    int index;
    int start;
    int end;
    int weight;
};

std::ostream& operator<<(std::ostream& out, const Answer& value)
{
    out << "Answer(weight:" << value.weight << ", path:" << value.path << ")";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Element& element)
{
    out << "Element(index:" << element.index << ", start:" << element.start
        << ", end:" << element.end << ", weight:" << element.weight << ")";
    return out;
}

class Solution
{
public:
    std::vector<int> maximumWeight(const std::vector<std::vector<int>>& intervals)
    {
        std::vector<Element> elements;
        elements.resize(intervals.size());
        for (uint64_t i = 0; i < intervals.size(); ++i)
        {
            auto& e= elements[i];
            const auto& interval = intervals[i];

            e.index = i;
            e.start = interval[0];
            e.end = interval[1];
            e.weight = interval[2];
        }
        std::sort(elements.begin(), elements.end(),
                [] (const Element& a, const Element& b) {
            return a.end < b.end;
        });
        // std::cout << "elements:" << elements << std::endl;

        std::vector<std::array<Answer, 4>> results;
        results.resize(intervals.size());
        for (uint64_t i = 0; i < 4; ++i)
        {
            results[0][i].weight = elements[0].weight;
            results[0][i].path.emplace_back(elements[0].index);
        }
        // std::cout << results[0] << std::endl;

        for (uint64_t i = 1; i < elements.size(); ++i)
        {
            const int start = elements[i].start;
            const uint64_t weight = elements[i].weight;

            int last = -1;
            for (int l = 0, r = i - 1; l <= r; )
            {
                const int mid = (l + r) / 2;
                if (elements[mid].end >= start)
                {
                    r = mid - 1;
                }
                else
                {
                    last = mid;
                    l = mid + 1;
                }
            }

            results[i][0].weight = weight;
            results[i][0].path.emplace_back(elements[i].index);

            if (results[i][0].weight < results[i - 1][0].weight)
            {
                results[i][0] = results[i - 1][0];
            }
            else if (results[i][0].weight == results[i - 1][0].weight)
            {
                if (results[i][0].path > results[i - 1][0].path)
                {
                    results[i][0].path = results[i - 1][0].path;
                }
            }

            for (int j = 1; j < 4; ++j)
            {
                if (last == -1)
                {
                    results[i][j].weight = weight;
                    results[i][j].path.emplace_back(elements[i].index);
                }
                else
                {
                    results[i][j].weight = results[last][j - 1].weight + weight;
                    results[i][j].path = results[last][j - 1].path;
                    results[i][j].path.emplace_back(elements[i].index);
                    std::sort(results[i][j].path.begin(), results[i][j].path.end());
                }

                if (results[i][j].weight < results[i - 1][j].weight)
                {
                    results[i][j] = results[i - 1][j];
                }
                else if (results[i][j].weight == results[i - 1][j].weight)
                {
                    if (results[i][j].path > results[i - 1][j].path)
                    {
                        results[i][j].path = results[i - 1][j].path;
                    }
                }
            }
            // std::cout << "last:" << last << ", " << results[i] << std::endl;
        }

        return results[elements.size() - 1][3].path;
    }
};

TEST(MaximumScoreOfNonOverlappingIntervals, simple)
{
    Solution solution;

    EXPECT_EQ(std::vector<int>({2, 3}),
            solution.maximumWeight({{1,3,2},{4,5,2},{1,5,5},{6,9,3},{6,7,1},{8,9,1}}));

    EXPECT_EQ(std::vector<int>({1, 3, 5, 6}),
            solution.maximumWeight({{5,8,1},{6,7,7},{4,7,3},{9,10,6},{7,8,2},{11,14,3},{3,5,5}}));

}

DEFINE_MAIN
