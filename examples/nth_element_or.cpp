#include "expressive/nth_element_or.hpp"

#include <type_traits>

struct one{};
struct two{};
struct three{};

struct alternative{};

auto main() -> int
{
    static_assert(std::is_same<one,         expressive::nth_element_or<0, alternative, one, two, three>::type>::value, "");
    static_assert(std::is_same<two,         expressive::nth_element_or<1, alternative, one, two, three>::type>::value, "");
    static_assert(std::is_same<three,       expressive::nth_element_or<2, alternative, one, two, three>::type>::value, "");
    static_assert(std::is_same<alternative, expressive::nth_element_or<3, alternative, one, two, three>::type>::value, "");
    static_assert(std::is_same<alternative, expressive::nth_element_or<4, alternative, one, two, three>::type>::value, "");
}
