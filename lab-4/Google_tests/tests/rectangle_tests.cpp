#include <gtest/gtest.h>
#include "rectangle.hpp"

class RectangleTest : public ::testing::Test {
protected:
    Point<int> testCenter{1, 2};
    Rectangle<int> validRect{testCenter, 4, 3};
};

TEST_F(RectangleTest, ValidConstruction) {
    EXPECT_NO_THROW({
                        Rectangle<int> rect(testCenter, 4, 3);
                    });

    Point<int> center = validRect.getCenter();
    EXPECT_EQ(center.getX(), testCenter.getX());
    EXPECT_EQ(center.getY(), testCenter.getY());
}

TEST_F(RectangleTest, InvalidConstruction) {
    EXPECT_THROW({
                     Rectangle<int> rect(testCenter, -4, 3);
                 }, std::invalid_argument);

    EXPECT_THROW({
                     Rectangle<int> rect(testCenter, 4, -3);
                 }, std::invalid_argument);

    EXPECT_THROW({
                     Rectangle<int> rect(testCenter, 0, 3);
                 }, std::invalid_argument);

    EXPECT_THROW({
                     Rectangle<int> rect(testCenter, 4, 0);
                 }, std::invalid_argument);

    EXPECT_THROW({
                     Rectangle<int> rect(testCenter, -4, -3);
                 }, std::invalid_argument);
}

TEST_F(RectangleTest, Area) {
    EXPECT_DOUBLE_EQ(validRect.area(), 12.0);

    Rectangle<int> square(testCenter, 5, 5);
    EXPECT_DOUBLE_EQ(square.area(), 25.0);

    Rectangle<int> minimal(testCenter, 1, 1);
    EXPECT_DOUBLE_EQ(minimal.area(), 1.0);
}

TEST_F(RectangleTest, Clone) {
    auto cloned = validRect.clone();

    EXPECT_NE(&validRect, cloned.get());

    EXPECT_DOUBLE_EQ(cloned->area(), validRect.area());

    Point<int> clonedCenter = cloned->getCenter();
    EXPECT_EQ(clonedCenter.getX(), testCenter.getX());
    EXPECT_EQ(clonedCenter.getY(), testCenter.getY());
}

TEST_F(RectangleTest, Comparison) {
    Rectangle<int> smaller(testCenter, 2, 2);

    Rectangle<int> equal(testCenter, 6, 2);

    Rectangle<int> larger(testCenter, 5, 5);

    EXPECT_TRUE(validRect > smaller);
    EXPECT_TRUE(smaller < validRect);
    EXPECT_TRUE(validRect == equal);
    EXPECT_TRUE(validRect < larger);
}

TEST_F(RectangleTest, DifferentTypes) {
    Rectangle<double> doubleRect(Point<double>(0.5, 0.5), 4.0, 3.0);
    EXPECT_DOUBLE_EQ(doubleRect.area(), 12.0);

    Rectangle<float> floatRect(Point<float>(0.5f, 0.5f), 4.0f, 3.0f);
    EXPECT_FLOAT_EQ(floatRect.area(), 12.0f);
}

TEST_F(RectangleTest, DoubleConversion) {
    auto area = double(validRect);
    EXPECT_DOUBLE_EQ(area, 12.0);
}

TEST_F(RectangleTest, TypeLimits) {
    Rectangle<int> maxRect(testCenter, std::numeric_limits<int>::max(), 1);
    EXPECT_GT(maxRect.area(), 0);

    Rectangle<int> minRect(testCenter, 1, 1);
    EXPECT_DOUBLE_EQ(minRect.area(), 1.0);
}

TEST_F(RectangleTest, SpecialCases) {
    Rectangle<int> square(testCenter, 5, 5);
    EXPECT_DOUBLE_EQ(square.area(), 25.0);

    Rectangle<int> long_rect(testCenter, 1000, 1);
    EXPECT_DOUBLE_EQ(long_rect.area(), 1000.0);

    Rectangle<int> tall_rect(testCenter, 1, 1000);
    EXPECT_DOUBLE_EQ(tall_rect.area(), 1000.0);
}
