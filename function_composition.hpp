#pragma once

#include "function_traits.hpp"

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

template<class First, class Second>
auto compose(First first, Second second) -> composition<First, Second>
{
    return composition<First, Second>{first, second};
}

template<class First, class Second, class = typename function_traits<First>::return_type>
auto operator >> (First && first, Second && second) -> void //composition<First, Second>;
//{
//    return composition<First, Second>{std::forward<First>(first),
//                                      std::forward<Second>(second)};
//}
