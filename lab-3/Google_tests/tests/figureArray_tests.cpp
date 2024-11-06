#include <gtest/gtest.h>
#include "figureArray.h"
#include "triangle.h"
#include "square.h"
#include "rectangle.h"
#include <cmath>

class FigureArrayTest : public ::testing::Test {
protected:
    FigureArray *array;
    const double EPSILON = 1e-10;

    void SetUp() override {
        array = new FigureArray();
        array->add(new Triangle(0, 0, 6));
        array->add(new Square(0, 0, 5));
        array->add(new Rectangle(0, 0, 4, 5));
    }

    void TearDown() override {
        delete array;
    }
};

TEST_F(FigureArrayTest, TotalArea) {
    double expectedArea = (6.0 * 6.0 * std::sqrt(3.0)) / 4 + 25.0 + 20.0;
    EXPECT_NEAR(array->getTotalArea(), expectedArea, EPSILON);
}

TEST_F(FigureArrayTest, Remove) {
    array->remove(1);
    double expectedArea = (6.0 * 6.0 * std::sqrt(3.0)) / 4 + 20.0;
    EXPECT_NEAR(array->getTotalArea(), expectedArea, EPSILON);
}

TEST_F(FigureArrayTest, AddFigure) {
    array->add(new Square(0, 0, 2));
    double expectedArea = (6.0 * 6.0 * std::sqrt(3.0)) / 4 + 25.0 + 20.0 + 4.0;
    EXPECT_NEAR(array->getTotalArea(), expectedArea, EPSILON);
}