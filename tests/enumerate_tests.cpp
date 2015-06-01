#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "expressive/enumerate.hpp"

struct loop_action_mock
{
    MOCK_METHOD2(call, void(int, int));
};

TEST(enumerate_tests, mutable_vector_can_be_enumerated)
{
    loop_action_mock mock;

    EXPECT_CALL(mock, call(0, 1));
    EXPECT_CALL(mock, call(1, 2));
    EXPECT_CALL(mock, call(2, 3));

    std::vector<int> numbers{1, 2, 3};

    for (auto elem : expressive::enumerate(numbers))
    {
        mock.call(elem.first, elem.second);
    }
}
