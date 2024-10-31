#include <gtest/gtest.h>
#include "hex.h"

TEST(HexConstructorTest, DefaultConstructor) {
    Hex h;
    EXPECT_EQ(h.getSize(), 0);
    EXPECT_EQ(h.toString(), "0");
}

TEST(HexConstructorTest, SizeValueConstructor) {
    Hex h(3, 5);
    EXPECT_EQ(h.getSize(), 3);
    EXPECT_EQ(h.toString(), "555");
}

TEST(HexConstructorTest, InitializerListConstructor) {
    Hex h({1, 2, 3});
    EXPECT_EQ(h.getSize(), 3);
    EXPECT_EQ(h.toString(), "321");
}

TEST(HexConstructorTest, StringConstructor) {
    Hex h1("ABC");
    EXPECT_EQ(h1.toString(), "ABC");

    Hex h2("123");
    EXPECT_EQ(h2.toString(), "123");

    Hex h3("aBC");
    EXPECT_EQ(h3.toString(), "ABC");
}

TEST(HexConstructorTest, CopyConstructor) {
    Hex original("ABC");
    Hex copy(original);
    EXPECT_EQ(copy.toString(), "ABC");
}

TEST(HexConstructorTest, MoveConstructor) {
    Hex original("ABC");
    Hex moved(std::move(original));
    EXPECT_EQ(moved.toString(), "ABC");
    EXPECT_EQ(original.getSize(), 0);
}

// Тесты на исключения в конструкторах
TEST(HexConstructorTest, InvalidHexDigit) {
    EXPECT_THROW(Hex(1, 16), std::invalid_argument);
    EXPECT_THROW(Hex({1, 16, 3}), std::invalid_argument);
    EXPECT_THROW(Hex("GHI"), std::invalid_argument);
}

// Тесты арифметических операций
TEST(HexArithmeticTest, Addition) {
    Hex a("A5");
    Hex b("3F");
    Hex sum = a.add(b);
    EXPECT_EQ(sum.toString(), "E4");
}

TEST(HexArithmeticTest, AdditionWithCarry) {
    Hex a("FF");
    Hex b("1");
    Hex sum = a.add(b);
    EXPECT_EQ(sum.toString(), "100");
}

TEST(HexArithmeticTest, Subtraction) {
    Hex a("A5");
    Hex b("3F");
    Hex diff = a.add(b);
    EXPECT_EQ(diff.toString(), "E4");
}

TEST(HexArithmeticTest, SubtractionWithBorrow) {
    Hex a("100");
    Hex b("1");
    Hex diff = a.subtract(b);
    EXPECT_EQ(diff.toString(), "FF");
}

TEST(HexArithmeticTest, SubtractionThrows) {
    Hex a("3F");
    Hex b("A5");
    EXPECT_THROW(a.subtract(b), std::invalid_argument);
}

// Тесты операций присваивания
TEST(HexAssignmentTest, AddAssign) {
    Hex a("A5");
    Hex b("3F");
    a.addAssign(b);
    EXPECT_EQ(a.toString(), "E4");
}

TEST(HexAssignmentTest, SubtractAssign) {
    Hex a("A5");
    Hex b("3F");
    a.subtractAssign(b);
    EXPECT_EQ(a.toString(), "66");
}

// Тесты операций сравнения
TEST(HexComparisonTest, GreaterThan) {
    Hex a("A5");
    Hex b("3F");
    EXPECT_TRUE(a.isGreaterThan(b));
    EXPECT_FALSE(b.isGreaterThan(a));
}

TEST(HexComparisonTest, LessThan) {
    Hex a("A5");
    Hex b("3F");
    EXPECT_FALSE(a.isLessThan(b));
    EXPECT_TRUE(b.isLessThan(a));
}

TEST(HexComparisonTest, Equal) {
    Hex a("A5");
    Hex b("A5");
    Hex c("3F");
    EXPECT_TRUE(a.isEqual(b));
    EXPECT_FALSE(a.isEqual(c));
}

// Тесты методов доступа
TEST(HexAccessTest, GetDigit) {
    Hex h("ABC");
    EXPECT_EQ(h.getDigit(0), 0xC);
    EXPECT_EQ(h.getDigit(1), 0xB);
    EXPECT_EQ(h.getDigit(2), 0xA);
}

TEST(HexAccessTest, GetDigitThrows) {
    Hex h("ABC");
    EXPECT_THROW(h.getDigit(3), std::out_of_range);
}

// Тесты граничных случаев
TEST(HexEdgeCaseTest, EmptyString) {
    Hex h("");
    EXPECT_EQ(h.toString(), "0");
}

TEST(HexEdgeCaseTest, SingleDigit) {
    Hex h("0");
    EXPECT_EQ(h.toString(), "0");
}

TEST(HexEdgeCaseTest, LeadingZeros) {
    Hex h("000ABC");
    EXPECT_EQ(h.toString(), "ABC");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
