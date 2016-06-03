#pragma once

#include <sstream>
#include <cxxabi.h>

namespace make_string_detail
{

template<class T>
auto print_value_or_container_impl(T && value, std::ostream & os, int) -> typename std::enable_if<std::is_same<decltype(os << value),
                                                                                          std::ostream &>::value>::type
{
    os << value;
}

template<class T>
auto print_value_or_container_impl(T && container, std::ostream & os, float) -> typename std::enable_if<std::is_same<decltype(container.begin()),
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

template<class T>
auto print_value_or_container(T && value, std::ostream & os)
{
    print_value_or_container_impl(value, os, 0);
}

} // namespace make_string_detail

template<class T>
auto make_string(T && p_param)
{
    std::stringstream l_ss;
    make_string_detail::print_value_or_container(p_param, l_ss);
    return l_ss.str();
}

template<class T, class... U>
auto make_string(T && p_param, U &&... p_params)
{
    std::stringstream l_ss;
    make_string_detail::print_value_or_container(p_param, l_ss);
    make_string_detail::print_value_or_container(make_string(std::forward<U>(p_params)...), l_ss);
    return l_ss.str();
}

template<class T>
auto demangle()
{
    int status;
    char * realname = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
    auto ret = std::string(realname);
    free(realname);
    return ret;
}
