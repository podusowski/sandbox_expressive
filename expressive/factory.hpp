#include <memory>
#include <functional>

namespace expressive
{

template<class Base>
struct factory
{
    using pointer = std::shared_ptr<Base>;
    using impl_type = std::function<pointer()>;

    auto create() -> pointer
    {
        return impl();
    }

    template<class Concrete>
    static auto bind() -> factory<Base>
    {
        return factory<Base>{std::bind(std::make_shared<Concrete>)};
    }

private:
    explicit factory(impl_type impl) : impl(impl)
    {
    }

    impl_type impl;
};

} // namespace expressive
