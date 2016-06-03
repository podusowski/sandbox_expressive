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
    F _function;
    StoredArg _arg;

    template<class Arg>
    auto operator() (Arg arg) const -> decltype(_function(_arg, arg))
    {
        return _function(_arg, arg);
    }
};

template<class F>
struct stored_t<F, void>
{
    F _function;

    template<class Arg>
    auto operator() (Arg arg) const -> decltype(_function(arg))
    {
        return _function(arg);
    }
};

template<class F>
struct fn_t
{
    F _function;

    template<class Arg>
    auto call(int, Arg arg) const -> decltype(_function(arg))
    {
        return _function(arg);
    }

    template<class Arg>
    auto call(float, Arg arg) const
    {
        using Stored = stored_t<decltype(*this), Arg>;

        return fn_t<Stored>{Stored{*this, arg}};
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

        const auto i = f(1);

        std::cout << "(int)(1): " << i << std::endl;
        std::cout << std::endl;
    }

    {
        const auto f = curry [](int i, int j)
                             {
                                 return i + j;
                             };

        std::cout << "(int, int)(1): " << f(1) << std::endl;
        std::cout << "(int, int)(1)(1): " << f(1)(1) << std::endl;

//        assert(i == 2);
    }
}
