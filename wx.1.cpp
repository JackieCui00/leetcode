#include <iostream>
#include <cassert>
#include <cmath>

#include <gtest/gtest.h>

// 1、给一个实数x大于0，求y使得y^7+0.5*y=x。
// 输入样例：129
// 输出样例（四舍五入到小数点后第二位小数）：2.00

double solve_quation(const double expect) {
    assert(expect > 0);

    double result = 1;
    double last_result = 0;

    do {
        const double v = std::pow(result, 7) + 0.5 * result;
        const double slap = 7 * std::pow(result, 6) + 0.5;

        last_result = result;
        result = (expect - v) / slap + result;

        assert(result > 0);

    } while (std::abs(result - last_result) > 0.01);

    return result;
}

TEST(solve_quation, simple) {
    {
        const double expect = 1.0;
        const double solve = solve_quation(expect);
        const double value = std::pow(solve, 7) + 0.5 * solve;
        std::cout << "Solve for " << expect
                << " is " << solve
                << ", value is " << value << std::endl;
    }

    {
        const double expect = 0.1;
        const double solve = solve_quation(expect);
        const double value = std::pow(solve, 7) + 0.5 * solve;
        std::cout << "Solve for " << expect
                << " is " << solve
                << ", value is " << value << std::endl;
    }

    {
        const double expect = 10;
        const double solve = solve_quation(expect);
        const double value = std::pow(solve, 7) + 0.5 * solve;
        std::cout << "Solve for " << expect
                << " is " << solve
                << ", value is " << value << std::endl;
    }
}

int main(int argc, char* argv[]) {
    ::testing::FLAGS_gtest_color="true";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
