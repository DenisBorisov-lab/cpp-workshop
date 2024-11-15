#include <gtest/gtest.h>
#include "square.hpp"

class SquareTest : public ::testing::Test {
protected:
    Point<int> testCenter{1, 2};
    Square<int> validSquare{testCenter, 5};
};

TEST_F(SquareTest, ValidConstruction) {
    EXPECT_NO_THROW({
                        Square<int> square(testCenter, 5);
                    });

    Point<int> center = validSquare.getCenter();
    EXPECT_EQ(center.getX(), testCenter.getX());
    EXPECT_EQ(center.getY(), testCenter.getY());
}

TEST_F(SquareTest, Area) {
    EXPECT_DOUBLE_EQ(validSquare.area(), 25.0);

    Square<int> unitSquare(testCenter, 1);
    EXPECT_DOUBLE_EQ(unitSquare.area(), 1.0);

    Square<int> largeSquare(testCenter, 10);
    EXPECT_DOUBLE_EQ(largeSquare.area(), 100.0);
}

TEST_F(SquareTest, Clone) {
    auto cloned = validSquare.clone();

    EXPECT_NE(&validSquare, cloned.get());

    EXPECT_DOUBLE_EQ(cloned->area(), validSquare.area());

    Point<int> clonedCenter = cloned->getCenter();
    EXPECT_EQ(clonedCenter.getX(), testCenter.getX());
    EXPECT_EQ(clonedCenter.getY(), testCenter.getY());
}

TEST_F(SquareTest, Comparison) {
    Square<int> smaller(testCenter, 3);

    Square<int> equal(testCenter, 5);

    Square<int> larger(testCenter, 6);

    EXPECT_TRUE(validSquare > smaller);
    EXPECT_TRUE(smaller < validSquare);
    EXPECT_TRUE(validSquare == equal);
    EXPECT_TRUE(validSquare < larger);
}

TEST_F(SquareTest, DifferentTypes) {
    Square<double> doubleSquare(Point<double>(0.5, 0.5), 5.0);
    EXPECT_DOUBLE_EQ(doubleSquare.area(), 25.0);

    Square<float> floatSquare(Point<float>(0.5f, 0.5f), 5.0f);
    EXPECT_FLOAT_EQ(floatSquare.area(), 25.0f);
}

TEST_F(SquareTest, DoubleConversion) {
    auto area = double(validSquare);
    EXPECT_DOUBLE_EQ(area, 25.0);
}

TEST_F(SquareTest, EdgeCases) {
    EXPECT_THROW({
                     Square<int> invalidSquare(testCenter, 0);
                 }, std::invalid_argument);

    EXPECT_THROW({
                     Square<int> invalidSquare(testCenter, -5);
                 }, std::invalid_argument);
}

TEST_F(SquareTest, TypeLimits) {
    Square<int> maxSquare(testCenter, std::numeric_limits<int>::max());
    EXPECT_GT(maxSquare.area(), 0);

    Square<int> minSquare(testCenter, 1);
    EXPECT_DOUBLE_EQ(minSquare.area(), 1.0);
}
