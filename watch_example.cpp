#include "unpure/watch.hpp"

#include <iostream>

int main()
{
    unpure::watch<bool> watcher;

    watcher.when_changed_to(true, []{ std::cout << "enabled" << std::endl; });
    watcher.when_changed_to(false, []{ std::cout << "disabled" << std::endl; });

    watcher = true;
    watcher = !(*watcher);
}
