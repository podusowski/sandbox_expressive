#pragma once

namespace expressive
{
namespace functional
{

template<class T>
struct method_wrapper;

template<class Result, class Class, class... Args>
struct method_wrapper<Result (Class::*)(Args...) const>
{
    method_wrapper(const Class & object, Result (Class::* method)(Args...) const) : object(object), method(method)
    {
    }

    auto operator() (Args... args)
    {
        return (object.*method)(args...);
    }

private:
    const Class & object;
    Result (Class::* method)(Args...) const;
};

template<class Struct, class Method>
auto method(Struct & object, Method p) -> method_wrapper<Method>
{
    return method_wrapper<Method>{object, p};
}

} // namespace functional
} // namespace expressive
