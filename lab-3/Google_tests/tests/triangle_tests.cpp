#include <gtest/gtest.h>
#include "triangle.h"
#include "exceptions.h"
#include <sstream>
#include <cmath>

class TriangleTest : public ::testing::Test {
protected:
    const double EPSILON = 1e-10;  // для сравнения double
};

TEST_F(TriangleTest, DefaultConstructor) {
    Triangle tr;
    EXPECT_DOUBLE_EQ(tr.getSide(), 0);
    auto center = tr.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 0);
    EXPECT_DOUBLE_EQ(center.second, 0);
}

TEST_F(TriangleTest, ParameterizedConstructor) {
    Triangle tr(1, 2, 3);
    EXPECT_DOUBLE_EQ(tr.getSide(), 3);
    auto center = tr.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 1);
    EXPECT_DOUBLE_EQ(center.second, 2);
}

TEST_F(TriangleTest, Height) {
    Triangle tr(0, 0, 2);
    double expected_height = std::sqrt(3.0);
    EXPECT_NEAR(tr.getHeight(), expected_height, EPSILON);
}

TEST_F(TriangleTest, Area) {
    Triangle tr(0, 0, 2);
    double expected_area = std::sqrt(3.0);
    EXPECT_NEAR(tr.getArea(), expected_area, EPSILON);
}

TEST_F(TriangleTest, Vertices) {
    Triangle tr(0, 0, 2);
    auto vertices = tr.getVertices();

    ASSERT_EQ(vertices.size(), 3);

    double r = 2 / (2 * std::sqrt(3));

    EXPECT_NEAR(vertices[0].first, 0, EPSILON);
    EXPECT_NEAR(vertices[0].second, r * std::sqrt(3), EPSILON);

    EXPECT_NEAR(vertices[1].first, -1, EPSILON);
    EXPECT_NEAR(vertices[1].second, -r, EPSILON);

    EXPECT_NEAR(vertices[2].first, 1, EPSILON);
    EXPECT_NEAR(vertices[2].second, -r, EPSILON);
}

TEST_F(TriangleTest, Equality) {
    Triangle tr1(1, 2, 3);
    Triangle tr2(1, 2, 3);
    Triangle tr3(1, 2, 4);
    Triangle tr4(0, 2, 3);

    EXPECT_TRUE(tr1 == tr2);
    EXPECT_FALSE(tr1 == tr3);
    EXPECT_FALSE(tr1 == tr4);
}

TEST_F(TriangleTest, Clone) {
    Triangle tr1(1, 2, 3);
    std::unique_ptr<Figure> tr2(tr1.clone());

    EXPECT_TRUE(*tr2 == tr1);
}

TEST_F(TriangleTest, Output) {
    Triangle tr(1, 2, 2);
    std::stringstream ss;
    ss << tr;
    std::string output = ss.str();

    EXPECT_TRUE(output.find("Center: (1, 2)") != std::string::npos);
    EXPECT_TRUE(output.find("Side: 2") != std::string::npos);
    EXPECT_TRUE(output.find("Height:") != std::string::npos);
    EXPECT_TRUE(output.find("Area:") != std::string::npos);
    EXPECT_TRUE(output.find("Vertices:") != std::string::npos);
}

TEST_F(TriangleTest, Input) {
    std::stringstream ss;
    ss << "1 2\n" << "3\n";

    Triangle tr;
    ss >> tr;

    auto center = tr.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 1);
    EXPECT_DOUBLE_EQ(center.second, 2);
    EXPECT_DOUBLE_EQ(tr.getSide(), 3);
}

TEST_F(TriangleTest, NegativeSideException) {
    std::stringstream ss;
    ss << "0 0\n" << "-1\n";

    Triangle tr;
    EXPECT_THROW({
                     ss >> tr;
                 }, NegativeSideException);
}
