#pragma once

namespace expressive
{
namespace functional
{

namespace method_details
{

template<class, class>
struct callable;

template<class Pointer, class Result, class Class, class... Args>
struct callable<Pointer, Result (Class::*)(Args...) const>
{
    callable(Pointer object, Result (Class::* method)(Args...) const) : object(object), method(method)
    {
    }

    auto operator() (Args... args) const
    {
        return ((*object).*method)(args...);
    }

private:
    Pointer object;
    Result (Class::* method)(Args...) const;
};

template<class Pointer, class Result, class Class, class... Args>
struct callable<Pointer, Result (Class::*)(Args...)>
{
    callable(Pointer object, Result (Class::* method)(Args...)) : object(object), method(method)
    {
    }

    auto operator() (Args... args)
    {
        return ((*object).*method)(args...);
    }

private:
    Pointer object;
    Result (Class::* method)(Args...);
};

} // namespace method_details

/**
 * Value passed through object argument is stored as-is in resulting callable,
 * this means that you can put for example std::shared_ptr and it will be stored.
 */
template<class Pointer, class Method>
auto method(Pointer object, Method p)
{
    return method_details::callable<Pointer, Method>{object, p};
}

} // namespace functional
} // namespace expressive
