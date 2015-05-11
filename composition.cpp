#include <iostream>
#include <sstream>
#include <cmath>
#include <memory>

#include "function_composition.hpp"

struct type1 {};
struct type2 {};
struct type3 {};

auto foo(type1) -> type2
{
    return type2{};
}

auto bar(type2) -> type3
{
    return type3{};
}

auto derefence(std::shared_ptr<std::string> sp) -> std::string
{
    return *sp;
}

auto string_to_int(std::string s) -> int
{
    std::stringstream ss(s);
    int ret;
    ss >> ret;
    return ret;
}

int main()
{
    auto composed = compose(&foo, &bar);
    type3 ret = composed(type1{});

    {
        auto c = compose(derefence, string_to_int);
        int i = c(std::make_shared<std::string>("2"));
        std::cout << i << std::endl;
    }
}
