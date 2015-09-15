#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "expressive/functional/method.hpp"

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

TEST(method_tests, method_from_const_object_is_called)
{
    const object_with_const_method_mock object;
    auto method = expressive::functional::method(object, &object_with_const_method_mock::foo);

    EXPECT_CALL(object, foo(argument)).WillOnce(Return(result));

    EXPECT_EQ(result, method(argument));
}
