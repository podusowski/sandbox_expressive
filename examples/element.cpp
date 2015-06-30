#include <map>
#include <iostream>

#include "expressive/element.hpp"

auto main() -> int
{
    const auto map = std::map<int, std::string>{{1, "one"}, {2, "two"}};

    expressive::element(map, 1, [](auto s)
    {
        std::cout << s << std::endl;
    });

    expressive::element(map, 10, [](auto s)
    {
        std::cout << "I shouldn't be called" << std::endl;
    });
}
