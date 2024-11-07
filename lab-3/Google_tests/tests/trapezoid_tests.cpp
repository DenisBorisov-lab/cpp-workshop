#include <gtest/gtest.h>
#include "trapezoid.h"
#include "exceptions.h"
#include <sstream>

class TrapezoidTest : public ::testing::Test {
protected:
    const double EPSILON = 1e-10;
};

TEST_F(TrapezoidTest, DefaultConstructor) {
    Trapezoid trap;
    EXPECT_DOUBLE_EQ(trap.getTopSide(), 0);
    EXPECT_DOUBLE_EQ(trap.getBottomSide(), 0);
    EXPECT_DOUBLE_EQ(trap.getHeight(), 0);
    auto center = trap.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 0);
    EXPECT_DOUBLE_EQ(center.second, 0);
}

TEST_F(TrapezoidTest, ParameterizedConstructor) {
    Trapezoid trap(1, 2, 3, 5, 4);
    EXPECT_DOUBLE_EQ(trap.getTopSide(), 3);
    EXPECT_DOUBLE_EQ(trap.getBottomSide(), 5);
    EXPECT_DOUBLE_EQ(trap.getHeight(), 4);
    auto center = trap.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 1);
    EXPECT_DOUBLE_EQ(center.second, 2);
}

TEST_F(TrapezoidTest, Area) {
    Trapezoid trap(0, 0, 3, 5, 4);
    double expected_area = (3 + 5) * 4 / 2.0;
    EXPECT_DOUBLE_EQ(trap.getArea(), expected_area);
}

TEST_F(TrapezoidTest, Vertices) {
    Trapezoid trap(0, 0, 2, 4, 2);
    auto vertices = trap.getVertices();

    ASSERT_EQ(vertices.size(), 4);


    EXPECT_NEAR(vertices[0].first, -1, EPSILON);
    EXPECT_NEAR(vertices[0].second, 1, EPSILON);
    EXPECT_NEAR(vertices[1].first, 1, EPSILON);
    EXPECT_NEAR(vertices[1].second, 1, EPSILON);


    EXPECT_NEAR(vertices[2].first, 2, EPSILON);
    EXPECT_NEAR(vertices[2].second, -1, EPSILON);
    EXPECT_NEAR(vertices[3].first, -2, EPSILON);
    EXPECT_NEAR(vertices[3].second, -1, EPSILON);
}

TEST_F(TrapezoidTest, Equality) {
    Trapezoid trap1(1, 2, 3, 5, 4);
    Trapezoid trap2(1, 2, 3, 5, 4);
    Trapezoid trap3(1, 2, 3, 6, 4);
    Trapezoid trap4(1, 2, 2, 5, 4);
    Trapezoid trap5(1, 2, 3, 5, 3);
    Trapezoid trap6(0, 2, 3, 5, 4);

    EXPECT_TRUE(trap1 == trap2);
    EXPECT_FALSE(trap1 == trap3);
    EXPECT_FALSE(trap1 == trap4);
    EXPECT_FALSE(trap1 == trap5);
    EXPECT_FALSE(trap1 == trap6);
}

TEST_F(TrapezoidTest, Clone) {
    Trapezoid trap1(1, 2, 3, 5, 4);
    std::unique_ptr<Figure> trap2(trap1.clone());

    EXPECT_TRUE(*trap2 == trap1);
}

TEST_F(TrapezoidTest, Output) {
    Trapezoid trap(1, 2, 3, 5, 4);
    std::stringstream ss;
    ss << trap;
    std::string output = ss.str();

    EXPECT_TRUE(output.find("Center: (1, 2)") != std::string::npos);
    EXPECT_TRUE(output.find("Top side: 3") != std::string::npos);
    EXPECT_TRUE(output.find("Bottom side: 5") != std::string::npos);
    EXPECT_TRUE(output.find("Height: 4") != std::string::npos);
    EXPECT_TRUE(output.find("Area: 16") != std::string::npos);
    EXPECT_TRUE(output.find("Vertices:") != std::string::npos);
}

TEST_F(TrapezoidTest, Input) {
    std::stringstream ss;
    ss << "1 2\n" << "3 5 4\n";

    Trapezoid trap;
    ss >> trap;

    auto center = trap.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 1);
    EXPECT_DOUBLE_EQ(center.second, 2);
    EXPECT_DOUBLE_EQ(trap.getTopSide(), 3);
    EXPECT_DOUBLE_EQ(trap.getBottomSide(), 5);
    EXPECT_DOUBLE_EQ(trap.getHeight(), 4);
}

TEST_F(TrapezoidTest, NegativeSideException) {
    EXPECT_THROW({
                     Trapezoid trap(0, 0, -1, 5, 4);
                 }, NegativeSideException);

    EXPECT_THROW({
                     Trapezoid trap(0, 0, 3, -5, 4);
                 }, NegativeSideException);

    EXPECT_THROW({
                     Trapezoid trap(0, 0, 3, 5, -4);
                 }, NegativeSideException);

    std::stringstream ss;
    ss << "0 0\n" << "-3 5 4\n";
    Trapezoid trap;
    EXPECT_THROW({
                     ss >> trap;
                 }, NegativeSideException);
}