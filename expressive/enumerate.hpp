#pragma once

#include <utility>
#include <cstddef>
#include <cassert>

namespace expressive
{

template<class value_iterator_type>
struct enumerating_iterator
{
    enumerating_iterator(value_iterator_type iterator, size_t index) : iterator(iterator), index(index)
    {
    }

    auto operator == (const enumerating_iterator<value_iterator_type> other) const -> bool
    {
        const auto iterators_equal = iterator == other.iterator;
        const auto index_equal = index == other.index;

        assert(iterators_equal == index_equal);

        return iterators_equal;
    }

    auto operator != (const enumerating_iterator<value_iterator_type> other) const -> bool
    {
        return not (*this == other);
    }

    auto operator ++ () -> enumerating_iterator &
    {
        iterator++;
        index++;
        return *this;
    }

    auto operator * ()
    {
        return std::make_pair(index, *iterator);
    }

private:
    value_iterator_type iterator;
    size_t index;
};

template<class iterator_type>
struct enumerating_range
{
    enumerating_range(iterator_type begin, iterator_type end) : underlaying_begin(begin), underlaying_end(end)
    {
    }

    auto begin()
    {
        return enumerating_iterator<iterator_type>{underlaying_begin,
                                                   0};
    }

    auto end()
    {
        return enumerating_iterator<iterator_type>{underlaying_end,
                                                   static_cast<size_t>(std::distance(underlaying_begin, underlaying_end))};
    }

private:
    iterator_type underlaying_begin;
    iterator_type underlaying_end;
};

template<class container_type>
auto enumerate(container_type & container)
{
    return enumerating_range<typename container_type::iterator>{container.begin(), container.end()};
}

} // namespace expressive
