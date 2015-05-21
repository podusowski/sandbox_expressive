#include <memory>
#include <functional>

namespace expressive
{

namespace detail
{

// need such version for std::bind -> std::function
template<class Class, class... Args>
auto make_shared_with_copied_args(Args... args) -> std::shared_ptr<Class>
{
    return std::make_shared<Class>(args...);
}

} // namespace detail

template<class Base, class... Args>
struct factory
{
    using pointer = std::shared_ptr<Base>;
    using impl_type = std::function<pointer(Args...)>;

    // FIXME: forward
    auto create(Args... args) -> pointer
    {
        return impl(args...);
    }

    // FIXME: forward
    template<class Concrete, class... BindedArgs>
    static auto bind(BindedArgs... binded_args) -> factory<Base, Args...>
    {
        impl_type impl = std::bind(std::static_pointer_cast<Base, Concrete>,
                                   std::bind(detail::make_shared_with_copied_args<Concrete, BindedArgs...>, binded_args...));

        return factory<Base, Args...>{impl};
    }

private:
    explicit factory(impl_type impl) : impl(impl)
    {
    }

    impl_type impl;
};

} // namespace expressive
