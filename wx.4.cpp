// 4、给一个数组a[n]，数组大小不超过1e5，数据范围0~1e8，求其异或值最大连续子区间。
// 输入样例：1 4 5 6
// 输出样例（4^5^6=7）：7

#include <iostream>

#include <gtest/gtest.h>

std::vector<int> FindMaxXorRange(const std::vector<int>& numbers) {
    assert(numbers.size() > 1);

    std::vector<int> xor_values = numbers;
    int max_xor = 0;
    std::pair<std::size_t, std::size_t> range;

    for (std::size_t len = 2; len <= numbers.size(); ++len) {
        for (std::size_t start = 0; (start + len) <= numbers.size(); ++ start) {
            const int end = start + len - 1;
            const int value = xor_values.at(start) ^ numbers.at(end);
            xor_values.at(start) = value;

            if (value > max_xor) {
                max_xor = value;
                range.first = start;
                range.second = end;
            }
        }
    }

    std::vector<int> result;
    for (std::size_t i = range.first; i <= range.second; ++i) {
        result.push_back(numbers.at(i));
    }

    return result;
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

TEST(FindMaxXorRange, simple) {
    {
        const std::vector<int> numbers = {1, 4, 5, 6};
        const auto result = FindMaxXorRange(numbers);
        std::cout << "Result for " << numbers << " is " << result << std::endl;
    }
}

int main(int argc, char* argv[]) {
    ::testing::FLAGS_gtest_color="true";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
