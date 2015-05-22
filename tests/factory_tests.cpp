#include "factory.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
    derived_with_some_ctor_args(int a, int b) {}
};

TEST(factory_tests, args_are_binded_during_factory_construction)
{
    auto factory = base_factory::bind<derived_with_some_ctor_args, int, int>(1, 2);
    auto object = factory.create();

    EXPECT_TRUE(bool(object));
    EXPECT_TRUE(dynamic_cast<derived_with_some_ctor_args*>(object.get()));
}