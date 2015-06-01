#pragma once

namespace expressive
{

template<class to_type, class from_type>
auto container_cast(from_type container)
{
    return to_type{container.begin(), container.end()};
}

} // namespace expressive
