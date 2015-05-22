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
