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

TEST(match_tests, match_by_predicate)
{
    action_strict_mock expected;
    action_strict_mock unexpected;

    auto is_even = [] (int i) -> bool
    {
        return i % 2 == 0;;
    };

    EXPECT_CALL(expected, call());
    functional::match(2)
                     (is_even, [&] { expected.call(); });

    functional::match(1)
                     (is_even, [&] { unexpected.call(); });

    EXPECT_CALL(expected, call());
    functional::match(2)
                     (2      , [&] { expected.call(); })
                     (is_even, [&] { unexpected.call(); });
}
