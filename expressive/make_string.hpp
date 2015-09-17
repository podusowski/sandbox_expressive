#pragma once

#include <sstream>

template<class T>
auto make_string(T && p_param)
{
    std::stringstream l_ss;
    l_ss << std::forward<T>(p_param);
    return l_ss.str();
}

template<class T, class... U>
auto make_string(T && p_param, U &&... p_params)
{
    std::stringstream l_ss;
    l_ss << std::forward<T>(p_param) << make_string(std::forward<U>(p_params)...);
    return l_ss.str();
}
