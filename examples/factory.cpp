#include "factory.hpp"

struct interface
{
};

struct concrete : public interface
{
};

using interface_factory = expressive::factory<interface>;

void foo(interface_factory & factory)
{
    auto object = factory.create();
}

int main()
{
    auto factory = interface_factory::bind<concrete>();
    foo(factory);
}
