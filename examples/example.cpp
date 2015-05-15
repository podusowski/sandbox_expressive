#include <sstream>
#include <cassert>
#include <iostream>
#include <functional>

#include "functional/composition.hpp"
#include "functional/curry.hpp"

template<int tag>
struct strict_type
{
    explicit strict_type(int value) : value(value)
    {
    }

    auto operator * () const -> int
    {
        return value;
    }

private:
    int value;
};

auto foo(strict_type<1> value) -> strict_type<2>
{
    return strict_type<2>{*value};
}

auto bar(strict_type<2> value) -> strict_type<3>
{
    return strict_type<3>{*value};
}

// usage

auto functional_way()
{
    using namespace functional;

    auto foobar = compose(foo, bar);

    /* to ensure return type */ strict_type<3> ret = foobar(strict_type<1>{3});

    assert(3 == *ret);
}

auto std_bind_way()
{
    using namespace std::placeholders;

    auto foobar = std::bind(bar, std::bind(foo, _1));

    /* to ensure return type */ strict_type<3> ret = foobar(strict_type<1>{3});

    assert(3 == *ret);
}

int main()
{
    functional_way();
    std_bind_way();
}
