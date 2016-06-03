#include <cassert>
#include <ostream>
#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <cxxabi.h>

template<class T>
auto demangle()
{
    int status;
    char * realname = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
    auto ret = std::string(realname);
    free(realname);
    return ret;
}

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

template<class Funtion>
struct fn_t
{
    const Funtion _function;

    template<class... Args>
    auto call(int, Args... args) const -> decltype(_function(args...))
    {
        return _function(args...);
    }

    template<class... Args>
    auto call(float, Args... args) const
    {
        return store(_function, args...);
    }

    template<class F, class Arg>
    auto store(F f, Arg arg) const
    {
        using Stored = stored_t<F, Arg>;
        return fn_t<Stored>{Stored{f, arg}};
    }

    template<class F, class Arg, class... Args>
    auto store(F f, Arg arg, Args... args) const
    {
        return store(store(f, arg), args...);
    }

    template<class... Args>
    auto operator () (Args... args) const -> decltype(call(int{}, args...))
    {
        return call(int{}, args...);
    }
};

template<class F>
std::ostream & operator << (std::ostream & os, fn_t<F> f)
{
    return os << demangle<F>();
}

template<class F>
auto fn(F function)
{
    return fn_t<F>{function};
}

struct _t
{
    template<class F>
    auto operator / (F function) const
    {
        return fn(function);
    }
};

constexpr auto _ = _t{};
#define curry _/

auto main() -> int
{
    {
        const auto f = curry [](int i)
                             {
                                 return i + 1;
                             };

        std::cout << "(int)(1): " << f(1) << std::endl;
        std::cout << std::endl;
    }

    {
        const auto f = curry [](int i, int j)
                             {
                                 return i + j;
                             };

        std::cout << "(int, int)(1): " << f(1) << std::endl;
        std::cout << "(int, int)(1)(1): " << f(1)(1) << std::endl;
        std::cout << "(int, int)(1, 1): " << f(1, 1) << std::endl;
        std::cout << std::endl;
    }

    {
        const auto f = curry [](int i, int j, int k)
                             {
                                 return (i - j) / k;
                             };

        std::cout << "(int, int, int)(100): "        << f(100) << std::endl;
        std::cout << "(int, int, int)(100)(10): "    << f(100)(10) << std::endl;
        std::cout << "(int, int, int)(100)(10)(2): " << f(100)(10)(2) << std::endl;
        std::cout << "(int, int, int)(100)(10, 2): " << f(100)(10, 2) << std::endl;
        std::cout << "(int, int, int)(100, 10, 2): " << f(100, 10, 2) << std::endl;
        std::cout << "(int, int, int)(100, 10)(2): " << f(100, 10)(2) << std::endl;
        std::cout << std::endl;
    }
}
