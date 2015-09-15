#pragma once

#include <ostream>

namespace expressive
{

namespace printable_detail
{

template<class T>
struct printable
{
    const T & container;
};

template<class T>
auto operator << (std::ostream & os, const printable<T> & container) -> std::ostream &
{
    auto it = container.container.begin();

    if (it != container.container.end())
    {
        os << *it;
    }

    while (++it != container.container.end())
    {
        os << ", " << *it;
    }

    return os;
}

} // namespace printable_detail

template<class T>
auto printable(const T & container)
{
    return printable_detail::printable<T>{container};
}

} // namespace expressive
