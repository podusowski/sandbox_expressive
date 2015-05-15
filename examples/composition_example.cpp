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

void find_in_container()
{
    auto ints_are_equal = std::equal_to<int>{};

    using namespace functional;

    auto x_is_equal_to_2 = compose(member(&my_struct::x),
                                   curry(ints_are_equal, 2));

    using namespace std::placeholders;

    auto x_is_equal_to_2_std = std::bind(ints_are_equal,
                                         std::bind(&my_struct::x, _1),
                                         2);

    auto vec = std::vector<my_struct>{{1}, {2}};

    auto found = std::find_if(vec.begin(),
                              vec.end(),
                              x_is_equal_to_2) != vec.end();

    auto found_std = std::find_if(vec.begin(),
                                  vec.end(),
                                  x_is_equal_to_2_std) != vec.end();

    std::cout << std::boolalpha << "has: " << found << "/" << found_std << std::endl;
}

auto sum_of_4(int a, int b, int c, int d) -> int
{
    return a + b + c + d;
}

void multiarguments()
{
    auto sum_of_3args_and_1 = functional::curry(sum_of_4, 1);
    std::cout << sum_of_3args_and_1(1, 2, 3) << std::endl;
}

int main()
{
    find_in_container();
    multiarguments();
}
