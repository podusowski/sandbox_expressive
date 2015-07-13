#pragma once

#include "expressive/meta/function_traits.hpp"

#include <type_traits>

namespace expressive
{

template<class function_type, class arg_type>
auto call_with_one_arg_or_none(function_type function, arg_type arg) -> typename std::enable_if<function_traits<function_type>::has_arg, void>::type
{
    function(arg);
}

template<class function_type, class arg_type>
auto call_with_one_arg_or_none(function_type function, arg_type arg) -> typename std::enable_if<!function_traits<function_type>::has_arg, void>::type
{
    function();
}

} // namespace expressive
