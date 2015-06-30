#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "expressive/element.hpp"

namespace
{

const auto map_of_numbers = std::map<int, std::string>{{1, "one"}, {2, "two"}};

} // namespace

template<class T>
struct action_mock
{
    MOCK_METHOD1_T(call, void(T));
};

template<class T>
using action_strict_mock = testing::StrictMock<action_mock<T>>;

struct else_mock
{
    MOCK_METHOD0(call, void());
};

using else_strict_mock = testing::StrictMock<else_mock>;

TEST(element_tests, action_called_when_element_is_found)
{
    action_strict_mock<std::string> action;

    EXPECT_CALL(action, call("one"));

    expressive::element(map_of_numbers, 1, [&](auto s)
    {
        action.call(s);
    });
}

TEST(element_tests, else_action_called_when_element_is_missing)
{
    action_strict_mock<std::string> action;
    else_mock els;

    EXPECT_CALL(els, call());

    expressive::element(map_of_numbers, 10, [&](auto s)
    {
        action.call(s);
    },
    [&]()
    {
        els.call();
    });
}
