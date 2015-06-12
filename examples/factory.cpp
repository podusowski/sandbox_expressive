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
    concrete(int number, std::string name) : number(number), name(name)
    {
    }

    auto say_hello() -> void override
    {
        std::cout << "hello " << name << ", your number is " << number << ", says struct!" << std::endl;
    }

private:
    int number;
    std::string name;
};

using interface_factory = expressive::factory<interface, int>;
//using interface_factory_function_style = expressive::factory<interface(int)>;

void foo(const interface_factory & factory)
{
    auto object = factory.create(1);

    assert(object);
    object->say_hello();
}

int main()
{
    using namespace std::placeholders;
    auto factory = interface_factory::bind<concrete, int, std::string>(_1, "Piotr");
    //auto factory = interface_factory::bind<concrete(int, std::string)>(_1, "Piotr");

    foo(factory);
}
