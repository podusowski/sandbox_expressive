#include "functional/match.hpp"

#include <iostream>

auto is_even(int i) -> bool
{
    return i % 2 == 0;
}

int main()
{
    auto i = 4;

    functional::match(i)
                     (2 ,      []{ std::cout << "it's 2!" << std::endl; })
                     (4 ,      []{ std::cout << "it's 4!" << std::endl; })
                     (is_even, []{ std::cout << "it's even!" << std::endl; });

//    functional::match(i,       2)
//                     (2,       functional::match::any) []{ std::cout << "it's 2!" << std::endl; }
//                     (4,       2                     ) []{ std::cout << "it's 4!" << std::endl; }
//                     (is_even, 2                     ) []{ std::cout << "it's even!" << std::endl; };
}
