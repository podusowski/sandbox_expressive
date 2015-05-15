#pragma once

#include <iostream>
#include <functional>

#include "curry.hpp"

namespace functional
{

template<class value_type>
auto condition_met(const value_type & value, const value_type & equal_to) -> bool
{
    return value == equal_to;
}

template<class value_type, class predicate_type>
auto condition_met(const value_type & value, predicate_type predicate) -> bool
{
    return predicate(value);
}

template<class value_type>
auto match(const value_type &) -> void
{
}

template<class value_type,
         class value_or_preficate_type,
         class action_type,
         class... other_types>
auto match(const value_type & value,
           value_or_preficate_type match_with, action_type action,
           other_types... others) -> void
{
    if (condition_met(value, match_with))
    {
        action();
    }
    else
    {
        match(value, others...);
    }
}

} // namespace functional
