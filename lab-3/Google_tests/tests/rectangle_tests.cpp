#include <gtest/gtest.h>
#include "rectangle.h"
#include "exceptions.h"
#include <sstream>

class RectangleTest : public ::testing::Test {
protected:
    const double EPSILON = 1e-10;
};

TEST_F(RectangleTest, DefaultConstructor) {
    Rectangle rect;
    auto center = rect.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 0);
    EXPECT_DOUBLE_EQ(center.second, 0);
}

TEST_F(RectangleTest, ParameterizedConstructor) {
    Rectangle rect(1, 2, 3, 4);  // x, y, width, height
    auto center = rect.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 1);
    EXPECT_DOUBLE_EQ(center.second, 2);
}

TEST_F(RectangleTest, Area) {
    Rectangle rect(0, 0, 2, 3);
    EXPECT_DOUBLE_EQ(rect.getArea(), 6.0);  // 2 * 3 = 6
}

TEST_F(RectangleTest, Vertices) {
    Rectangle rect(0, 0, 2, 4);
    auto vertices = rect.getVertices();

    ASSERT_EQ(vertices.size(), 4);

    double half_width = 1.0;
    double half_height = 2.0;

    EXPECT_NEAR(vertices[0].first, -half_width, EPSILON);
    EXPECT_NEAR(vertices[0].second, half_height, EPSILON);

    EXPECT_NEAR(vertices[1].first, half_width, EPSILON);
    EXPECT_NEAR(vertices[1].second, half_height, EPSILON);

    EXPECT_NEAR(vertices[2].first, half_width, EPSILON);
    EXPECT_NEAR(vertices[2].second, -half_height, EPSILON);

    EXPECT_NEAR(vertices[3].first, -half_width, EPSILON);
    EXPECT_NEAR(vertices[3].second, -half_height, EPSILON);
}

TEST_F(RectangleTest, Equality) {
    Rectangle rect1(1, 2, 3, 4);
    Rectangle rect2(1, 2, 3, 4);
    Rectangle rect3(1, 2, 3, 5);
    Rectangle rect4(0, 2, 3, 4);
    Rectangle rect5(1, 2, 4, 4);

    EXPECT_TRUE(rect1 == rect2);
    EXPECT_FALSE(rect1 == rect3);
    EXPECT_FALSE(rect1 == rect4);
    EXPECT_FALSE(rect1 == rect5);
}

TEST_F(RectangleTest, Clone) {
    Rectangle rect1(1, 2, 3, 4);
    std::unique_ptr<Figure> rect2(rect1.clone());

    EXPECT_TRUE(*rect2 == rect1);
}

TEST_F(RectangleTest, Output) {
    Rectangle rect(1, 2, 3, 4);
    std::stringstream ss;
    ss << rect;
    std::string output = ss.str();

    EXPECT_TRUE(output.find("Center: (1, 2)") != std::string::npos);
    EXPECT_TRUE(output.find("Width: 3") != std::string::npos);
    EXPECT_TRUE(output.find("Height: 4") != std::string::npos);
    EXPECT_TRUE(output.find("Area: 12") != std::string::npos);
    EXPECT_TRUE(output.find("Vertices:") != std::string::npos);
}

TEST_F(RectangleTest, Input) {
    std::stringstream ss;
    ss << "1 2\n" << "3 4\n";

    Rectangle rect;
    ss >> rect;

    auto center = rect.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 1);
    EXPECT_DOUBLE_EQ(center.second, 2);
}

TEST_F(RectangleTest, NegativeSideException) {
    EXPECT_THROW({
                     Rectangle rect(0, 0, -1, 2);
                 }, NegativeSideException);

    EXPECT_THROW({
                     Rectangle rect(0, 0, 2, -1);
                 }, NegativeSideException);

    std::stringstream ss;
    ss << "0 0\n" << "-1 2\n";
    Rectangle rect;
    EXPECT_THROW({
                     ss >> rect;
                 }, NegativeSideException);
}