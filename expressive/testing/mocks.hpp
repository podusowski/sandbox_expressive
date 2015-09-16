#pragma once

#include <memory>
#include <tuple>

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

private:
    template<int n, class type>
    auto nth()
    {
        auto & mock = std::get<std::shared_ptr<type>>(mocks[n]);

        if (not mock)
        {
            mock = std::make_shared<type>();
        }

        return mock;
    }

    std::array<std::tuple<std::shared_ptr<types>...>, 2> mocks;
};

} // namespace expressive
