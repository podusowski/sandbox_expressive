#include <memory>

namespace expressive
{

template<class Base>
struct factory
{
    using pointer = std::shared_ptr<Base>;

    auto create() -> pointer
    {
        return pointer{};
    }

    template<class Concrete>
    static auto bind() -> factory<Base>
    {
        return factory<Base>{};
    }
};

} // namespace expressive
