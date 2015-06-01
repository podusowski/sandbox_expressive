#pragma once

#include "function_traits.hpp"

#include <type_traits>

namespace functional
{

namespace curry_details
{

template<class Callable, class Arg, class... Others>
struct curried
{
    curried() = delete;

    curried(Callable callable, Arg arg) : callable(callable), arg(arg)
    {
    }

    auto operator () (Others... others) const -> typename function_traits<Callable>::return_type
    {
        return callable(arg, others...);
    }

private:
    typename std::remove_reference<Callable>::type callable;
    typename std::remove_reference<Arg>::type arg;
};

template<class Callable>
struct curry_traits : public curry_traits<decltype(&Callable::operator())>
{
};

template<class Result, class Class, class Arg, class... Rest>
struct curry_traits<Result(Class::*)(Arg, Rest...) const>
{
    template<class Callable>
    struct curried_callable
    {
        using type = curried<Callable, Arg, Rest...>;
    };
};

template<class Result, class Class, class Arg, class... Rest>
struct curry_traits<Result(Class::*)(Arg, Rest...)>
{
    template<class Callable>
    struct curried_callable
    {
        using type = curried<Callable, Arg, Rest...>;
    };
};

template<class Result, class Arg, class... Rest>
struct curry_traits<Result(*)(Arg, Rest...)>
{
    template<class Callable>
    struct curried_callable
    {
        using type = curried<Callable, Arg, Rest...>;
    };
};

} // namespace curry_details

template<class Callable, class Arg>
auto curry(Callable callable, Arg arg)
{
    return typename curry_details::curry_traits<Callable>::template curried_callable<Callable>::type{callable, arg};
}

} // namespace functional
