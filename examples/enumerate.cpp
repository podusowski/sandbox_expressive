#include <vector>
#include <iostream>

#include "expressive/enumerate.hpp"

auto main() -> int
{
    std::vector<int> numbers{1, 2, 3};

    for (auto elem : expressive::enumerate(numbers))
    {
        std::cout << elem.first << " - " << elem.second << std::endl;
    }
}
