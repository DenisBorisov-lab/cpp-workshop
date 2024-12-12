#include <gtest/gtest.h>
#include "../include/CustomMemoryResource.h"
#include "../include/Stack.h"

TEST(StackTest, BasicIntTest) {
    CustomMemoryResource customResource(500);
    std::pmr::polymorphic_allocator<int> allocator(&customResource);
    Stack<int, std::pmr::polymorphic_allocator<int>> stack(4, allocator);
    stack.push(10);
    stack.push(20);
    stack.push(30);
    ASSERT_EQ(stack.get_size(), 3);
    ASSERT_EQ(stack.top(), 30);
    stack.pop();
    ASSERT_EQ(stack.top(), 20);
    stack.pop();
    ASSERT_EQ(stack.top(), 10);
    stack.pop();
    ASSERT_EQ(stack.get_size(), 0);
}

TEST(StackTest, OverflowTest) {
    CustomMemoryResource customResource(500);
    std::pmr::polymorphic_allocator<int> allocator(&customResource);
    Stack<int, std::pmr::polymorphic_allocator<int>> stack(2, allocator);
    stack.push(1);
    stack.push(2);
    ASSERT_THROW(stack.push(3), std::runtime_error);
}

TEST(StackTest, UnderflowTest) {
    CustomMemoryResource customResource(500);
    std::pmr::polymorphic_allocator<int> allocator(&customResource);
    Stack<int, std::pmr::polymorphic_allocator<int>> stack(2, allocator);
    ASSERT_THROW(stack.pop(), std::runtime_error);
}

TEST(StackTest, ComplexTypeTest) {
    struct ComplexType {
        int id;
        std::string name;
        double value;

        ComplexType(int i, const std::string &n, double v)
                : id(i), name(n), value(v) {}
    };

    CustomMemoryResource customResource(2048);
    std::pmr::polymorphic_allocator<ComplexType> allocator(&customResource);
    Stack<ComplexType, std::pmr::polymorphic_allocator<ComplexType>> stack(4, allocator);

    stack.push(ComplexType(1, "Item1", 10.5));
    stack.push(ComplexType(2, "Item2", 20.5));

    ASSERT_EQ(stack.get_size(), 2);
    ASSERT_EQ(stack.top().id, 2);
    ASSERT_EQ(stack.top().name, "Item2");
    ASSERT_DOUBLE_EQ(stack.top().value, 20.5);

    stack.pop();
    ASSERT_EQ(stack.top().id, 1);
    ASSERT_EQ(stack.top().name, "Item1");
    ASSERT_DOUBLE_EQ(stack.top().value, 10.5);
}

TEST(StackTest, IteratorTest) {
    CustomMemoryResource customResource(500);
    std::pmr::polymorphic_allocator<int> allocator(&customResource);
    Stack<int, std::pmr::polymorphic_allocator<int>> stack(5, allocator);
    stack.push(1);
    stack.push(2);
    stack.push(3);

    int expected_value = 1;
    for (auto it = stack.begin(); it != stack.end(); ++it) {
        ASSERT_EQ(*it, expected_value++);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
