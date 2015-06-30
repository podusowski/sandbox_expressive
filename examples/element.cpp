#include <map>
#include <iostream>

namespace expressive
{

template<class Map, class Action>
auto element(const Map & map, typename Map::key_type key, Action action)
{
    const auto it = map.find(key);

    if (it != map.end())
    {
        action(it->second);
    }
}

} // namespace expressive

auto main() -> int
{
    const auto map = std::map<int, std::string>{{1, "one"}, {2, "two"}};

    expressive::element(map, 1, [](auto s)
    {
        std::cout << s << std::endl;
    });

    expressive::element(map, 10, [](auto s)
    {
        std::cout << "I shouldn't be called" << std::endl;
    });
}
