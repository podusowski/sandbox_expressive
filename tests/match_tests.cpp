#include "functional/match.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct action_mock
{
    MOCK_METHOD0(call, void());
};

using action_strict_mock = testing::StrictMock<action_mock>;

TEST(match_tests, simple_match_by_value)
{
    action_strict_mock expected;
    action_strict_mock unexpected;

    auto i = 1;

    EXPECT_CALL(expected, call());
    functional::match(i)
                     (1, [&] { expected.call(); });

    EXPECT_CALL(expected, call());
    functional::match(i)
                     (1, [&] { expected.call(); })
                     (2, [&] { unexpected.call(); });

    EXPECT_CALL(expected, call());
    functional::match(i)
                     (2, [&] { unexpected.call(); })
                     (1, [&] { expected.call(); });

    functional::match(i)
                     (2, [&] { unexpected.call(); });
}
