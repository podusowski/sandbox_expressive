#include "functional/match.hpp"

#include <iostream>
#include <map>

auto is_even(int i) -> bool
{
    return i % 2 == 0;
}

auto container_lookup() -> void
{
     auto map = std::map<int, int>{{1, 2}, {2, 3}};

     functional::match(map.find(1),
                       map.end()            , [] { std::cout << "doesn't have it" << std::endl; },
                       functional::otherwise, [] { std::cout << "have it" << std::endl; } );
}

auto main() -> int
{
    auto i = 4;

    functional::match(i,
                      2      , []{ std::cout << "it's 2!" << std::endl; },
                      4      , []{ std::cout << "it's 4!" << std::endl; },
                      is_even, []{ std::cout << "it's even!" << std::endl; });

    auto divided = functional::match(i,
                                     is_even,               [i]{ return i / 2; },
                                     functional::otherwise, [ ]{ return 1; });

    std::cout << "divided: " << divided << std::endl;

    container_lookup();
}
