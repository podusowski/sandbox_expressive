#pragma once

#include <memory>
#include <functional>

namespace expressive
{

namespace factory_details
{

// need such version for std::bind -> std::function
template<class Base, class Concrete, class... Args>
auto make_shared_with_copied_args(Args... args) -> std::shared_ptr<Base>
{
    return std::make_shared<Concrete>(args...);
}

} // namespace factory_details

template<class Base, class... Args>
struct factory
{
    using pointer = std::shared_ptr<Base>;
    using impl_type = std::function<pointer(Args...)>;

    factory()
    {
    }

    virtual auto create(Args... args) const -> pointer
    {
        return impl(args...);
    }

    template<class Concrete, class... ConcreteArgs, class... BindedArgs>
    static auto bind(BindedArgs... binded_args) -> factory<Base, Args...>
    {
        // when some abstract factory is binded to some class, a constructor declaration have to be provided
        static_assert(sizeof...(ConcreteArgs) == sizeof...(BindedArgs), "you have to provide constructor arguments");

        impl_type impl = std::bind(factory_details::make_shared_with_copied_args<Base, Concrete, ConcreteArgs...>, binded_args...);

        return factory<Base, Args...>{impl};
    }

private:
    explicit factory(impl_type impl) : impl(impl)
    {
    }

    impl_type impl;
};

} // namespace expressive
