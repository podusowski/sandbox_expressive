#pragma once

#include "function_traits.hpp"

namespace functional
{

template<class Callable, class Arg>
struct curried_callable
{
    curried_callable(Callable callable, Arg arg) : callable(callable), arg(arg)
    {
    }

    template<class... Args>
    auto operator () (Args... args) -> typename function_traits<Callable>::return_type
    {
        return callable(arg, args...);
    }

private:
    Callable callable;
    Arg arg;
};

template<class Callable, class Arg>
auto curry(Callable callable, Arg arg) -> curried_callable<Callable, Arg>
{
    return curried_callable<Callable, Arg>{callable, arg};
}

} // namespace functional
