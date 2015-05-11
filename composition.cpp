#include <sstream>
#include <cassert>
#include <iostream>

#include "function_composition.hpp"
#include "curry.hpp"

using namespace functional;

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

auto foobar(strict_type<1> first, strict_type<2> second) -> strict_type<3>
{
    return strict_type<3>{*first + *second};
}

auto sum(int a, int b) -> int
{
    return a + b;
}

auto print_sum(int a, int b) -> void
{
    std::cout << a + b << std::endl;
}

int main()
{
    // function composition
    {
        auto composed = compose(foo, bar);
        strict_type<3> ret = composed(strict_type<1>{3});
        assert(3 == *ret);
    }

    // function currying
    {
        auto curried = curry(sum, 1);
        auto ret = curried(3);
        assert(4 == ret);
    }

    {
        auto curried = curry(print_sum, 1);
        curried(3);
    }
}
