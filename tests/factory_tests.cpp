#include "factory.hpp"
#include "factory_mock.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

struct base { virtual ~base() {} };
struct derived : public base {};

using base_factory = expressive::factory<base>;

TEST(factory_tests, trivial_construct)
{
    auto factory = base_factory::bind<derived>();
    auto object = factory.create();

    EXPECT_TRUE(bool(object));
    EXPECT_TRUE(dynamic_cast<derived*>(object.get()));
}

struct derived_with_some_ctor_args : public base
{
    derived_with_some_ctor_args(int a, int b) : a(a), b(b) {}
    int a;
    int b;
};

void expect_typed_object_to_be_filled(const base & object)
{
    const auto & typed_object = dynamic_cast<const derived_with_some_ctor_args&>(object);

    EXPECT_EQ(1, typed_object.a);
    EXPECT_EQ(2, typed_object.b);
}

TEST(factory_tests, args_are_binded_during_factory_construction)
{
    auto factory = base_factory::bind<derived_with_some_ctor_args, int, int>(1, 2);
    auto object = factory.create();

    EXPECT_TRUE(bool(object));
    expect_typed_object_to_be_filled(*object);
}

using base_factory_with_arg = expressive::factory<base, int>;

TEST(factory_tests, one_arg_is_binded_while_the_second_one_is_provided_in_create)
{
    using namespace std::placeholders;
    auto factory = base_factory_with_arg::bind<derived_with_some_ctor_args, int, int>(_1, 2);
    auto object = factory.create(1);

    EXPECT_TRUE(bool(object));
    expect_typed_object_to_be_filled(*object);
}

//TEST(factory_tests, factory_mock_with_one_arg_is_usable)
//{
//    factory_mock<base, int> factory;
//
//    EXPECT_CALL(factory, create(2)).WillOnce(Return(std::shared_ptr<base>{}));
//    factory.create(2);
//}

TEST(factory_tests, factory_mock_with_two_args_is_usable)
{
    factory_mock<base, int, int> factory;

    EXPECT_CALL(factory, create(1, 2)).WillOnce(Return(std::shared_ptr<base>{}));
    factory.create(1, 2);
}
