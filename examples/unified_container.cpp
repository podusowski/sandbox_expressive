#include <vector>
#include <set>
#include <type_traits>
#include <iostream>

template<class Container>
auto insert(Container & p_container, const typename Container::value_type & p_value) -> decltype(p_container.push_back(p_value))
{
    return p_container.push_back(p_value);
}

template<class Container>
auto insert(Container & p_container, const typename Container::value_type & p_value) -> decltype(p_container.insert(p_value))
{
    return p_container.insert(p_value);
}

template<class Container>
auto print(const Container & p_container)
{
    for (const auto & e : p_container)
    {
        std::cout << e << " ";
    }
}

auto main() -> int
{
    std::vector<int> v;
    std::set<int> s;
    insert(v, 1);
    insert(s, 1);

    print(v);
    print(s);
}
