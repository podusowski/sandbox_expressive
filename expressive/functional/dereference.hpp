#pragma once

namespace expressive
{

template<class pointer_like>
auto dereference(pointer_like value)
{
    return *value;
}

} // namespace expressive
