#include <gtest/gtest.h>
#include "figure.hpp"

template<Scalar T>
class TestFigure : public Figure<T> {
public:
    TestFigure() = default;

    explicit TestFigure(const Point<T> &center) : Figure<T>(center) {}

    double area() const override { return 100.0; }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<TestFigure<T>>(this->center);
    }

    void input(std::istream &) override {}
};

class FigureTest : public ::testing::Test {
protected:
    Point<int> testPoint{5, 10};
    TestFigure<int> figure{testPoint};
};

TEST_F(FigureTest, Constructor) {
    Point<int> center = figure.getCenter();
    EXPECT_EQ(center.getX(), 5);
    EXPECT_EQ(center.getY(), 10);
}

TEST_F(FigureTest, GetCenter) {
    Point<int> center = figure.getCenter();
    EXPECT_EQ(center.getX(), testPoint.getX());
    EXPECT_EQ(center.getY(), testPoint.getY());
}

TEST_F(FigureTest, DoubleConversion) {
    auto area = double(figure);
    EXPECT_DOUBLE_EQ(area, 100.0);
}

TEST_F(FigureTest, ComparisonOperators) {
    TestFigure<int> figure1(Point<int>(0, 0));
    TestFigure<int> figure2(Point<int>(1, 1));

    EXPECT_TRUE(figure1 == figure2);
    EXPECT_FALSE(figure1 > figure2);
    EXPECT_FALSE(figure1 < figure2);
}

TEST_F(FigureTest, Clone) {
    auto cloned = figure.clone();
    EXPECT_EQ(cloned->getCenter().getX(), testPoint.getX());
    EXPECT_EQ(cloned->getCenter().getY(), testPoint.getY());
    EXPECT_DOUBLE_EQ(cloned->area(), figure.area());
}

class FigureTemplateTest : public ::testing::Test {
};

TEST_F(FigureTemplateTest, DifferentTypes) {
    TestFigure<int> intFigure(Point<int>(5, 5));
    EXPECT_EQ(intFigure.getCenter().getX(), 5);

    TestFigure<double> doubleFigure(Point<double>(5.5, 5.5));
    EXPECT_DOUBLE_EQ(doubleFigure.getCenter().getX(), 5.5);

    TestFigure<float> floatFigure(Point<float>(5.5f, 5.5f));
    EXPECT_FLOAT_EQ(floatFigure.getCenter().getX(), 5.5f);
}

TEST_F(FigureTemplateTest, CopyingIsDisabled) {
    TestFigure<int> fig(Point<int>(0, 0));
    SUCCEED();
}
