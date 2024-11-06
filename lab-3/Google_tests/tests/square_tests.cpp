#include <gtest/gtest.h>
#include "square.h"
#include <sstream>
#include "exceptions.h"

class SquareTest : public ::testing::Test {
protected:
    const double EPSILON = 1e-10;
};

TEST_F(SquareTest, DefaultConstructor) {
    Square sq;
    auto center = sq.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 0);
    EXPECT_DOUBLE_EQ(center.second, 0);
}

TEST_F(SquareTest, ParameterizedConstructor) {
    Square sq(1, 2, 3);
    auto center = sq.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 1);
    EXPECT_DOUBLE_EQ(center.second, 2);
}

TEST_F(SquareTest, Area) {
    Square sq(0, 0, 2);
    EXPECT_DOUBLE_EQ(sq.getArea(), 4.0);
}

TEST_F(SquareTest, Vertices) {
    Square sq(0, 0, 2);
    auto vertices = sq.getVertices();

    ASSERT_EQ(vertices.size(), 4);

    double half_side = 1.0;

    EXPECT_NEAR(vertices[0].first, -half_side, EPSILON);
    EXPECT_NEAR(vertices[0].second, half_side, EPSILON);

    EXPECT_NEAR(vertices[1].first, half_side, EPSILON);
    EXPECT_NEAR(vertices[1].second, half_side, EPSILON);

    EXPECT_NEAR(vertices[2].first, half_side, EPSILON);
    EXPECT_NEAR(vertices[2].second, -half_side, EPSILON);

    EXPECT_NEAR(vertices[3].first, -half_side, EPSILON);
    EXPECT_NEAR(vertices[3].second, -half_side, EPSILON);
}

TEST_F(SquareTest, Equality) {
    Square sq1(1, 2, 3);
    Square sq2(1, 2, 3);
    Square sq3(1, 2, 4);
    Square sq4(0, 2, 3);

    EXPECT_TRUE(sq1 == sq2);
    EXPECT_FALSE(sq1 == sq3);
    EXPECT_FALSE(sq1 == sq4);
}

TEST_F(SquareTest, Clone) {
    Square sq1(1, 2, 3);
    std::unique_ptr<Figure> sq2(sq1.clone());

    EXPECT_TRUE(*sq2 == sq1);
}

TEST_F(SquareTest, Output) {
    Square sq(1, 2, 2);
    std::stringstream ss;
    ss << sq;
    std::string output = ss.str();

    EXPECT_TRUE(output.find("Center: (1, 2)") != std::string::npos);
    EXPECT_TRUE(output.find("Side length: 2") != std::string::npos);
    EXPECT_TRUE(output.find("Area: 4") != std::string::npos);
    EXPECT_TRUE(output.find("Vertices:") != std::string::npos);
}

TEST_F(SquareTest, Input) {
    std::stringstream ss;
    ss << "1 2\n" << "3\n";

    Square sq;
    ss >> sq;

    auto center = sq.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 1);
    EXPECT_DOUBLE_EQ(center.second, 2);
}

TEST_F(SquareTest, NegativeSideException) {
    std::stringstream ss;
    ss << "0 0\n" << "-1\n";

    Square sq;
    EXPECT_THROW({ ss >> sq; }, NegativeSideException);
}
