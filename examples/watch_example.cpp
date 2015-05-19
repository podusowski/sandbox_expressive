#include "unpure/watch.hpp"

#include <iostream>

int main()
{
    const auto print_old_and_new_value = [](bool old_value, bool new_value)
    {
        std::cout << "changed from " << std::boolalpha << old_value << " to " << new_value << std::endl;
    };

    unpure::watch<bool> value{print_old_and_new_value, false};

    value = true;
    value = true;
    value = false;
    value = false;
    value = true;
    value = false;
}
