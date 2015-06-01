#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "expressive/enumerate.hpp"
#include "expressive/container_cast.hpp"

struct loop_action_mock
{
    MOCK_METHOD2(call, void(int, int));
};

template<class container_type>
auto expect_vector_to_be_enumerated(container_type vector)
{
    loop_action_mock mock;

    EXPECT_CALL(mock, call(0, 1));
    EXPECT_CALL(mock, call(1, 2));
    EXPECT_CALL(mock, call(2, 3));

    for (auto elem : expressive::enumerate(vector))
    {
        mock.call(elem.first, elem.second);
    }
}

TEST(enumerate_tests, mutable_vector_can_be_enumerated)
{
    std::vector<int> numbers{1, 2, 3};
    expect_vector_to_be_enumerated<std::vector<int> &>(numbers);
}

TEST(enumerate_tests, value_elem_dont_mutate_elements)
{
    // this is also a std::map behavior

    std::vector<int> numbers{1};

    for (auto elem : expressive::enumerate(numbers))
        elem.first = 2;

    EXPECT_EQ(1, numbers[0]);
}

TEST(enumerate_tests, immutable_vector_can_be_enumerated)
{
    const std::vector<int> numbers{1, 2, 3};
    expect_vector_to_be_enumerated<const std::vector<int> &>(numbers);
}

TEST(enumerate_tests, can_be_converted_to_map)
{
    const auto number_names = std::vector<std::string>{"zero", "one", "two"};

    using int_to_name = std::map<int, std::string>;
    const int_to_name names = expressive::container_cast<std::map<int, std::string>>(expressive::enumerate(number_names));

    EXPECT_EQ((int_to_name{{0, "zero"}, {1, "one"}, {2, "two"}}), names);
}
