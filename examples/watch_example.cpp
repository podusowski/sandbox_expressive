#include "unpure/watch.hpp"

#include <iostream>

int main()
{
    unpure::watch<bool> value;

    value.when_changed([&] { std::cout << "changed to: " << std::boolalpha << *value << std::endl; });

    value = true;
    value = true;
    value = false;
}
