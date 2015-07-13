#include "expressive/meta/call_with_one_arg_or_none.hpp"

#include <iostream>

auto main() -> int
{
    int i = expressive::call_with_one_arg_or_none([](int x) { std::cout << "have arg: " << x << std::endl; return 5; }, 10);
    std::cout << i << std::endl;

    expressive::call_with_one_arg_or_none([](auto x) { std::cout << "have arg: " << x << std::endl; }, 10);
    expressive::call_with_one_arg_or_none([]()      { std::cout << "no arg" << std::endl; }, 10);
}
