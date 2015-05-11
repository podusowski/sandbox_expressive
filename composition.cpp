#include <sstream>
#include <cassert>

#include "function_composition.hpp"

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

int main()
{
    {
        auto composed = compose(&foo, &bar);
        strict_type<3> ret = composed(strict_type<1>{3});
        assert(3 == *ret);
    }
}
