#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include "functional/composition.hpp"
#include "functional/curry.hpp"

struct my_struct
{
    int x;
};

auto take_x(const my_struct & s) -> int
{
    return s.x;
}

void find_in_container()
{
    auto is_a = functional::compose(take_x,
                                    functional::curry(std::equal_to<int>{}, 2));

    auto vec = std::vector<my_struct>{{1}, {2}};

    auto found = std::find_if(vec.begin(),
                              vec.end(),
                              is_a) != vec.end();

    std::cout << std::boolalpha << "has: " << found << std::endl;
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
