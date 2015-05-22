#pragma once

#include <gmock/gmock.h>

#include "factory.hpp"

template<class Base, class Arg0, class Arg1>
struct factory_mock : public expressive::factory<Base, Arg0, Arg1>
{
    MOCK_METHOD1_T(create, std::shared_ptr<Base>(Arg0));
    MOCK_METHOD2_T(create, std::shared_ptr<Base>(Arg0, Arg1));
    //MOCK_METHOD3_T(create, std::shared_ptr<Base>(Arg0, Arg1, Arg2));
};
