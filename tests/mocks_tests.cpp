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
    auto second_foo_mock = mocks.second<foo_mock>();
    auto third_foo_mock = mocks.third<foo_mock>();

    EXPECT_TRUE(bool(first_foo_mock));
    EXPECT_TRUE(bool(second_foo_mock));

    auto second_ref_for_first_foo_mock = mocks.first<foo_mock>();

    EXPECT_EQ(first_foo_mock.get(), second_ref_for_first_foo_mock.get());
    EXPECT_NE(first_foo_mock.get(), second_foo_mock.get());
    EXPECT_NE(first_foo_mock.get(), third_foo_mock.get());
}

struct bar_mock
{
    virtual ~bar_mock() = default;
};

TEST(mocks_tests, mocks_of_different_types_are_constructed_on_use)
{
    expressive::mocks<foo_mock, bar_mock> mocks;

    auto first_foo_mock = mocks.first<foo_mock>();
    auto second_bar_mock = mocks.second<bar_mock>();

    EXPECT_TRUE(bool(first_foo_mock));
    EXPECT_TRUE(bool(second_bar_mock));
}

TEST(mocks_tests, mocks_are_strict_mocks)
{
    expressive::mocks<foo_mock> mocks;

    std::shared_ptr<testing::StrictMock<foo_mock>> first_foo_mock = mocks.first<foo_mock>();

    EXPECT_TRUE(bool(first_foo_mock));
}
