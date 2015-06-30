#pragma once

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
