#include <memory>
#include <functional>

namespace expressive
{

namespace detail
{

// need such version for std::bind -> std::function
template<class Base, class Concrete, class... Args>
auto make_shared_with_copied_args(Args... args) -> std::shared_ptr<Base>
{
    return std::make_shared<Concrete>(args...);
}

} // namespace detail

template<class Base, class... Args>
struct factory
{
    using pointer = std::shared_ptr<Base>;
    using impl_type = std::function<pointer(Args...)>;

    auto create(Args... args) -> pointer
    {
        return impl(args...);
    }

    template<class Concrete, class... ConcreteArgs, class... BindedArgs>
    static auto bind(BindedArgs... binded_args) -> factory<Base, Args...>
    {
        impl_type impl = std::bind(detail::make_shared_with_copied_args<Base, Concrete, ConcreteArgs...>, binded_args...);

        return factory<Base, Args...>{impl};
    }

private:
    explicit factory(impl_type impl) : impl(impl)
    {
    }

    impl_type impl;
};

} // namespace expressive
