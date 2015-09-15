#include "expressive/container.hpp"
#include "expressive/container/printable.hpp"

#include <vector>
#include <set>
#include <iostream>
#include <cassert>

auto main() -> int
{
    std::vector<int> v;
    std::set<int> s;

    expressive::insert(v, 1);

    expressive::insert(s, 1);
    expressive::insert(s, 3);

    assert(expressive::exists(v, 1));
    assert(not expressive::exists(v, 2));

    assert(expressive::exists(s, 1));
    assert(not expressive::exists(s, 2));

    std::cout << "vector: " << expressive::printable(v) << std::endl;
    std::cout << "set: " << expressive::printable(s) << std::endl;
}
