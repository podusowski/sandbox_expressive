#pragma once

#include "meta/function_traits.hpp"

namespace expressive
{
namespace functional
{

template<class First, class Second>
struct composition
{
    composition(First first, Second second) : first(first), second(second)
    {
    }

    auto operator () (typename function_traits<First>::arg_type arg) -> typename function_traits<Second>::return_type
    {
        return second(first(arg));
    }

private:
    First first;
    Second second;
};

/**
 * calling the result will be equivalent to second(first(x))
 */
template<class First, class Second>
auto compose(First first, Second second)
{
    return composition<First, Second>{first, second};
}

/**
 * calling the result will be equivalent to third...(second(first(x)))
 */
template<class First, class Second, class... Rest>
auto compose(First first, Second second, Rest... rest)
{
    return compose(compose(first, second), rest...);
}

} // namespace functional
} // namespace expressive
