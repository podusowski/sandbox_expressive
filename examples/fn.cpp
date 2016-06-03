#include "expressive/make_string.hpp"
#include "expressive/fn.hpp"

#include <ostream>
#include <iostream>
#include <typeinfo>

template<class F>
std::ostream & operator << (std::ostream & os, expressive::fn_t<F> f)
{
    return os << demangle<F>();
}

auto main() -> int
{
    using namespace std::placeholders;

    {
        const auto f = fn [](int i)
                          {
                              return i + 1;
                          };

        std::cout << "(int)(1): " << f(1) << std::endl;
        std::cout << "(int)(_1)(1): " << f(_1)(1) << std::endl;
        std::cout << std::endl;
    }

    {
        const auto f = fn [](int i, int j)
                          {
                              return i + j;
                          };

        std::cout << "(int, int)(1): " << f(1) << std::endl;
        std::cout << "(int, int)(1)(1): " << f(1)(1) << std::endl;
        std::cout << "(int, int)(1, 1): " << f(1, 1) << std::endl;
        std::cout << std::endl;

        std::cout << "(int, int)(1, _1)(1): " << f(1, _1)(1) << std::endl;
        std::cout << "(int, int)(_1, 1): "    << f(_1, 1) << std::endl;
        std::cout << "(int, int)(_1, 1)(1): " << f(_1, 1)(1) << std::endl;
        std::cout << std::endl;
    }

    {
        const auto f = fn [](int i, int j, int k)
                          {
                              const auto result = (i - j) / k;
                              return make_string("(", i, " - ", j, ") / ", k, " = ", result);
                          };

        std::cout << "(int, int, int)(100): "        << f(100) << std::endl;
        std::cout << "(int, int, int)(100)(10): "    << f(100)(10) << std::endl;
        std::cout << "(int, int, int)(100)(10)(2): " << f(100)(10)(2) << std::endl;
        std::cout << "(int, int, int)(100)(10, 2): " << f(100)(10, 2) << std::endl;
        std::cout << "(int, int, int)(100, 10, 2): " << f(100, 10, 2) << std::endl;
        std::cout << "(int, int, int)(100, 10)(2): " << f(100, 10)(2) << std::endl;
        std::cout << std::endl;

        std::cout << "(int, int, int)(100, _1): "        << f(100, _1) << std::endl;
        std::cout << "(int, int, int)(100, _1)(2): "     << f(100, _1)(2) << std::endl;
        std::cout << "(int, int, int)(100, _1)(10)(2): " << f(100, _1)(10)(2) << std::endl; // 10 is applied as _1 !!!
        std::cout << "(int, int, int)(100, _1)(10, 2): " << f(100, _1)(2, 10) << std::endl;

        std::cout << std::endl;
    }
}
