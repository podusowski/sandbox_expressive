#pragma once

namespace expressive
{

template<unsigned Index, class First, class... Rest>
struct nth_element_or : public nth_element_or<Index - 1, Rest...>
{
};

template<class First, class... Rest>
struct nth_element_or<0>
{
    using type = First;
};

template<>
struct nth_element_or<0>
{
    using type = int;
};

} // namespace expressive
