#include <gtest/gtest.h>
#include "trapezoid.hpp"

class TrapezoidTest : public ::testing::Test {
protected:
    Point<int> testCenter{0, 0};
    Trapezoid<int> trapezoid{testCenter, 4, 8, 3};
};

TEST_F(TrapezoidTest, Constructor) {
    Point<int> center = trapezoid.getCenter();
    EXPECT_EQ(center.getX(), 0);
    EXPECT_EQ(center.getY(), 0);
}

TEST_F(TrapezoidTest, Area) {
    EXPECT_DOUBLE_EQ(trapezoid.area(), 18.0);
}

TEST_F(TrapezoidTest, DoubleConversion) {
    auto area = double(trapezoid);
    EXPECT_DOUBLE_EQ(area, 18.0);
}

TEST_F(TrapezoidTest, Clone) {
    auto cloned = trapezoid.clone();
    EXPECT_DOUBLE_EQ(cloned->area(), trapezoid.area());

    Point<int> clonedCenter = cloned->getCenter();
    EXPECT_EQ(clonedCenter.getX(), testCenter.getX());
    EXPECT_EQ(clonedCenter.getY(), testCenter.getY());
}

TEST_F(TrapezoidTest, Comparison) {
    Trapezoid<int> smaller(Point<int>(1, 1), 2, 4, 2);
    Trapezoid<int> equal(Point<int>(2, 2), 6, 6, 3);

    EXPECT_TRUE(trapezoid > smaller);
    EXPECT_FALSE(trapezoid < smaller);
    EXPECT_TRUE(trapezoid == equal);
}

TEST_F(TrapezoidTest, DifferentTypes) {
    Trapezoid<double> doubleTrap(Point<double>(0.5, 0.5), 4.0, 8.0, 3.0);
    EXPECT_DOUBLE_EQ(doubleTrap.area(), 18.0);

    Trapezoid<float> floatTrap(Point<float>(0.5f, 0.5f), 4.0f, 8.0f, 3.0f);
    EXPECT_FLOAT_EQ(floatTrap.area(), 18.0f);
}


TEST_F(TrapezoidTest, EdgeCases) {
    Trapezoid<int> rectangle(Point<int>(0, 0), 5, 5, 3);
    EXPECT_DOUBLE_EQ(rectangle.area(), 15.0);

    Trapezoid<int> minimal(Point<int>(0, 0), 1, 1, 1);
    EXPECT_DOUBLE_EQ(minimal.area(), 1.0);
}

TEST_F(TrapezoidTest, InvalidDimensions) {
    EXPECT_THROW({
                     Trapezoid<int> trap(testCenter, -4, 8, 3);
                 }, std::invalid_argument);

    EXPECT_THROW({
                     Trapezoid<int> trap(testCenter, 4, -8, 3);
                 }, std::invalid_argument);

    EXPECT_THROW({
                     Trapezoid<int> trap(testCenter, 4, 8, -3);
                 }, std::invalid_argument);

    EXPECT_THROW({
                     Trapezoid<int> trap(testCenter, 0, 8, 3);
                 }, std::invalid_argument);

    EXPECT_THROW({
                     Trapezoid<int> trap(testCenter, 4, 0, 3);
                 }, std::invalid_argument);

    EXPECT_THROW({
                     Trapezoid<int> trap(testCenter, 4, 8, 0);
                 }, std::invalid_argument);
}
