#include "expressive/fn.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std::placeholders;

TEST(fn_tests, one_param)
{
    const auto f = fn [](int i)
                      {
                          return i + 1;
                      };

    EXPECT_EQ(1, f(1));
    EXPECT_EQ(1, f(_1)(1));
}
