#pragma once

#include <gmock/gmock.h>

#include "factory.hpp"
#include "expressive/meta/nth_element_or.hpp"

namespace expressive
{

template<class Base, class... Args>
struct factory_mock : public expressive::factory<Base, Args...>
{
    template<unsigned index>
    using arg = typename nth_element_or<index, int, Args...>::type;

    MOCK_CONST_METHOD1_T(create, std::shared_ptr<Base>(arg<0>));
    MOCK_CONST_METHOD2_T(create, std::shared_ptr<Base>(arg<0>, arg<1>));
    MOCK_CONST_METHOD3_T(create, std::shared_ptr<Base>(arg<0>, arg<1>, arg<2>));
    MOCK_CONST_METHOD4_T(create, std::shared_ptr<Base>(arg<0>, arg<1>, arg<2>, arg<3>));
};

} // namespace expressive
