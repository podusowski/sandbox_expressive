#pragma once

#include <iostream>

namespace functional
{

template<class value_type>
struct matcher
{
    matcher() = delete;
    matcher(const matcher<value_type> &) = default;
    matcher(matcher<value_type> &&) = default;

    explicit matcher(const value_type & value, bool active) : value(value), active(active)
    {
    }

    template<class action_type>
    auto operator () (const value_type & value, action_type action) -> matcher
    {
        std::cout << "value match\n";
        if (active and this->value == value)
        {
            action();
            return matcher{value, false};
        }
        else
        {
            return *this;
        }
    }

    template<class predicate_type, class action_type>
    auto operator () (predicate_type predicate, action_type action) -> matcher
    {
        std::cout << "pred match\n";
        if (active and predicate(this->value))
        {
            action();
            return matcher{value, false};
        }
        else
        {
            return *this;
        }
    }

private:
    const value_type & value;
    bool active;
};

template<class value_type>
auto match(const value_type & value) -> matcher<value_type>
{
    return matcher<value_type>{value, true};
}

} // namespace functional
