#pragma once

#include <stdexcept>

namespace functional
{

struct bad_match : public std::runtime_error
{
    bad_match() : std::runtime_error{"didn't match_impl anything"}
    {
    }
};

template<class value_type>
auto condition_met(const value_type & value, const value_type & equal_to) -> bool
{
    return value == equal_to;
}

template<class value_type,
         class predicate_type>
auto condition_met(const value_type & value, predicate_type predicate) -> bool
{
    return predicate(value);
}

template<class return_type,
         class value_type>
auto match_impl(const value_type &) -> return_type
{
    throw bad_match{};
}

template<class return_type,
         class value_type,
         class value_or_preficate_type,
         class action_type,
         class... other_types>
auto match_impl(const value_type & value,
           value_or_preficate_type match_with, action_type action,
           other_types... others) -> return_type
{
    if (condition_met(value, match_with))
    {
        return action();
    }
    else
    {
        return match_impl<return_type>(value, others...);
    }
}

template<class value_type,
         class value_or_preficate_type,
         class action_type,
         class... other_types>
auto match(const value_type & value,
           value_or_preficate_type match_with, action_type action,
           other_types... others) -> decltype(action())
{
    return match_impl<decltype(action())>(value, match_with, action, others...);
}

struct otherwise_t
{
    template<class... arg_types>
    auto operator() (arg_types...) const -> bool
    {
        return true;
    }
};

constexpr otherwise_t otherwise = otherwise_t{};

} // namespace functional
