#include <gtest/gtest.h>
#include "solution.h"

class IsAfraidTest : public ::testing::TestWithParam<std::tuple<std::string, int, bool>> {
};

TEST_P(IsAfraidTest, CheckIsAfraid) {
    auto [day, value, expected] = GetParam();
    EXPECT_EQ(isAfraid(day, value), expected)
                        << "Day: " << day << ", Value: " << value << ", Expected: " << expected;
}

INSTANTIATE_TEST_SUITE_P(
        IsAfraidTestCases,
        IsAfraidTest,
        ::testing::Values(
                std::make_tuple("Понедельник", 12, true),
                std::make_tuple("Понедельник", 13, false),
                std::make_tuple("Понедельник", 11, false),
                std::make_tuple("Вторник", 96, true),
                std::make_tuple("Вторник", 95, false),
                std::make_tuple("Вторник", 94, false),
                std::make_tuple("Среда", 34, true),
                std::make_tuple("Среда", 33, false),
                std::make_tuple("Четверг", 0, true),
                std::make_tuple("Четверг", 1, false),
                std::make_tuple("Пятница", 2, true),
                std::make_tuple("Пятница", 3, false),
                std::make_tuple("Суббота", 56, true),
                std::make_tuple("Суббота", 57, false),
                std::make_tuple("Суббота", 55, false),
                std::make_tuple("Воскресенье", 666, true),
                std::make_tuple("Воскресенье", -666, true),
                std::make_tuple("Воскресенье", 0, false)
        )
);

TEST(IsAfraidExceptionTest, ThrowsOnInvalidDay) {
    EXPECT_THROW({
                     try {
                         isAfraid("InvalidDay", 0);
                     }
                     catch (const std::runtime_error &e) {
                         EXPECT_STREQ("Invalid day of the week!", e.what());
                         throw;
                     }
                 }, std::runtime_error);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
