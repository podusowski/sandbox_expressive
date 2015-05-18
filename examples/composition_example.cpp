#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include "functional/composition.hpp"
#include "functional/curry.hpp"
#include "functional/member.hpp"
#include "functional/method.hpp"

struct my_struct
{
    int x;
};

struct validator
{
    auto get_y_out_of_x(int x) const -> int
    {
        return x + 10;
    }
};

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

    const auto val = validator{};

    const auto y_equal_to_12 = compose(compose(member(&my_struct::x), method(val, &validator::get_y_out_of_x)),
                                       curry(ints_are_equal, 12));


    //const auto y_equal_to_12 = member(&my_struct::x) | method(val, &validator::get_y_out_of_x) | curry(ints_are_equal, 12);

    return std::find_if(vec.begin(), vec.end(), y_equal_to_12) != vec.end();
}

auto bind_style(const std::vector<my_struct> & vec) -> bool
{
    using namespace std::placeholders;

    const auto val = validator{};

    const auto y_equal_to_12 = std::bind(ints_are_equal,
                                        std::bind(&validator::get_y_out_of_x, &val, std::bind(&my_struct::x, _1)),
                                        12);

    return std::find_if(vec.begin(), vec.end(), y_equal_to_12) != vec.end();
}

int main()
{
    const auto vec = std::vector<my_struct>{{1}, {2}};
    std::cout << std::boolalpha << "has: " << expressive_style(vec) << "/" << bind_style(vec) << std::endl;
}