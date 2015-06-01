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
    // make_shared can't handle unified initialization :(
    my_struct(int x) : x(x)
    {
    }

    int x;
};

struct converting_object
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

template<class pointer_like>
auto dereference(pointer_like value)
{
    return *value;
}

auto expressive_style(const std::vector<std::shared_ptr<my_struct>> & vec) -> bool
{
    using namespace functional;

    const auto conv = converting_object{};

    // note that elements are not dependend on each other
    const auto take_x = member(&my_struct::x);
    const auto convert_x_to_y = method(conv, &converting_object::get_y_out_of_x);
    const auto is_equal_to_12 = curry(ints_are_equal, 12);

    const auto predicate = compose(dereference<std::shared_ptr<my_struct>>,
                                   take_x,
                                   convert_x_to_y,
                                   is_equal_to_12);

    return std::find_if(vec.begin(), vec.end(), predicate) != vec.end();
}

auto bind_style(const std::vector<std::shared_ptr<my_struct>> & vec) -> bool
{
    using namespace std::placeholders;

    const auto conv = converting_object{};

    const auto take_x = std::bind(&my_struct::x, _1);
    const auto take_x_and_convert_to_y = std::bind(&converting_object::get_y_out_of_x, &conv, take_x);
    const auto predicate = std::bind(ints_are_equal, take_x_and_convert_to_y, 12);

    return std::find_if(vec.begin(), vec.end(), predicate) != vec.end();
}

int main()
{
    const auto vec = std::vector<std::shared_ptr<my_struct>>{std::make_shared<my_struct>(1),
                                                             std::make_shared<my_struct>(2)};

    std::cout << std::boolalpha << "has: " << expressive_style(vec) << "/"
                                           << bind_style(vec) << std::endl;
}
