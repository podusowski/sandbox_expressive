#include "factory.hpp"

#include <iostream>
#include <cassert>

struct interface
{
    virtual auto say_hello() -> void = 0;
    virtual ~interface() {}
};

struct concrete : public interface
{
    auto say_hello() -> void override
    {
        std::cout << "hello from concrete struct!" << std::endl;
    }
};

using interface_factory = expressive::factory<interface>;

void foo(interface_factory & factory)
{
    auto object = factory.create();

    assert(object);
    object->say_hello();
}

int main()
{
    auto factory = interface_factory::bind<concrete>();
    foo(factory);
}
