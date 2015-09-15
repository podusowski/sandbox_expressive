#include "expressive/functional/method.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

using namespace testing;

namespace
{

const auto result = 1;
const auto argument = 5;

} // namespace

struct object_with_const_method_mock
{
    MOCK_CONST_METHOD1(foo, int(int));
};

TEST(method_tests, method_from_const_object_passed_by_raw_pointer_is_called)
{
    const object_with_const_method_mock object;
    auto method = expressive::functional::method(&object, &object_with_const_method_mock::foo);

    EXPECT_CALL(object, foo(argument)).WillOnce(Return(result));
    EXPECT_EQ(result, method(argument));
}

TEST(method_tests, method_from_const_object_passed_by_sp_is_called)
{
    const auto object = std::make_shared<object_with_const_method_mock>();

    {
        const auto method = expressive::functional::method(object, &object_with_const_method_mock::foo);

        EXPECT_FALSE(object.unique());

        EXPECT_CALL(*object, foo(argument)).WillOnce(Return(result));
        EXPECT_EQ(result, method(argument));
    }

    EXPECT_TRUE(object.unique());
}

struct object_with_method_mock
{
    MOCK_METHOD1(foo, int(int));
};

TEST(method_tests, method_from_object_passed_by_raw_pointer_is_called)
{
    object_with_method_mock object;
    auto method = expressive::functional::method(&object, &object_with_method_mock::foo);

    EXPECT_CALL(object, foo(argument)).WillOnce(Return(result));
    EXPECT_EQ(result, method(argument));
}
