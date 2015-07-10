#include <map>
#include <iostream>

#include "expressive/element.hpp"

auto make_map()
{
    return std::map<int, std::string>{{1, "one"}, {2, "two"}};
}

auto element_exists()
{
    const auto map = make_map();

    const auto found = expressive::element(map, 1, [](auto s)
    {
        std::cout << s << std::endl;
    });

    std::cout << "exists: " << std::boolalpha << found << std::endl;
}

auto element_missing()
{
    const auto map = make_map();

    const auto found = expressive::element(map, 10, [](auto s)
    {
        std::cout << "I shouldn't be called" << std::endl;
    });

    std::cout << "exists: " << std::boolalpha << found << std::endl;
}

auto main() -> int
{
    element_exists();
    element_missing();
}
