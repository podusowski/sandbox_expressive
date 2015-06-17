#pragma once

#include <tuple>

namespace expressive
{

template<bool in_range, unsigned index, class Alternative, class... Elements>
struct nth_element_or_impl;

template<unsigned index, class Alternative, class... Elements>
struct nth_element_or_impl<true, index, Alternative, Elements...>
{
    using type = typename std::tuple_element<index, std::tuple<Elements...>>::type;
};

template<unsigned index, class Alternative, class... Elements>
struct nth_element_or_impl<false, index, Alternative, Elements...>
{
    using type = Alternative;
};

template<unsigned index, class Alternative, class... Elements>
struct nth_element_or : public nth_element_or_impl<index < sizeof...(Elements), index, Alternative, Elements...>
{
};

} // namespace expressive
