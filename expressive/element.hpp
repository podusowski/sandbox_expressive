#pragma once

namespace expressive
{

template<class Map>
auto element(const Map & map, typename Map::key_type key)
{
    const auto it = map.find(key);

    if (it != map.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class Map, class Action>
auto element(const Map & map, typename Map::key_type key, Action action)
{
    const auto it = map.find(key);

    if (it != map.end())
    {
        action(it->second);
        return true;
    }
    else
    {
        return false;
    }
}

template<class Map, class Action, class Else>
auto element(const Map & map, typename Map::key_type key, Action action, Else els)
{
    const auto it = map.find(key);

    if (it != map.end())
    {
        action(it->second);
        return true;
    }
    else
    {
        els();
        return false;
    }
}

} // namespace expressive
