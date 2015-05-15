#include "unpure/watch.hpp"

#include <iostream>

int main()
{
    unpure::watch<bool> my_important_value;

    my_important_value.when_changed([&] { std::cout << "changed to: " << std::boolalpha << *my_important_value << std::endl; });

    my_important_value = true;
    my_important_value = true;
    my_important_value = !(*my_important_value);
}
