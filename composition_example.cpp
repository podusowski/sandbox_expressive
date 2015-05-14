#include <memory>
#include <iostream>

#include "functional/composition.hpp"
#include "functional/curry.hpp"

auto indirected(std::shared_ptr<int> x) -> int
{
    return *x;
}

auto power_of_two(int x) -> int
{
    return x * x;
}

int main()
{
    auto x = std::make_shared<int>(5);
    auto pow = functional::compose(indirected, power_of_two);
    std::cout << pow(x) << std::endl;
}
