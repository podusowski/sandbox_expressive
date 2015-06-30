#pragma once

namespace expressive
{
namespace functional
{

template<class pointer_like>
auto dereference(pointer_like value)
{
    return *value;
}

} // namespace functional
} // namespace expressive
