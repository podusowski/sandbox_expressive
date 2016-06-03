#pragma once

#include <functional>

namespace expressive
{

template<class F, class StoredArg>
struct stored_t
{
    const F _function;
    const StoredArg _arg;

    template<class... Args>
    auto operator() (Args... args) const -> decltype(_function(_arg, args...))
    {
        return _function(_arg, args...);
    }
};

template<class F>
struct stored_t<F, void>
{
    const F _function;

    template<class... Args>
    auto operator() (Args... args) const -> decltype(_function(args...))
    {
        return _function(args...);
    }
};

template<class F, class... Args>
auto callable_with_impl(int, F f, Args... args) -> decltype(f(args...), std::true_type{});

template<class F, class... Args>
auto callable_with_impl(float, F f, Args... args) -> std::false_type;

template<class F, class... Args>
auto callable_with(F f, Args... args)
{
    return decltype(callable_with_impl(int{}, f, args...)){};
}

template<class Funtion>
struct fn_t
{
    const Funtion _function;

    template<class... Args>
    auto call(std::true_type /* callable */, Args... args) const
    {
        return _function(args...);
    }

    template<class... Args>
    auto call(std::false_type /* callable */, Args... args) const
    {
        return store(_function, args...);
    }

    template<class F, class Arg>
    auto store_or_bind(std::true_type /* placeholder */, F f, Arg arg) const
    {
        using fn = fn_t<decltype(std::bind(f, arg))>;
        return fn{std::bind(f, arg)};
    }

    template<class F, class Arg>
    auto store_or_bind(std::false_type /* placeholder */, F f, Arg arg) const
    {
        using Stored = stored_t<F, Arg>;
        return fn_t<Stored>{Stored{f, arg}};
    }

    template<class F, class Arg>
    auto store(F f, Arg arg) const
    {
        using Placeholder = std::integral_constant<bool, std::is_placeholder<Arg>::value != 0>;
        return store_or_bind(Placeholder{}, f, arg);
    }

    template<class F, class Arg, class... Args>
    auto store(F f, Arg arg, Args... args) const
    {
        return store(store(f, arg), args...);
    }

    template<class... Args>
    auto operator () (Args... args) const
    {
        return call(callable_with(_function, args...), args...);
    }
};

template<class F>
auto make_fn(F function)
{
    return fn_t<F>{function};
}

struct fn_maker
{
    template<class F>
    auto operator % (F function) const
    {
        return make_fn(function);
    }
};

constexpr auto _make_fn = fn_maker{};

} // expressive

#define fn expressive::_make_fn %
