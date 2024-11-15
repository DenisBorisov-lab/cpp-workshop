#include <gtest/gtest.h>
#include "point.hpp"

class PointTest : public ::testing::Test {
protected:
    Point<int> defaultPoint;
    Point<int> testPoint{3, 4};
};


TEST_F(PointTest, DefaultConstructor) {
    EXPECT_EQ(defaultPoint.getX(), 0);
    EXPECT_EQ(defaultPoint.getY(), 0);
}


TEST_F(PointTest, ParameterizedConstructor) {
    EXPECT_EQ(testPoint.getX(), 3);
    EXPECT_EQ(testPoint.getY(), 4);
}


TEST_F(PointTest, Getters) {
    Point<int> point(5, 6);
    EXPECT_EQ(point.getX(), 5);
    EXPECT_EQ(point.getY(), 6);
}


TEST_F(PointTest, Setters) {
    Point<int> point;
    point.setX(7);
    point.setY(8);
    EXPECT_EQ(point.getX(), 7);
    EXPECT_EQ(point.getY(), 8);
}


TEST(PointTemplateTest, DifferentTypes) {

    Point<int> intPoint(1, 2);
    EXPECT_EQ(intPoint.getX(), 1);
    EXPECT_EQ(intPoint.getY(), 2);


    Point<double> doublePoint(1.5, 2.5);
    EXPECT_DOUBLE_EQ(doublePoint.getX(), 1.5);
    EXPECT_DOUBLE_EQ(doublePoint.getY(), 2.5);


    Point<float> floatPoint(1.5f, 2.5f);
    EXPECT_FLOAT_EQ(floatPoint.getX(), 1.5f);
    EXPECT_FLOAT_EQ(floatPoint.getY(), 2.5f);
}


TEST(PointTemplateTest, TypeLimits) {

    Point<int> maxInt(std::numeric_limits<int>::max(),
                      std::numeric_limits<int>::max());
    EXPECT_EQ(maxInt.getX(), std::numeric_limits<int>::max());
    EXPECT_EQ(maxInt.getY(), std::numeric_limits<int>::max());


    Point<int> minInt(std::numeric_limits<int>::min(),
                      std::numeric_limits<int>::min());
    EXPECT_EQ(minInt.getX(), std::numeric_limits<int>::min());
    EXPECT_EQ(minInt.getY(), std::numeric_limits<int>::min());
}


TEST_F(PointTest, Modification) {
    Point<int> point(1, 1);


    point.setX(2);
    EXPECT_EQ(point.getX(), 2);
    EXPECT_EQ(point.getY(), 1);

    point.setY(3);
    EXPECT_EQ(point.getX(), 2);
    EXPECT_EQ(point.getY(), 3);

    point.setX(2);
    point.setY(3);
    EXPECT_EQ(point.getX(), 2);
    EXPECT_EQ(point.getY(), 3);
}

TEST_F(PointTest, NegativeValues) {
    Point<int> point(-5, -10);
    EXPECT_EQ(point.getX(), -5);
    EXPECT_EQ(point.getY(), -10);

    point.setX(-15);
    point.setY(-20);
    EXPECT_EQ(point.getX(), -15);
    EXPECT_EQ(point.getY(), -20);
}


TEST_F(PointTest, ZeroValues) {
    Point<int> point(0, 0);
    EXPECT_EQ(point.getX(), 0);
    EXPECT_EQ(point.getY(), 0);
}
