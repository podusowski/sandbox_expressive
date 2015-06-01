#pragma once

#include <ostream>
#include <typeinfo>

namespace expressive
{

template<class Tag, class Underlaying>
struct strong_type
{
    explicit strong_type(Underlaying value) : value(value)
    {
    }

    auto operator = (Underlaying value) -> strong_type &
    {
        this->value = value;
        return *this;
    }

    auto operator == (strong_type<Tag, Underlaying> other) const -> bool
    {
        return value == other.value;
    }

    auto get() const -> Underlaying
    {
        return value;
    }

    auto operator * () const -> Underlaying
    {
        return value;
    }

private:
    Underlaying value;
};

template<class Tag>
using strong_int = strong_type<Tag, int>;

template<class Tag>
using strong_unsigned = strong_type<Tag, unsigned>;

template<class Tag, class Underlaying>
std::ostream & operator << (std::ostream & os, strong_type<Tag, Underlaying> val)
{
    return os << typeid(Tag).name() << ":" << val.get();
}

} // namespace expressive
