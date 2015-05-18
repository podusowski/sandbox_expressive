#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include "functional/composition.hpp"
#include "functional/curry.hpp"
#include "functional/member.hpp"

struct my_struct
{
    int x;
};

//struct validator
//{
//    auto is_valid(int) const -> bool
//    {
//        return true;
//    }
//};

auto ints_are_equal(int a, int b) -> bool
{
    // there is std::equal_to template but it's a struct
    // for some reason and therefore it's usage is more
    // complicated than simple function

    return a == b;
}

auto expressive_style(const std::vector<my_struct> & vec) -> bool
{
    using namespace functional;

    const auto x_is_equal_to_2 = compose(member(&my_struct::x),
                                         curry(ints_are_equal, 2));

    return std::find_if(vec.begin(), vec.end(), x_is_equal_to_2) != vec.end();
}

auto bind_style(const std::vector<my_struct> & vec) -> bool
{
    using namespace std::placeholders;

    const auto x_is_equal_to_2 = std::bind(ints_are_equal,
                                           std::bind(&my_struct::x, _1),
                                           2);

    return std::find_if(vec.begin(), vec.end(), x_is_equal_to_2) != vec.end();
}

int main()
{
    const auto vec = std::vector<my_struct>{{1}, {2}};
    std::cout << std::boolalpha << "has: " << expressive_style(vec) << "/" << bind_style(vec) << std::endl;
}
