#include "../include/factorial.h"
#include <gtest/gtest.h>
#include <cassert>

TEST(FactorialTest, FactorialZero) {
    EXPECT_EQ(factorial(0), 1);
}

TEST(FactorialTest, FactorialOne) {
    EXPECT_EQ(factorial(1), 1);
}

TEST(FactorialTest, FactorialFive) {
    EXPECT_EQ(factorial(5), 120);
}

TEST(FactorialTest, FactorialTen) {
    EXPECT_EQ(factorial(10), 3628800);
}