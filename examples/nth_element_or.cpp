#include "expressive/nth_element_or.hpp"

auto main() -> int
{
    using elem = expressive::nth_element_or<0, int>;
    static_assert(std::is_same<int, elem>::value);
}
