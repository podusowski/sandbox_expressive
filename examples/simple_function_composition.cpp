#include <sstream>
#include <cassert>
#include <iostream>
#include <functional>

#include "expressive/functional/composition.hpp"
#include "expressive/strong_type.hpp"

struct one;
struct two;
struct three;

using type1 = expressive::strong_int<one>;
using type2 = expressive::strong_int<two>;
using type3 = expressive::strong_int<three>;

auto foo(type1 value) -> type2
{
    return type2{*value};
}

auto bar(type2 value) -> type3
{
    return type3{*value};
}

// usage

auto functional_way()
{
    using namespace expressive::functional;

    auto foobar = compose(foo, bar);

    /* to ensure return type */ type3 ret = foobar(type1{3});

    assert(3 == *ret);
}

auto std_bind_way()
{
    using namespace std::placeholders;

    auto foobar = std::bind(bar, std::bind(foo, _1));

    /* to ensure return type */ type3 ret = foobar(type1{3});

    assert(3 == *ret);
}

int main()
{
    functional_way();
    std_bind_way();
}
