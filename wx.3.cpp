// 3、给一个数组a[n]，数组大小不超过1e3，数据范围0~1e8，找到三个数（可重复）使得它们的和为指定值T，如果有多个解输出一个即可。
// 输入样例（n a[0] a[1] ... a[n-1] T）：4 2 7 3 8 17
// 输出样例：2 7 8

#include <iostream>

#include <gtest/gtest.h>
#include <tuple>

bool FindTwoSum(const int expect, const std::vector<int> numbers, std::pair<int, int>* result) {
    std::size_t start = 0;
    std::size_t end = numbers.size() - 1;

    while (start <= end) {
        const int sum = numbers.at(start) + numbers.at(end);
        if (sum == expect) {
            result->first = numbers.at(start);
            result->second = numbers.at(end);
            return true;
        } else if (sum < expect) {
            ++start;
        } else { // sum > expect
            --end;
        }
    }

    return false;
}

std::tuple<int, int, int> FindMatch(const int expect, std::vector<int> numbers) {
    assert(expect > 0);
    assert(!numbers.empty());

    std::sort(numbers.begin(), numbers.end());

    for (const auto num : numbers) {
        assert(num > 0);
        if (num > expect) {
            break;
        }

        const int expect_two_sum = expect - num;
        std::pair<int, int> result;
        // maybe optimize here
        const bool find = FindTwoSum(expect_two_sum, numbers, &result);
        if (find) {
            return std::make_tuple(num, result.first, result.second);
        }
    }

    // 假设一定有解
    assert(false);
    return std::make_tuple(0, 0, 0);
}

inline std::ostream& operator<<(std::ostream& out, const std::vector<int>& elements) {
    out << "vector<";
    std::string seperator = "";
    for (const auto& e : elements) {
        out << seperator << e;
        seperator = ", ";
    }
    out << ">";
    return out;
}

TEST(FindMatch, simple) {
    {
        const int expect = 17;
        const std::vector<int> numbers = {4, 2, 7, 3, 8};
        auto result = FindMatch(expect, numbers);
        std::cout << "Result for {expect:" << expect << ", numbers:" << numbers << "} is {"
            << std::get<0>(result) << ", " << std::get<1>(result) << ", " << std::get<2>(result)
            << "}" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    ::testing::FLAGS_gtest_color="true";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
