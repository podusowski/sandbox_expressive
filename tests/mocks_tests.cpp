#include "expressive/testing/mocks.hpp"

#include <gtest/gtest.h>

struct foo
{
    MOCK_METHOD0(bar, void());
    virtual ~foo() = default;
};

TEST(mocks_tests, mocks_of_one_type_are_constructed_on_use)
{
    expressive::mocks<foo> mocks;

    auto first_foo_mock = mocks.first<foo>();
    auto second_foo_mock = mocks.second<foo>();
    auto third_foo_mock = mocks.third<foo>();

    EXPECT_TRUE(bool(first_foo_mock));
    EXPECT_TRUE(bool(second_foo_mock));

    auto second_ref_for_first_foo_mock = mocks.first<foo>();

    EXPECT_EQ(first_foo_mock.get(), second_ref_for_first_foo_mock.get());
    EXPECT_NE(first_foo_mock.get(), second_foo_mock.get());
    EXPECT_NE(first_foo_mock.get(), third_foo_mock.get());
}

struct bar
{
    virtual ~bar() = default;
};

TEST(mocks_tests, mocks_of_different_types_are_constructed_on_use)
{
    expressive::mocks<foo, bar> mocks;

    auto first_foo_mock = mocks.first<foo>();
    auto second_bar_mock = mocks.second<bar>();

    EXPECT_TRUE(bool(first_foo_mock));
    EXPECT_TRUE(bool(second_bar_mock));
}

TEST(mocks_tests, mocks_are_strict_mocks)
{
    expressive::mocks<foo> mocks;

    std::shared_ptr<testing::StrictMock<foo>> first_foo_mock = mocks.first<foo>();

    EXPECT_TRUE(bool(first_foo_mock));
}

struct object_with_dependencies
{
    object_with_dependencies(std::shared_ptr<foo> foo,
                             std::shared_ptr<bar>) : m_foo(foo)
    {
    }

    auto get_foo()
    {
        return m_foo;
    }

    auto call_foo()
    {
        m_foo->bar();
    }

private:
    std::shared_ptr<foo> m_foo;
};

struct concrete_object_with_dependencies_test_suite : public expressive::object_with_dependencies_test_suite<object_with_dependencies, foo, bar>
{
};

TEST_F(concrete_object_with_dependencies_test_suite, construct)
{
    EXPECT_EQ(typeid(object_with_dependencies), typeid(sut()));
    EXPECT_NE(nullptr, sut().get_foo());

    EXPECT_CALL(*mock<foo>(), bar());
    sut().call_foo();
}
