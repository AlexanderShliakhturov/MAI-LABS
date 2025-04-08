#include <gtest/gtest.h>
#include "../include/figures/Triangle.hpp"
#include "../src/figures/Triangle.cpp"

using namespace figures;

TEST(constructor, basic_no_exception) {
    ASSERT_NO_THROW(Triangle(Point(0, 0), Point(1, 0), Point(0, 1)));
}

TEST(constructor, basic_exception) {
    ASSERT_THROW(Triangle(Point(0, 0), Point(10, 0), Point(15, 0)), std::invalid_argument);
}

TEST(constructor, side_size_constructor_no_exception) {
    ASSERT_NO_THROW(Triangle(5));
}

TEST(constructor, side_size_constructor_exception) {
    ASSERT_THROW(Triangle(0), std::invalid_argument);
}

TEST(constructor, through_other) {
    Triangle test_1 (Point(1, 1), Point(10, 1), Point(1, 5));
    Triangle test_2 (test_1);

    EXPECT_TRUE(test_1 == test_2);
    EXPECT_DOUBLE_EQ(test_1.get_side("1_2"), test_2.get_side("1_2"));
}

TEST(constructor, through_other_move) {
    Triangle test_1 (Point(1, 1), Point(10, 1), Point(1, 5));
    Triangle test_2 (std::move(test_1));

    EXPECT_TRUE(test_1 == test_2);
    EXPECT_DOUBLE_EQ(test_1.get_side("1_2"), test_2.get_side("1_2"));
}

TEST(constructor, copy_constructor_equiv) {
    Triangle t1 (Point(2, 2), Point(4, 1), Point(3, 4));
    Triangle t2 (t1);

    EXPECT_TRUE(t1 == t2);
    EXPECT_DOUBLE_EQ(t1.get_side("1_2"), t2.get_side("1_2"));
}

TEST(constructor, move_constructor_equiv) {
    Triangle t1 (Point(2, 2), Point(4, 1), Point(3, 4));
    Triangle t2 (std::move(t1));

    EXPECT_TRUE(t1 == t2);
    EXPECT_DOUBLE_EQ(t1.get_side("1_2"), t2.get_side("1_2"));
}

TEST(constructor, assigment_operator_equiv) {
    Triangle t1 (Point(2, 2), Point(4, 1), Point(3, 4));
    Triangle t2 = t1;

    EXPECT_TRUE(t1 == t2);
    EXPECT_DOUBLE_EQ(t1.get_side("1_2"), t2.get_side("1_2"));
}

TEST(constructor, assigment_operator_move_test) {
    Triangle t1 (Point(2, 2), Point(4, 1), Point(3, 4));
    Triangle t2 = std::move(t1);

    EXPECT_TRUE(t1 == t2);
    EXPECT_DOUBLE_EQ(t1.get_side("1_2"), t2.get_side("1_2"));
}

TEST(basic_operations, copy_assigment) {
    Triangle test_1 (Point(1, 1), Point(10, 1), Point(1, 5));
    Triangle test_2 = test_1;

    EXPECT_TRUE(test_1 == test_2);
    EXPECT_DOUBLE_EQ(test_1.get_side("1_2"), test_2.get_side("1_2"));
}

TEST(basic_operations, move_assigment) {
    Triangle test_1 (Point(1, 1), Point(10, 1), Point(1, 5));
    Triangle test_2 = std::move(test_1);

    EXPECT_TRUE(test_1 == test_2);
    EXPECT_DOUBLE_EQ(test_1.get_side("1_2"), test_2.get_side("1_2"));
}

TEST(basic_operations, calculate_geometric_center) {
    Triangle test (Point(0, 0), Point(3, 0), Point(0, 3));
    Point center = test.calculate_geometric_center();

    EXPECT_DOUBLE_EQ(center.get_x_cord(), 1);
    EXPECT_DOUBLE_EQ(center.get_y_cord(), 1);
}

TEST(basic_operations, calculate_perimeter) {
    Triangle test (Point(0, 0), Point(3, 0), Point(0, 4));
    EXPECT_DOUBLE_EQ(test.calculate_perimeter(), 12);
}

TEST(basic_operations, calculate_area) {
    Triangle test (Point(0, 0), Point(3, 0), Point(0, 4));
    EXPECT_DOUBLE_EQ(test.calculate_area(), 6);
}

TEST(basic_operations, get_side) {
    Triangle test (Point(0, 0), Point(3, 0), Point(0, 4));
    EXPECT_DOUBLE_EQ(test.get_side("1_2"), 3);
}

TEST(basic_operations, operator_double) {
    Triangle test (Point(0, 0), Point(2, 0), Point(0, 2));
    EXPECT_DOUBLE_EQ(double(test), test.calculate_area());
}

TEST(basic_operations, equals_operator_true) {
    Triangle t1 (Point(0, 0), Point(2, 0), Point(0,2));
    Triangle t2 (Point(0, 0), Point(2, 0), Point(0,2));
    EXPECT_TRUE(t1 == t2);
}

TEST(basic_operations, equals_operator_false) {
    Triangle t1 (Point(0, 0), Point(2, 0), Point(0, 2));
    Triangle t2 (Point(0, 0), Point(4, 0), Point(0, 4));
    EXPECT_FALSE(t1 == t2);
}

TEST(basic_operations, not_equals_operator_true) {
    Triangle t1 (Point(0, 0), Point(2, 0), Point(0, 2));
    Triangle t2 (Point(0, 0), Point(4, 0), Point(0, 4));
    EXPECT_TRUE(t1 != t2);
}

TEST(basic_operations, not_equals_operator_false) {
    Triangle t1 (Point(0, 0), Point(2, 0), Point(0, 2));
    Triangle t2 (Point(0, 0), Point(2, 0), Point(0, 2));
    EXPECT_FALSE(t1 != t2);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}