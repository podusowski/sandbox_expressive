#include "expressive/fn.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <tuple>

#include <iostream>
#include "expressive/make_string.hpp"

using namespace std::placeholders;
using namespace expressive;

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
    EXPECT_EQ(2, f(4)(_1)(2));

//    EXPECT_EQ(2, f(_1)(4)(2));
//    EXPECT_EQ(2, f(_1, _2)(4, 2));

//    EXPECT_EQ(2, f(4, _1)(2));

    //EXPECT_EQ(2, f(_1, 2)(4));
}

TEST(fn_tests, three_params)
{
    const auto f = fn [](int i, int j, int k)
                      {
                          return (i - j) / k;
                      };

    EXPECT_EQ(25, f(100, 50, 2));
    EXPECT_EQ(25, f(100, 50)(2));
    EXPECT_EQ(25, f(100)(50, 2));
    EXPECT_EQ(25, f(100)(50)(2));
}

namespace
{

struct tuple_maker
{
    template<class... Args>
    auto operator () (Args... args) const
    {
        return std::make_tuple(args...);
    }
};

} // namespace

TEST(fn_tests, variadic)
{
    const auto f = fn tuple_maker{};

    EXPECT_EQ(std::make_tuple(1, 2, 3), f(1, 2, 3));
}

namespace
{

auto add(int a, int b)
{
    return a + b;
}

} // namespace

TEST(fn_tests, function_can_be_called_with)
{
    EXPECT_TRUE(expressive::callable_with(add, 1, 2));
    EXPECT_TRUE(expressive::callable_with(add, 1, 2.0));

    EXPECT_FALSE(expressive::callable_with(add, 1));
    EXPECT_FALSE(expressive::callable_with(add, 1, 2, 3));
    EXPECT_FALSE(expressive::callable_with(add, 1, "2"));
}

TEST(fn_tests, bind_expression_can_be_called_with)
{
    const auto b = std::bind(&add, _1, _2);

    EXPECT_TRUE(expressive::callable_with(b, 1, 2));
    EXPECT_TRUE(expressive::callable_with(b, 1, 2.0));

    EXPECT_FALSE(expressive::callable_with(b, 1));
    EXPECT_TRUE(expressive::callable_with(b, 1, 2, 3)); // bind expression is callable with more number of params!
    EXPECT_FALSE(expressive::callable_with(b, 1, "2"));
}

TEST(fn_tests, composition)
{
    const auto a = fn [](auto i) { return i + 1; };
    const auto s = fn [](auto i) { return make_string(i); };
    const auto g = a | s;

    EXPECT_EQ("2", g(1));
}

//TEST(fn_tests, fmap)
//{
//    const auto odd = fn [](auto i) { return i % 2 == 0; };
//    const auto in = std::vector<int>{1, 2, 3};
//
//    const auto out = in >>= odd;
//
//    EXPECT_EQ((std::vector<bool>{false, true, false}), out);
//}
