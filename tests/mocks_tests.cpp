#include "expressive/testing/mocks.hpp"

#include <gtest/gtest.h>

struct foo_mock
{
    virtual ~foo_mock() = default;
};

TEST(mocks_tests, mocks_of_one_type_are_constructed_on_use)
{
    expressive::mocks<foo_mock> mocks;

    auto first_foo_mock = mocks.first<foo_mock>();

    EXPECT_TRUE(bool(first_foo_mock));

    auto second_ref_for_first_foo_mock = mocks.first<foo_mock>();

    EXPECT_EQ(first_foo_mock.get(), second_ref_for_first_foo_mock.get());
}
