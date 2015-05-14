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

int main()
{
    auto vec = std::vector<my_struct>{{1}, {2}};

    auto equals_to_2 = functional::curry(std::equal_to<int>{}, 2);

    //std::cout << std::boolalpha << equals_to_2(3) << std::endl;


    auto is_a = functional::compose(take_x, equals_to_2);
//    auto found = std::find_if(vec.begin(), vec.end(), is_a) != vec.end();

//    std::cout << std::boolalpha << "has: " << found << std::endl;
}
