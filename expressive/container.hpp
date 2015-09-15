#pragma once

#include <algorithm>

namespace expressive
{

template<class Container>
auto insert(Container & p_container, const typename Container::value_type & p_value) -> decltype(p_container.push_back(p_value))
{
    return p_container.push_back(p_value);
}

template<class Container>
auto insert(Container & p_container, const typename Container::value_type & p_value) -> decltype(p_container.insert(p_value))
{
    return p_container.insert(p_value);
}

namespace exists_detail
{

template<class Container>
auto exists_impl(Container & p_container, const typename Container::value_type & p_value, float) -> bool
{
    return std::find(p_container.begin(), p_container.end(), p_value) != p_container.end();
}

template<class Container>
auto exists_impl(Container & p_container, const typename Container::key_type & p_value, int) -> bool
{
    return p_container.find(p_value) != p_container.end();
}

} // namespace exists_detail

template<class Container, class Key>
auto exists(Container & p_container, const Key & p_key) -> bool
{
    return exists_detail::exists_impl(p_container, p_key, int{});
}

} // namespace expressive
