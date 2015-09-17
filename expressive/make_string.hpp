#pragma once

#include <sstream>

namespace make_string_detail
{

template<class T>
auto print_to(T && value, std::ostream & os, int) -> typename std::enable_if<std::is_same<decltype(os << value),
                                                                                          std::ostream &>::value>::type
{
    os << value;
}

template<class T>
auto print_to(T && container, std::ostream & os, float) -> typename std::enable_if<std::is_same<decltype(container.begin()),
                                                                                                decltype(container.end())>::value>::type
{
    auto it = container.begin();

    if (it != container.end())
    {
        os << *it;
    }

    while (++it != container.end())
    {
        os << ", " << *it;
    }
}

} // namespace make_string_detail

template<class T>
auto make_string(T && p_param)
{
    std::stringstream l_ss;
    make_string_detail::print_to(p_param, l_ss, 0);
    return l_ss.str();
}

template<class T, class... U>
auto make_string(T && p_param, U &&... p_params)
{
    std::stringstream l_ss;
    make_string_detail::print_to(p_param, l_ss, 0);
    make_string_detail::print_to(make_string(std::forward<U>(p_params)...), l_ss, 0);
    return l_ss.str();
}
