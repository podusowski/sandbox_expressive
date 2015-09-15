#pragma once

namespace expressive
{
namespace functional
{

namespace method_details
{

template<class Pointer, class T>
struct method_wrapper;

template<class Pointer, class Result, class Class, class... Args>
struct method_wrapper<Pointer, Result (Class::*)(Args...) const>
{
    method_wrapper(Pointer object, Result (Class::* method)(Args...) const) : object(object), method(method)
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
struct method_wrapper<Pointer, Result (Class::*)(Args...)>
{
    method_wrapper(Pointer object, Result (Class::* method)(Args...)) : object(object), method(method)
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

template<class Pointer, class Method>
auto method(Pointer object, Method p) -> method_details::method_wrapper<Pointer, Method>
{
    return method_details::method_wrapper<Pointer, Method>{object, p};
}

} // namespace functional
} // namespace expressive
