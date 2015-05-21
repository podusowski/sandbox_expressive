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
    concrete(std::string name, std::string from) : name(name), from(from)
    {
    }

    concrete(std::string name)
    {
    }

    auto say_hello() -> void override
    {
        std::cout << "hello " << name << " from " << from << ", says struct!" << std::endl;
    }

private:
    std::string name;
    std::string from;
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
    using namespace std::placeholders;
    auto factory = interface_factory::bind<concrete>(std::string("Piotr"));
    foo(factory);
}
