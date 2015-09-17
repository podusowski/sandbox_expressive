#include "expressive/make_string.hpp"

#include <iostream>
#include <vector>

auto main() -> int
{
    auto i = int{5};
    auto b = false;
    auto v = std::vector<int>{1, 2, 3};

    std::cout << make_string(i, b);
}
