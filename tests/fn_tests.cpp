#include "expressive/fn.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <tuple>

using namespace std::placeholders;

TEST(fn_tests, one_param)
{
    const auto f = fn [](int i)
                      {
                          return i + 1;
                      };

    EXPECT_EQ(2, f(1));
    EXPECT_EQ(2, f(_1)(1));
    EXPECT_EQ(2, f(_1)(_1)(1));
}

TEST(fn_tests, two_params)
{
    const auto f = fn [](int i, int j)
                      {
                          return i / j;
                      };

    EXPECT_EQ(2, f(4, 2));
    EXPECT_EQ(2, f(4)(2));
//    EXPECT_EQ(2, f(_1, _2)(4, 2));
    EXPECT_EQ(2, f(4, _1)(2));
//    EXPECT_EQ(2, f(_1, 2)(2));
}

//namespace
//{
//
//struct tuple_maker
//{
//    template<class... Args>
//    auto sum(Args... args) const
//    {
//        return std::make_tuple(args...);
//    }
//};
//
//}
//
//TEST(fn_tests, variadic)
//{
//    const auto f = fn tuple_maker{};
//
//    EXPECT_EQ(std::make_tuple(1, 2, 3), f(1, 2, 3));
//}

namespace
{

auto add(int a, int b)
{
    return a + b;
}

}

TEST(fn_tests, can_be_called_with)
{
    EXPECT_EQ(std::true_type{}, expressive::callable_with(add, 1, 2));
    EXPECT_EQ(std::true_type{}, expressive::callable_with(add, 1, 2.0));

    EXPECT_EQ(std::false_type{}, expressive::callable_with(add, 1));
    EXPECT_EQ(std::false_type{}, expressive::callable_with(add, 1, 2, 3));
    EXPECT_EQ(std::false_type{}, expressive::callable_with(add, 1, "2"));
}
