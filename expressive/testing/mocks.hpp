#pragma once

#include <memory>
#include <tuple>

#include <gmock/gmock.h>

namespace expressive
{

template<class... types>
struct mocks
{
    template<class type>
    auto first()
    {
        return nth<0, type>();
    }

    template<class type>
    auto second()
    {
        return nth<1, type>();
    }

    template<class type>
    auto third()
    {
        return nth<2, type>();
    }

private:
    template<int n, class type>
    auto nth()
    {
        auto & mock = std::get<std::shared_ptr<type>>(mocks[n]);

        if (not mock)
        {
            mock = std::make_shared<testing::StrictMock<type>>();
        }

        return std::dynamic_pointer_cast<testing::StrictMock<type>>(mock);
    }

    std::array<std::tuple<std::shared_ptr<types>...>, 3> mocks;
};

} // namespace expressive
