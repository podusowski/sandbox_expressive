#pragma once

#include <type_traits>

namespace expressive
{

template<class function_type, class arg_type>
auto call_with_one_arg_or_none(function_type function, arg_type arg) -> decltype(function(std::declval<arg_type>()))
{
    function(arg);
}

template<class function_type, class arg_type>
auto call_with_one_arg_or_none(function_type function, arg_type arg) -> decltype(function())
{
    function();
}

} // namespace expressive
